const std = @import("std");

const cpp_source = [_][]const u8 {


    "src/engine/background_man.cpp",
    "src/engine/input_man.cpp",
    "src/engine/render_man.cpp",
    "src/engine/asset_man.cpp",
    "src/engine/music_man.cpp",
    "src/engine/debugger.cpp",
    "src/systems.cpp",
//    "src/gameplay/enemy/vagant/vagant.cpp",
//    "src/gameplay/enemy/chaser/chaser.cpp",
//    "src/gameplay/enemy/eye/crystal_eye.cpp",
//    "src/gameplay/enemy/basic/basic_enemy.cpp",
//    "src/gameplay/enemy/enemy_man.cpp",
//    "src/gameplay/enemy/minion/minion.cpp",
//    "src/gameplay/enemy/anemonae/anemonae.cpp",
//    "src/gameplay/enemy/broken_ship/broken_ship.cpp",
//    "src/gameplay/projectile/orbital/orbital_proj.cpp",
//    "src/gameplay/projectile/missile/missile_proj.cpp",
//    "src/gameplay/projectile/plasma/plasma.cpp",
//    "src/gameplay/projectile/basic/basic_projectile.cpp",
//    "src/gameplay/projectile/upgrade/upgrade_proj.cpp",
//    "src/gameplay/projectile/projectile_manager.cpp",
//    "src/gameplay/projectile/big_shot/bigshot_proj.cpp",
//    "src/gameplay/player/aux_powers/orbital_shield.cpp",
//    "src/gameplay/player/primary_shots/basic_shot.cpp",
//    "src/gameplay/player/primary_shots/plasma_shot.cpp",
    "src/gameplay/player/player.cpp",
//    "src/gameplay/player/special_shots/big_shooter.cpp",
    "src/gameplay/player/player_manager.cpp",
//    "src/gameplay/player/secondary_shots/missile_shooter.cpp",
    "src/gameplay/ui/ui_man.cpp",
//    "src/gameplay/levels/levels.cpp",
    "src/main.cpp",


    "dependencies/dear_imgui/imgui.cpp",
    "dependencies/dear_imgui/imgui_demo.cpp",
    "dependencies/dear_imgui/imgui_draw.cpp",
    "dependencies/dear_imgui/imgui_tables.cpp",
    "dependencies/dear_imgui/imgui_widgets.cpp",

    "dependencies/raylib-imgui/rlImGui.cpp",
};

const cpp_flags = [_][]const u8 {

    "-std=c++23",
};

pub fn build(b: *std.Build) void {

    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const raylib_dep = b.dependency("raylib", .{
        .target = target,
        .optimize = optimize,
        .linux_display_backend = .X11
    });

    const raylib_lib = raylib_dep.artifact("raylib");

    var fs_mod = b.addModule("game", .{

        .link_libc = true,
        .link_libcpp = true,
        .target = target,
        .optimize = optimize,
    });

    fs_mod.addCSourceFiles(.{
        .files = cpp_source[0..],
        .flags = cpp_flags[0..],
    });

    fs_mod.linkLibrary(raylib_lib);

    fs_mod.addIncludePath(b.path("src/engine/"));
    fs_mod.addIncludePath(b.path("include/"));
    fs_mod.addIncludePath(b.path("src/"));
    fs_mod.addIncludePath(b.path("dependencies/dear_imgui/"));

    const exe = b.addExecutable(.{
        .name = "fearful_stars",
        .root_module = fs_mod,
    });


    const assets = b.addInstallDirectory(.{
        .source_dir = b.path("assets"),
        .install_dir = .bin,
        .install_subdir = "assets"

    });

    const build_step = b.getInstallStep();
    build_step.dependOn(&assets.step);

    const run = b.addRunArtifact(exe);
    run.step.dependOn(&assets.step);
    const step = b.step("run", "run the game");

    step.dependOn(&run.step);


    b.installArtifact(exe);
}
