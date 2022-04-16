@echo off
ssh %rpg64_ssh_user%@%rpg64_ssh_hostname% "cd ~/rpg64;make ABI=%rpg64_abi% RELEASE_BUILD=%rpg64_release% -j"
echo MAKE

if "%1"=="1" (
    @echo on
)
