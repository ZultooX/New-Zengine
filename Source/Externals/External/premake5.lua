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
       Dirs.Projects.Externals.Root .. "/DDSTextureLoader/*",
       Dirs.Projects.Externals.Root .. "/Eigen/*",
       Dirs.Projects.Externals.Root .. "/nlohmann/*",
       Dirs.Projects.Externals.Root .. "/stb_image/*",
       Dirs.Projects.Externals.Root .. "/TgaFbx/*",
       Dirs.Projects.Externals.Root .. "/PhysX/*",
       Dirs.Projects.Externals.Root .. "/ImGui/*",
       Dirs.Projects.Externals.Root .. "/OpenGL/*",
       Dirs.Projects.Externals.Root .. "/SDL3/*",
    }
    
    files { 
        "**"
    }

    removefiles { 
        "*.vcxproj", 
        "*.vcxproj.filters",
        "*.lua",
        "lib/**",
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
libdirs
{
    Dirs.Projects.Externals.External .. "/External/TgaFbx/lib/debug",
    "lib/debug/"
}
links { 
    "*.lib",
    "TGAFbx-d.lib",
    "LowLevel_static_64",
    "LowLevelAABB_static_64",
    "LowLevelDynamics_static_64",
    "PhysX_64",
    "PhysXCharacterKinematic_static_64",
    "PhysXCommon_64",
    "PhysXCooking_64",
    "PhysXExtensions_static_64",
    "PhysXFoundation_64",
    "PhysXPvdSDK_static_64",
    "PhysXTask_static_64",
    "PhysXVehicle_static_64",
    "PhysXVehicle2_static_64",
    "SceneQuery_static_64",
    "SimulationController_static_64",
    "SDL3",
}
runtime "Debug"
symbols "On"
targetsuffix("-Debug")

filter "configurations:Release"
    libdirs
    {
    Dirs.Projects.Externals.External .. "/External/TgaFbx/lib/release",
        "lib/release/"
    }
    links { 
    "*.lib",
    "TGAFbx.lib",
    "PhysX_64",
    "PhysXCommon_64",
    "PhysXFoundation_64",
    "SDL3",
    }
    runtime "Release"
    optimize "On"
    targetsuffix("-Release")

filter "system:windows"
systemversion "latest"
kind 'StaticLib'
staticruntime 'off'
symbols 'On'
systemversion 'latest'
warnings 'Off'


