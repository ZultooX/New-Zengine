project 'GraphicsEngine'
location '.'
language 'C++'
cppdialect 'C++20'

-- unitybuild "On"

-- pchheader 'GraphicsEngine.pch.h'
-- pchsource 'GraphicsEngine.pch.cpp'

dependson { "Shaders" }
links {
    "External",
    "ImGui",
    "Zultools",
    -- "ECS",
    
    "d3d11",
    "d3dcompiler",
    "kernel32",
    "user32",
    "gdi32",
    "winspool",
    "comdlg32",
    "advapi32",
    "shell32",
    "ole32",
    "oleaut32",
    "uuid",
    "odbc32",
    "odbccp32",
}

targetdir(Dirs.Temp)
targetname("%{prj.name}")
objdir("%{Dirs.Temp}/%{prj.name}/%{cfg.buildcfg}")

files {
    '**.h',
    '**.hpp',
    '**.cpp',
    '**.hlsl',
    '**.hlsli',
    '../../EngineDefines.h',
}
filter {}
files { "../../EngineDefines.h" }
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

    -- Include additional directories explicitly if needed
    Dirs.Projects.Engines.Engine,
}


includedirs {
    '.',
	Dirs.Projects.Engines.GraphicsEngine .. "*",
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