project 'Shaders'
location '.'
language 'C++'
cppdialect 'C++20'
kind "Utility"
targetdir(Dirs.Temp)
targetname("%{prj.name}")
objdir("%{Dirs.Temp}/%{prj.name}/%{cfg.buildcfg}")

files {
    '**.h',
    '**.cpp',
    '**.hlsl',
    '**.hlsli',
}

links {
    "External"
}

includedirs {
    '.',
}


externalincludedirs {
    Dirs.Projects.Externals.Zultools,
    Dirs.Projects.Externals.Eigen,
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

filter('files:**/PS_**.hlsl')
removeflags('ExcludeFromBuild')
shadertype('Pixel')
shaderobjectfileoutput(Dirs.Shaders .. 'Pixel/%{file.basename}.cso')

filter('files:**/VS_**.hlsl')
removeflags('ExcludeFromBuild')
shadertype('Vertex')
shaderobjectfileoutput(Dirs.Shaders .. 'Vertex/%{file.basename}.cso')
--, '/Zpr'
shaderoptions({ '/WX' })
