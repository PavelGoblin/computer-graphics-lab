@echo off
REM ===================================================================
REM  Computer Graphics Lab - One-Click Runner
REM  Usage: Double-click or type:  run 3   (for experiment 3)
REM ===================================================================
if "%1"=="" (
    echo [93mUsage: run ^<number^>[0m
    echo  [97mExample: run 5  [0m(runs Midpoint Circle)
    echo.
    pause
    exit /b
)

set EXP=%1

REM Map experiment number to source file
if %EXP%==2 set SRC=exp02_slope_intercept.cpp
if %EXP%==3 set SRC=exp03_dda_line.cpp
if %EXP%==4 set SRC=exp04_bresenham_line.cpp
if %EXP%==5 set SRC=exp05_midpoint_circle.cpp
if %EXP%==6 set SRC=exp06_translation.cpp
if %EXP%==7 set SRC=exp07_rotation.cpp
if %EXP%==8 set SRC=exp08_scaling.cpp
if %EXP%==9 set SRC=exp09_3d_rotation.cpp
if %EXP%==10 set SRC=exp10_cohen_sutherland.cpp
if %EXP%==11 set SRC=exp11_sutherland_hodgman.cpp
if %EXP%==12 set SRC=exp12_bezier.cpp
if %EXP%==13 set SRC=exp13_b_spline.cpp

if "%SRC%"=="" (
    echo [91mInvalid experiment number! Use 2-13[0m
    pause
    exit /b
)

echo.
echo [96m=== Compiling Experiment %EXP% ===[0m
g++ -o "exp%EXP%.exe" "%SRC%" -I "include" -L "include" -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

if %ERRORLEVEL% NEQ 0 (
    echo [91m[FAILED] Compilation error! Check g++ is installed.[0m
    pause
    exit /b
)

echo [92m[SUCCESS] Running Experiment %EXP%...[0m
echo [90m(Close the graphics window when done)[0m
echo.
exp%EXP%.exe
echo.
echo [92m[Done][0m
pause
