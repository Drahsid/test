@echo off
ssh %rpg64_ssh_user%@%rpg64_ssh_hostname% "cd ~/rpg64;make clean"
echo CLEAN

if "%1"=="1" (
    @echo on
)
