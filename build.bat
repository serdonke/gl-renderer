@echo off
setlocal enabledelayedexpansion

:: Run CMake to configure and build
cmake -B build
if %ERRORLEVEL% neq 0 exit /b 1

cmake --build build --parallel
if %ERRORLEVEL% neq 0 exit /b 1

:: Check if an argument is given and executable exists
if "%~1" neq "" if exist "build\%~1.exe" (
    cd build
    "%~1.exe"
) else (
    echo.
    echo To run examples: build.bat [NAME]
    echo Available options:
    for %%F in (build\*.exe) do echo [32m%%~nxF[0m
)

