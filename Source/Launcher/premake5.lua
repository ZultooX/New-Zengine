-- Launcher project config file

local releasePrefix = ""
local debugPrefix = ""

local currentDir = os.getcwd()
local dirName = currentDir:match("([^/\\]+)$")

project "Launcher"
location "."
-- "Engine", "Game", "GraphicsEngine", "PhysicsEngine", "Editor", 
links { "GraphicsEngine", "Game", "Engine", "External", "ws2_32.lib" }

kind "WindowedApp"
language "C++"
cppdialect "C++20"

targetdir(Dirs.Bin)
debugdir(Dirs.Bin)
-- print("hi")
targetname("%{prj.name}")
objdir("%{Dirs.Temp}/%{prj.name}/%{prj.buildcfg}")

-- pchheader "stdafx.h"
-- pchsource "stdafx.cpp"

links{
}

files {
    '**.h',
    '**.hpp',
    '**.cpp',
    '**.c',
    "../EngineDefines.h" 
}

includedirs { '.' }

externalanglebrackets "On"
externalincludedirs {
    -- Dirs.Projects.Engines.PhysicsEngine,
    Dirs.Projects.Engines.Engine,
    Dirs.Projects.Externals.Root .. "**",
    Dirs.Projects.Engines.GraphicsEngine,
    Dirs.Projects.Game,
    -- Dirs.Projects.Systems.ECS,
    -- Dirs.Projects.Editor,
}
-- externalwarnings "Default"
filter "configurations:Debug"
links { 
    
}
runtime "Debug"
symbols "On"
targetsuffix("-Debug")

filter "configurations:Release"
links {

}
runtime "Release"
optimize "On"
targetsuffix("-Release")

filter "system:windows"
systemversion "latest"

-- sdlchecks "true"
-- conformanceMode "On"
-- buildoptions { "/STACK:8000000" }
flags {
    -- "FatalWarnings", -- Would be both compile and lib, the original didn't set lib
    "FatalCompileWarnings",
    "MultiProcessorCompile"
}

filter {}
