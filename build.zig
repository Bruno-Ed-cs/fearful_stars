const std = @import("std");

const cpp_source = [_][]const u8 {

    "src/engine/debugger.cpp",
    "src/engine/asset_man.cpp",
    "src/engine/input_man.cpp",
    "src/engine/music_man.cpp",
    "src/engine/background_man.cpp",
    "src/engine/render_man.cpp",
    "src/gameplay/enemy/basic/basic_enemy.cpp",
    "src/gameplay/enemy/enemy_man.cpp",
    "src/gameplay/levels/levels.cpp",
    "src/gameplay/player/primary_shots/basic_shot.cpp",
    "src/gameplay/player/player.cpp",
    "src/gameplay/player/player_manager.cpp",
    "src/gameplay/projectile/basic/basic_projectile.cpp",
    "src/gameplay/projectile/projectile_manager.cpp",
    "src/systems.cpp",
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
    });

    const raylib_lib = raylib_dep.artifact("raylib");

    const exe = b.addExecutable(.{
        .name = "fearful_stars",
        .root_module = b.addModule("main", .{
            .optimize = optimize,
            .target = target,
            .link_libcpp = true,
        }),

    });

    exe.addCSourceFiles(.{
        .files = cpp_source[0..],
        .flags = cpp_flags[0..],
    });

    exe.linkLibrary(raylib_lib);

    exe.addIncludePath(b.path("src/engine/"));
    exe.addIncludePath(b.path("include/"));
    exe.addIncludePath(b.path("src/"));
    exe.addIncludePath(b.path("dependencies/dear_imgui/"));


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
