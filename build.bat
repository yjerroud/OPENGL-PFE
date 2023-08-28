@echo off

set INCLUDE_IMGUI=/I .\..\dependencies\imgui\
set INCLUDE_GLFW3=/I .\..\dependencies\glfw3\include\
set INCLUDE_GLEW=/I .\..\dependencies\glew\include\
set INCLUDE_STB=/I .\..\dependencies\
set LIBS=opengl32.lib user32.lib kernel32.lib gdi32.lib .\..\dependencies\glfw3\lib-vc2022\glfw3dll.lib .\..\dependencies\glew\glew32s.lib

IF NOT EXIST build (
	mkdir build
	copy dependencies\glfw3\lib-vc2022\glfw3.dll build\.
)

pushd build

cl /Zi -D DEBUG %INCLUDE_STB% %INCLUDE_IMGUI% %INCLUDE_GLEW% %INCLUDE_GLFW3% ..\src\main.cpp %LIBS% /FePFE

popd
