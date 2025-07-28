@echo off
setlocal

rem Adjust RAYLIB_PATH if you're using standalone Raylib install
set RAYLIB_PATH=C:\raylib

if not exist exclusive (
    rem MSYS2 build
    gcc main.c -o flappy.exe -lraylib -lopengl32 -lgdi32 -lwinmm
) else (
    rem Standalone Raylib
    gcc main.c -o flappy.exe -I"%RAYLIB_PATH%\include" -L"%RAYLIB_PATH%\lib" -lraylib -lopengl32 -lgdi32 -lwinmm
)

echo Build complete.
pause
