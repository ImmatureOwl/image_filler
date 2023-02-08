@echo off
set BAT_BASE_PATH=%~dp0
set PRJ_PATH=%BAT_BASE_PATH%\filler-app
set TARGET_PATH=%BAT_BASE_PATH%\bin
set SRC_PATH=%PRJ_PATH%\src
set INC_PATH="%PRJ_PATH%\include"
set CORE_INC_PATH="%BAT_BASE_PATH%\filler-core\include"

clang ^
    -I %INC_PATH% ^
    -I %CORE_INC_PATH% ^
    -o "%TARGET_PATH%\app.exe" "%SRC_PATH%\*.c" ^
    -L "%TARGET_PATH%" -l filler-core