@echo off

set name=%1%

if not exist "scripts\" cd ..
if exist "projects\%name%\" exit

if not exist "projects\" mkdir "projects"
if not exist "projects\%name%\" mkdir "projects\%name%"

set path="projects\%name%\premake5.lua"

echo project "%name%" > %path%
type config.lua >> %path%

echo include "projects/%name%" >> premake5.lua

pause