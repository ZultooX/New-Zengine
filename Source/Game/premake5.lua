-- Game project config file

project 'Game'
location '.'

kind 'StaticLib'
language 'C++'
cppdialect 'C++20'

targetdir(Dirs.Temp)
objdir("%{Dirs.Temp}/%{prj.name}/%{prj.buildcfg}")
targetname("%{prj.name}")

files {
    '**.h',
    '**.hpp',
    '**.cpp',
    '**.c'
}

includedirs { '.' }

links {
    "Engine",
    -- "ECS",
    "PhysicsEngine",
    "Shaders",
}

externalanglebrackets 'On'
externalincludedirs {
    Dirs.Projects.Externals.Root .. "**",
    Dirs.Projects.Engines.Engine,
    Dirs.Projects.Engines.GraphicsEngine,
    Dirs.Projects.Shaders,
    -- Dirs.Projects.Systems.ECS,
    Dirs.Projects.Engines.PhysicsEngine,
}
-- externalwarnings 'Default'

includedirs {
    '.',
    Dirs.Projects.Game .. "*"
}


filter 'configurations:Debug'
defines { '_DEBUG' }
runtime 'Debug'
symbols 'On'
targetsuffix("-Debug")

filter 'configurations:not Debug'
defines { '_NDEBUG' }
runtime 'Release'
optimize 'On'
targetsuffix("-Release")

filter 'configurations:Release'
defines { '_RELEASE' }

filter 'configurations:Retail'
defines { '_RETAIL' }

filter 'system:windows'
defines { '_WIN32' }
systemversion 'latest'
warnings 'Extra'

-- sdlchecks 'true'
-- conformanceMode 'On'
-- buildoptions { '/STACK:8000000' }
flags {
    -- 'FatalWarnings', -- Would be both compile and lib, the original didn't set lib
    'FatalCompileWarnings',
    'MultiProcessorCompile'
}

filter {}
