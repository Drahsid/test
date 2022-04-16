@echo off

rem @echo off
set TARGET_DRIVE=f:
set ROM_NAME=rpg64_%rpg64_abi%.z64
set Lv1dRdR4bMcK=%cd:~0,2%

if %rpg64_abi%==32 (
    set ROM_NAME=rpg64_o32.z64
)

del %TARGET_DRIVE%\%ROM_NAME%
copy build\%ROM_NAME% %TARGET_DRIVE%\%ROM_NAME%

%TARGET_DRIVE%
cls
%USB64_DIR%/unfloader.exe -r %ROM_NAME% -d -h 24
%Lv1dRdR4bMcK%

@echo on
