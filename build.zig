const std = @import("std");


    "src/engine/debugger.cpp",
    "src/engine/asset_man.cpp",
    "src/engine/input_man.cpp",
    "src/engine/music_man.cpp",
    "src/gameplay/enemy/basic/basic_enemy.cpp",
    "src/gameplay/enemy/enemy_man.cpp",
    "src/gameplay/levels/levels.cpp",
    "src/gameplay/player/player_manager.cpp",
    "src/gameplay/player/player.cpp",
    "src/gameplay/player/shooting_machine.cpp",
    "src/gameplay/projectile/basic/basic_projectile.cpp",
    "src/gameplay/projectile/projectile_manager.cpp",
    "src/systems.cpp",
    "src/main.cpp",

};

const imgui_source = [_][]const u8 {

    "dependencies/dear_imgui/imgui.cpp",
    "dependencies/dear_imgui/imgui_demo.cpp",
    "dependencies/dear_imgui/imgui_draw.cpp",
    "dependencies/dear_imgui/imgui_tables.cpp",
    "dependencies/dear_imgui/imgui_widgets.cpp",

    "dependencies/raylib-imgui/rlImGui.cpp",

};

const cpp_flags = [_][]const u8 {

    "-std=c++23",
    "-Wall",
};

pub fn build(b: *std.Build) void {

    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const imgui_lib = b.addLibrary(.{
        .name = "imgui",
        .linkage = .static,
        .root_module = b.addModule("imgui", .{
            .target = target,
            .optimize = optimize,
            .link_libcpp = true,

        }),
    });

    imgui_lib.addCSourceFiles(.{
        .files = imgui_source[0..],
        .flags = cpp_flags[0..],
    });

    imgui_lib.addIncludePath(b.path("dependencies/dear_imgui/"));
    imgui_lib.addIncludePath(b.path("include/"));

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
    exe.linkLibrary(imgui_lib);

    exe.addIncludePath(b.path("src/engine/"));
    exe.addIncludePath(b.path("include/"));
    exe.addIncludePath(b.path("src/"));


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
