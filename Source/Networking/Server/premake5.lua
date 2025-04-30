-- Engine Project Configuration

project 'Server'
location '.'
language 'C++'
cppdialect 'C++20'

links {
	"NetworkShared"
}

includedirs{
	Dirs.Projects.Networking.NetworkShared .. "*"
}

targetdir(Dirs.Temp)
targetname("%{prj.name}")
objdir("%{Dirs.Temp}/%{prj.name}/%{cfg.buildcfg}")

files {
	'**.h',
	'**.hpp',
	'**.cpp',
	'**.hlsl',
	'**.hlsli',}


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
kind 'ConsoleApp'
staticruntime 'off'
symbols 'On'
systemversion 'latest'
warnings 'Extra'

