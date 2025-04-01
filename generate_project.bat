@ECHO OFF
PUSHD %~dp0
CALL "Premake/Premake5" vs2022 --file="generate_project.lua" || @PAUSE
POPD