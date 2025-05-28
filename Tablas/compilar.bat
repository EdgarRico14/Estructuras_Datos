@echo off
setlocal EnableExtensions EnableDelayedExpansion

:inicio
cls
echo Compilando...

gcc -std=c99 Practica9.c Hash.c Arbol.c Libro.c -o main.exe

set "UserChoice=abort"
if %ERRORLEVEL% equ 0 (
    echo Compilacion exitosa.
    pause
    :executar
    cls
    main.exe
    set /p UserChoice=" Continuar? (y/c/n): "
    if /I "!UserChoice!"=="y" goto executar
    if /I "!UserChoice!"=="c" goto inicio
    goto end
) else (
    echo Error en la compilacion.
    set /p UserChoice=" Continuar? (y/c/n): "
    if /I "!UserChoice!"=="y" goto inicio
    if /I "!UserChoice!"=="c" goto inicio
    goto end
)

:end
pause
