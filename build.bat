@echo off
windres res.rc res.o
if ERRORLEVEL 1 pause
gcc -c *.c
IF ERRORLEVEL 1 pause
gcc -o rxe RXE.o res.o -w -s -O3
IF ERRORLEVEL 1 pause
del *.o
