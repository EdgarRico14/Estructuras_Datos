#ifndef LIBRO_H
#define LIBRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define CANT_LIBROS 50
#define MAX_ISBN 20
#define MAX_TITULO 45
#define MAX_AUTOR 30


typedef struct
{
    char isbn[MAX_ISBN];   //International Standard Book Number
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int fecha;
    int disponible;
}Libro;

typedef struct
{
	int min;
	int max;
}FiltroNUM;

typedef struct
{
	char min;
	char max;

}FiltroCHAR;

Libro* obtener_libros(void);
void imprimir(Libro);
int captura_FiltroNUM(FiltroNUM*);
int captura_FiltroCHAR(FiltroCHAR*);
void menu();

#endif