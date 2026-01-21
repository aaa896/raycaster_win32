@echo off
pushd "../build"
cl -Zi -nologo -fsanitize=address ../code/win32_entry.c  ../code/platform_win32.c  ../code/game_entry.c User32.lib Gdi32.lib

if %ERRORLEVEL% == 0 (
    echo Compilation Succeeded
) else (
    echo Compilation Failed
)
popd

