----------- Setup default variables
local releasePrefix = ""
local debugPrefix = ""

local currentDir = os.getcwd()
local dirName = currentDir:match("([^/\\]+)$")



function setupProject()
    project(dirName)

    location '.'
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"


    targetname("%{prj.name}")
    objdir("%{Dirs.Temp}/%{prj.name}/%{cfg.buildcfg}")
end

function loadFiles()
    libdirs("/Lib/")
 
    includedirs {
        ".",
       Dirs.Projects.Externals.Root .. dirName .. "/*"
    }
    
    files { 
        "**"
    }

    removefiles { 
        "*.vcxproj", 
        "*.vcxproj.filters",
        "*.lua",
    }
end




os.mkdir(dirName)
os.mkdir("lib")
os.mkdir("lib/debug")
os.mkdir("lib/release")

setupProject()
loadFiles()


links{ -- If both debug and release is the same.

}

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


