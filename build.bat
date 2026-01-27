@echo off
SETLOCAL

SET MAKE=mingw32-make
SET MAKEFILE=Makefile-raycimgui
SET AR=ar
SET CC=gcc
SET CXX=g++

:loop
if NOT "%1"=="" (
    if "%1"=="--make-cmd" (
        SET MAKE=%2
        SHIFT
    ) else if "%1"=="--makefile" (
        SET MAKEFILE=%2
        SHIFT
    ) else if "%1"=="--ar" (
        SET AR=%2
        SHIFT
    ) else if "%1"=="--cc" (
        SET CC=%2
        SHIFT
    ) else if "%1"=="--cxx" (
        SET CXX=%2
        SHIFT
    ) else if "%1"=="--clean" (
        SET IS_CLEAN=true
    )
    SHIFT
    goto :loop
)

SET LIB_NAME=raycimgui

SET SRC_DIR=src
SET VENDOR_DIR=vendor
SET BUILD_DIR=target
SET LIB_DIR=%LIB_NAME%

@REM DEPENDENCIES
SET VENDOR_RAYLIB=raylib-5.0
SET VENDOR_CIMGUI=cimgui-1.92.1-docking

if defined IS_CLEAN (
    @rmdir /s /q %LIB_DIR%      >nul 2>&1
    @rmdir /s /q %BUILD_DIR%    >nul 2>&1

    @REM BEGIN - Clean cimgui
    @cd %VENDOR_CIMGUI%
    %MAKE% -f ../Makefile-cimgui clean CXX=%CXX% OS=Windows_NT
    @cd ..
    @rmdir /s /q %VENDOR_DIR%\%VENDOR_CIMGUI%   >nul 2>&1
    @REM END - Clean cimgui
)

@REM BEGIN - Build cimgui

@cd %VENDOR_CIMGUI%
%MAKE% -f ../Makefile-cimgui CXX=%CXX% OS=Windows_NT
@cd ..

mkdir %VENDOR_DIR%\%VENDOR_CIMGUI%          >nul 2>&1
mkdir %VENDOR_DIR%\%VENDOR_CIMGUI%\include  >nul 2>&1
mkdir %VENDOR_DIR%\%VENDOR_CIMGUI%\lib      >nul 2>&1
mkdir %VENDOR_DIR%\%VENDOR_CIMGUI%\bin      >nul 2>&1

echo F | xcopy /q /y %VENDOR_CIMGUI%\imgui\LICENSE.txt      %VENDOR_DIR%\%VENDOR_CIMGUI%\LICENSE-imgui      >nul 2>&1
echo F | xcopy /q /y %VENDOR_CIMGUI%\LICENSE                %VENDOR_DIR%\%VENDOR_CIMGUI%\LICENSE-cimgui     >nul 2>&1
echo A | xcopy /q %VENDOR_CIMGUI%\README.md                 %VENDOR_DIR%\%VENDOR_CIMGUI%\                   >nul 2>&1

echo A | xcopy /q %VENDOR_CIMGUI%\cimgui.h              %VENDOR_DIR%\%VENDOR_CIMGUI%\include\           >nul 2>&1
echo A | xcopy /q %VENDOR_CIMGUI%\libcimgui.dll.a       %VENDOR_DIR%\%VENDOR_CIMGUI%\lib\               >nul 2>&1
echo A | xcopy /q %VENDOR_CIMGUI%\cimgui.dll            %VENDOR_DIR%\%VENDOR_CIMGUI%\bin\               >nul 2>&1

@REM END - Build cimgui

SET MAKEFILE_ARGS=^
    ARG_AR=%AR% ^
    ARG_CC=%CC% ^
    ARG_SRC_DIR=%SRC_DIR% ^
    ARG_BUILD_DIR=%BUILD_DIR% ^
    ARG_LIB_NAME=%LIB_NAME% ^
    ARG_VENDOR_RAYLIB=%VENDOR_RAYLIB% ^
    ARG_VENDOR_CIMGUI=%VENDOR_CIMGUI%

@echo on
%MAKE% -f %MAKEFILE% %MAKEFILE_ARGS%
@echo off

mkdir %LIB_DIR%             >nul 2>&1
mkdir %LIB_DIR%\include     >nul 2>&1
mkdir %LIB_DIR%\lib         >nul 2>&1
mkdir %LIB_DIR%\bin         >nul 2>&1

echo A | xcopy /q %VENDOR_DIR%\%VENDOR_CIMGUI%\include\*    %LIB_DIR%\include\                  >nul 2>&1
echo A | xcopy /q %VENDOR_DIR%\%VENDOR_CIMGUI%\lib\*        %LIB_DIR%\lib\                      >nul 2>&1
echo A | xcopy /q %VENDOR_DIR%\%VENDOR_CIMGUI%\bin\*        %LIB_DIR%\bin\                      >nul 2>&1

mkdir %LIB_DIR%\include\fontawesome         >nul 2>&1
echo A | xcopy /s /e /q %SRC_DIR%\fontawesome               %LIB_DIR%\include\fontawesome       >nul 2>&1

echo A | xcopy /q %SRC_DIR%\%LIB_NAME%.h                    %LIB_DIR%\include\                  >nul 2>&1
echo A | xcopy /q %BUILD_DIR%\lib%LIB_NAME%.a               %LIB_DIR%\lib\                      >nul 2>&1

@REM LICENSES
echo F | xcopy /q /y %VENDOR_DIR%\%VENDOR_CIMGUI%\LICENSE-imgui     %LIB_DIR%\                      >nul 2>&1
echo F | xcopy /q /y %VENDOR_DIR%\%VENDOR_CIMGUI%\LICENSE-cimgui    %LIB_DIR%\                      >nul 2>&1
echo F | xcopy /q /y %VENDOR_DIR%\%VENDOR_RAYLIB%\LICENSE           %LIB_DIR%\LICENSE-raylib        >nul 2>&1
echo F | xcopy /q /y LICENSE                                        %LIB_DIR%\LICENSE-raycimgui     >nul 2>&1
