@echo off
if not exist build (
    mkdir build
)
cd build
cmake ..
cmake --build . --parallel
if %errorlevel% equ 0 (
    .\main.exe
) else (
    exit /b 1
)
