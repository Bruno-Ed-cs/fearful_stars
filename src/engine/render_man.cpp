#include "render_man.hpp"
#include "raylib.h"
#include "globals.hpp"

using namespace Engine;

auto initialization_err = std::runtime_error("Render manager used but not initialized");

void RenderMan::send_back(Texture sprite, Rectangle render_view, Rectangle source_view, int z_index, double rotation) {

    if (!s_initialized)
        throw initialization_err;

    if(((render_view.y > canva_size().y * 1.1 || render_view.y < 0 - canva_size().y * 0.1) ||
        (render_view.x > canva_size().x * 1.1 || render_view.x < 0 - canva_size().x * 0.1)))
        return;

    s_background.push_back(RenderElement{
        .source = sprite,
        .render_view = render_view,
        .source_view = source_view,
        .z_index = z_index,
        .rotation = rotation,
    });

}

void RenderMan::send_front(Texture sprite, Rectangle render_view, Rectangle source_view, int z_index, double rotation) {

    if (!s_initialized)
        throw initialization_err;

    if(((render_view.y > canva_size().y * 1.1 || render_view.y < 0 - canva_size().y * 0.1) ||
        (render_view.x > canva_size().x * 1.1 || render_view.x < 0 - canva_size().x * 0.1)))
        return;

    s_foreground.push_back(RenderElement{
        .source = sprite,
        .render_view = render_view,
        .source_view = source_view,
        .z_index = z_index,
        .rotation = rotation,
    });
}

void RenderMan::send_middle(Texture sprite, Rectangle render_view, Rectangle source_view, int z_index, double rotation) {

    if (!s_initialized)
        throw initialization_err;

    if(((render_view.y > canva_size().y * 1.1 || render_view.y < 0 - canva_size().y * 0.1) ||
        (render_view.x > canva_size().x * 1.1 || render_view.x < 0 - canva_size().x * 0.1)))
        return;

    s_middleground.push_back(RenderElement{
        .source = sprite,
        .render_view = render_view,
        .source_view = source_view,
        .z_index = z_index == 0 ? static_cast<int>(render_view.y) : z_index,
        .rotation = rotation,
    });
}


void RenderMan::init(int canva_wid, int canva_hei) {

    s_initialized = true;
    s_canva = LoadRenderTexture(canva_wid, canva_hei);
    s_background = std::vector<RenderElement>();
    s_foreground = std::vector<RenderElement>();
    s_middleground = std::vector<RenderElement>();
}

Vector2 RenderMan::canva_size() {

    if (!s_initialized)
        throw initialization_err;

    return Vector2(s_canva.texture.width, s_canva.texture.height);

}

void RenderMan::render_to_canva() {

    auto z_sort = [](auto& element1, auto& element2){

        if (element1.z_index < element2.z_index) return true;

        return false;
    };

    std::sort(s_background.begin(), s_background.end(), z_sort);
    std::sort(s_foreground.begin(), s_foreground.end(), z_sort);
    std::sort(s_middleground.begin(), s_middleground.end(), z_sort);

    BeginTextureMode(s_canva);

    ClearBackground(BLANK);

    for (auto& element: s_background) {

        DrawTexturePro(element.source, element.source_view, element.render_view, Vector2{0, 0}, element.rotation, WHITE);
    };

    for (auto& element: s_middleground) {

        DrawTexturePro(element.source, element.source_view, element.render_view, Vector2{0, 0}, element.rotation, WHITE);
    };

    for (auto& element: s_foreground) {

        DrawTexturePro(element.source, element.source_view, element.render_view, Vector2{0, 0}, element.rotation, WHITE);
    };

    EndTextureMode();

    s_background.clear();
    s_middleground.clear();
    s_foreground.clear();
}

void RenderMan::draw_to_window() {

    if (!s_initialized)
        throw initialization_err;

    render_to_canva();

    Rectangle source = { 0, 0, (float)s_canva.texture.width, (float)s_canva.texture.height * -1 };
    Rectangle dest = { 0, 0, (float)Engine::g_window->get_width(), (float)Engine::g_window->get_height()};
    Vector2 origin = { 0, 0 };
    DrawTexturePro(s_canva.texture, source, dest, origin, 0.0f, WHITE);

}
