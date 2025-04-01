-- Engine Project Configuration

project 'Engine'
location '.'
language 'C++'
cppdialect 'C++20'

links {
    "External",
    "ImGui",

    "GraphicsEngine",
}

targetdir(Dirs.Temp)
targetname("%{prj.name}")
objdir("%{Dirs.Temp}/%{prj.name}/%{cfg.buildcfg}")

files {
    '**.h',
    '**.hpp',
    '**.cpp',
    '**.hlsl',
    '**.hlsli', }

includedirs {
    '.',
    Dirs.Projects.Engines.Engine .. "*",
}

files { "../../EngineDefines.h" }

externalincludedirs {
    Dirs.Projects.Externals.Root .. "**",
    Dirs.Projects.Engines.GraphicsEngine,
    -- Dirs.Projects.Engines.PhysicsEngine,
    -- Dirs.Projects.Systems.ECS,
}

externalincludedirs {
    -- Include the root "Externals" directory
    Dirs.Projects.Externals.Root .. "**",

    -- Loop through all subprojects and add their directories
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

shadermodel('5.0')

filter('files:**.hlsl')
flags('ExcludeFromBuild')
shaderobjectfileoutput(Dirs.Shaders .. '%{file.basename}.cso')

filter('files:**PS.hlsl')
removeflags('ExcludeFromBuild')
shadertype('Pixel')

filter('files:**VS.hlsl')
removeflags('ExcludeFromBuild')
shadertype('Vertex')

shaderoptions({ '/WX' })
