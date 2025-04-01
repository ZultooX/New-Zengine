-- Engine Project Configuration

project 'ECS'
location '.'
language 'C++'
cppdialect 'C++20'

links {
    "External",
    "ImGui",
    "Zultools",

    "PhysicsEngine",
    "Common",
}


targetdir(Dirs.Temp)
targetname("%{prj.name}")
objdir("%{Dirs.Temp}/%{prj.name}/%{cfg.buildcfg}")

files {
    '**.h',
    '**.hpp',
    '**.cpp',
}

includedirs {
    '.',
    Dirs.Projects.Systems.ECS .. "*"
}


externalincludedirs {
    Dirs.Projects.Engines.Engine,
    Dirs.Projects.Engines.GraphicsEngine,
    Dirs.Projects.Engines.PhysicsEngine,
    Dirs.Projects.Externals.Root .. "**",

    table.unpack(
        (function()
            local dirs = {}
            for _, dir in pairs(Dirs.Projects.Externals) do
                table.insert(dirs, dir .. "/**")
            end
            return dirs
        end)()
    ),
}


filter 'configurations:Debug'
defines { '_DEBUG' }
runtime 'Debug'
symbols 'on'
targetsuffix("-Debug")

filter 'configurations:Release'
defines '_RELEASE'
runtime 'Release'
optimize 'on'
targetsuffix("-Release")

filter 'system:windows'
kind 'StaticLib'
staticruntime 'off'
symbols 'On'
systemversion 'latest'
warnings 'Extra'
