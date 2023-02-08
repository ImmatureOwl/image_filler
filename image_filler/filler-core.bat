@echo off
set BAT_BASE_PATH=%~dp0
set PRJ_PATH=%BAT_BASE_PATH%\filler-core
set TARGET_PATH=%BAT_BASE_PATH%\bin
set SRC_PATH=%PRJ_PATH%\src
set INC_PATH="%PRJ_PATH%\include"

if exist "%TARGET_PATH%" (
    RD /S /Q "%TARGET_PATH%"
)

MD "%TARGET_PATH%"

clang ^
    -I %INC_PATH% ^
    -o "%TARGET_PATH%\filler-core.lib" "%SRC_PATH%\*.c" -fuse-ld=llvm-lib