@echo off

:setabi

if "%1" equ "N32" (
    set rpg64_abi=n32
    goto setrelease
)
if "%1" equ "32" (
    set rpg64_abi=32
    goto setrelease
)
if "%1" equ "o32" (
    set rpg64_abi=32
    goto setrelease
)
if "%1" equ "O32" (
    set rpg64_abi=32
    goto setrelease
)
if "%1" equ "eabi" (
    set rpg64_abi=eabi
    goto setrelease
)
if "%1" equ "EABI" (
    set rpg64_abi=eabi
    goto setrelease
)

echo which abi? [n32/32/o32/eabi]
set /p rpg64_abi=

if %rpg64_abi% equ "n32" goto setrelease
if %rpg64_abi% equ "N32" (
    set rpg64_abi=n32
    goto setrelease
)
if %rpg64_abi% equ "o32" (
    set rpg64_abi=32
    goto setrelease
)
if %rpg64_abi% equ "O32" (
    set rpg64_abi=32
    goto setrelease
)
if %rpg64_abi% equ "eabi" goto setrelease
if %rpg64_abi% equ "EABI" (
    set rpg64_abi=eabi
    goto setrelease
)

goto setabi

:setrelease

if "%2" equ "0" (
    set rpg64_release="%2"
    goto eof
)
if "%2" equ "1" (
    set rpg64_release="%2"
    goto eof
)

echo release build? [0/1]
set /p rpg64_release=
if %rpg64_release% equ "0" (
    goto eof
)
if %rpg64_release% equ "1' (
    goto eof
)

goto setrelease

:eof

@echo on
