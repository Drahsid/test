@echo off
ssh %rpg64_ssh_user%@%rpg64_ssh_hostname% "cd ~/rpg64;make ultralib clean ABI=%rpg64_abi% RELEASE_BUILD=%rpg64_release%;make ultralib distclean ABI=%rpg64_abi% RELEASE_BUILD=%rpg64_release%;make ultralib ABI=%rpg64_abi% RELEASE_BUILD=%rpg64_release% USE_MODERN_GCC=1 -j"
echo ULTRALIB

if "%1"=="1" (
    @echo on
)
