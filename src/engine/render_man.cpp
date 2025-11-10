#include "render_man.hpp"
#include "deps.hpp"
#include "globals.hpp"
#include "winman.hpp"

using namespace Engine;

auto initialization_err = std::runtime_error("Render manager used but not initialized");

void RenderMan::send_texture(RenderMan::Plane layer, Texture sprite, Rectangle render_view, Rectangle source_view, int z_index, double rotation, Color tint) {

    if (!s_initialized)
        throw initialization_err;

    if(((render_view.y > canva_size().y * 1.1 || render_view.y < 0 - canva_size().y * 0.1) ||
        (render_view.x > canva_size().x * 1.1 || render_view.x < 0 - canva_size().x * 0.1)))
        return;


    int index = render_view.x + render_view.y + z_index;

    RenderElement element = RenderElement{
        .source = sprite,
        .render_view = render_view,
        .source_view = source_view,
        .z_index = index,
        .rotation = rotation,
        .tint = tint,
    };

    switch (layer) {

        case RenderMan::Plane::back:
            s_background.push_back(element);
        break;

        case RenderMan::Plane::front:
            s_foreground.push_back(element);
        break;

        case RenderMan::Plane::middle:
            s_middleground.push_back(element);
        break;
    
    }

}

void RenderMan::init(int canva_wid, int canva_hei) {

    s_initialized = true;
    s_canva = LoadRenderTexture(canva_wid, canva_hei);
    s_background = std::vector<RenderElement>();
    s_foreground = std::vector<RenderElement>();
    s_middleground = std::vector<RenderElement>();
    s_camera = Camera2D{
        .offset = Vector2{0, 0},
        .target = Vector2{0, 0},
        .rotation = 0.0,
        .zoom = 1.0
    };
    
}

Vector2 RenderMan::canva_size() {

    if (!s_initialized)
        throw initialization_err;

    return Vector2(s_canva.texture.width, s_canva.texture.height);

}


void RenderMan::begin_draw_debug() {
    
    BeginTextureMode(s_canva);
    BeginMode2D(s_camera);
};

void RenderMan::end_draw_debug() {

    EndMode2D();
    EndTextureMode();

};

void RenderMan::render_to_canva() {

    auto z_sort = [](auto& element1, auto& element2){

        if (element1.z_index < element2.z_index) return true;

        return false;
    };

    std::sort(s_background.begin(), s_background.end(), z_sort);
    std::sort(s_foreground.begin(), s_foreground.end(), z_sort);
    std::sort(s_middleground.begin(), s_middleground.end(), z_sort);

    BeginTextureMode(s_canva);
    BeginMode2D(s_camera);

    ClearBackground(BLANK);

    for (auto& element: s_background) {

        DrawTexturePro(element.source, element.source_view, element.render_view, Vector2{0, 0}, element.rotation, element.tint);
    };

    for (auto& element: s_middleground) {

        DrawTexturePro(element.source, element.source_view, element.render_view, Vector2{0, 0}, element.rotation, element.tint);
    };

    for (auto& element: s_foreground) {

        DrawTexturePro(element.source, element.source_view, element.render_view, Vector2{0, 0}, element.rotation, element.tint);
    };
    EndMode2D();

    EndTextureMode();

    s_background.clear();
    s_middleground.clear();
    s_foreground.clear();
}

void RenderMan::draw_to_window() {

    if (!s_initialized)
        throw initialization_err;


    double scale_factor = std::floor(Engine::WinMan::get_height() / canva_size().y);
    Vector2 position = Vector2{.x = 0, .y = 0};
    float render_wid = canva_size().x * scale_factor;
    float render_height = canva_size().y * scale_factor;

    if (render_wid < Engine::WinMan::get_width()) {

        position.x += (Engine::WinMan::get_width() - render_wid) / 2;
    }

    if (render_height < Engine::WinMan::get_height()) {

        position.y += (Engine::WinMan::get_height() - render_height) / 2;
    }

    Rectangle source = { 0, 0, (float)s_canva.texture.width, (float)s_canva.texture.height * -1 };
    Rectangle dest = { position.x, position.y, render_wid, render_height};
    Vector2 origin = { 0, 0 };
    DrawTexturePro(s_canva.texture, source, dest, origin, 0.0f, WHITE);

}

RenderTexture& RenderMan::get_canva() {

    return s_canva;
}

Camera2D& RenderMan::get_camera() {

    return s_camera;

}
