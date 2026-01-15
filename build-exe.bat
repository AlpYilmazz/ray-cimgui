@echo off
SETLOCAL

set ARG_ENTRY=%1
SHIFT

:loop
if NOT "%1"=="" (
    if "%1"=="--out" (
        SET ARG_OUTPUT=%2
        SHIFT
    )
    SHIFT
    goto :loop
)

set CC=gcc

set COMPILER_FLAGS=-std=c11

set INCLUDE=^
    -Ivendor/raylib-5.0/include ^
    -Iraycimgui/include
set LIB=^
    -Lvendor/raylib-5.0/lib ^
    -Lraycimgui/lib

set LINK=^
    -Wl,--start-group ^
    -lraylib ^
    -lcimgui ^
    -lraycimgui ^
    -lgdi32 -lwinmm ^
    -lws2_32 ^
    -Wl,--end-group

set SRC_DIR=.

if defined ARG_OUTPUT (
    set OUTPUT=%ARG_OUTPUT%
) else (
    set OUTPUT=out.exe
)

set COMPILE=%SRC_DIR%/%ARG_ENTRY%

@echo on
%CC% %COMPILER_FLAGS% %COMPILE% %INCLUDE% %LIB% %LINK% -o %OUTPUT%
@echo off
