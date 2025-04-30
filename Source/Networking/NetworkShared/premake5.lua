-- Engine Project Configuration

project 'NetworkShared'
location '.'
language 'C++'
cppdialect 'C++20'

links {

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
kind 'StaticLib'
staticruntime 'off'
symbols 'On'
systemversion 'latest'
warnings 'Extra'

