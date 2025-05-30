
setlocal EnableExtensions EnableDelayedExpansion
:inicio
cls
@echo on
gcc -std=c99 Tree.c -o main.exe
@echo off
set "UserChoice=abort"
if %ERRORLEVEL% equ 0 (
    echo Compilacion exitosa.
	pause
	:executar
	cls
	main.exe	
	set /p UserChoice="Continuar? (y/c/n) "
	if /I "!UserChoice!"=="y" goto executar
	if /I "!UserChoice!"=="c" goto inicio
	goto end

)else (
    @echo on
    echo Error en compilacion.
	set /p UserChoice="Continuar? (y/c/n) "
	if /I "!UserChoice!"=="y" goto inicio
	if /I "!UserChoice!"=="c" goto inicio
	goto end
)
:end
pause