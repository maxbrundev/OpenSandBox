@echo off
SET version=%~1%
if "%~1"=="" SET version="vs2022"

pushd SandBox
call ..\Dependencies\premake5\bin\premake5.exe %version%
popd

PAUSE