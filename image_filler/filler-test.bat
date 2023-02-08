@echo off
set BAT_BASE_PATH=%~dp0
set PRJ_PATH=%BAT_BASE_PATH%\filler-test
set TARGET_PATH=%BAT_BASE_PATH%\bin
set SRC_PATH=%PRJ_PATH%\src
set INC_PATH="%PRJ_PATH%\include"
set CORE_INC_PATH="%BAT_BASE_PATH%\filler-core\include"
set RES_PATH="%PRJ_PATH%\resources"

XCOPY /E /Q /Y /I %RES_PATH% %TARGET_PATH%\resources

clang ^
    -I %INC_PATH% ^
    -I %CORE_INC_PATH% ^
    -o "%TARGET_PATH%\test.exe" "%SRC_PATH%\*.c" ^
    -L "%TARGET_PATH%" -l filler-core