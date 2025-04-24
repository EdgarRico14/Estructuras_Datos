#ifndef ARBOL_H
#define ARBOL_H

#include <stdio.h>
#include <stdlib.h>
#include "Libro.h"
#include <string.h>
#include <ctype.h>
#include <math.h>


typedef struct nodo
{
	Libro *libro;
	struct nodo *izq;
	struct nodo *dch;
}Nodo;

//Estructura para busquedas exactas o aproximadas
typedef struct
{
	Nodo *menor;
	Nodo *igual;
	Nodo *mayor;
    
}Resultado;

//PROTOTIPOS CREAR ARBOLES

//ISBN
void crearArbol_ISBN(Nodo ** raiz, Libro *libro);
//TITULO
void crearArbol_Titulo(Nodo ** raiz, Libro *libro);
//AUTOR
void crearArbol_Autor(Nodo ** raiz, Libro *libro);
//FECHA
void crearArbol_Fecha(Nodo ** raiz, Libro *libro);

//PROTOTIPOS PARA REALIZAR BUSQUEDAS

//ISBN
Resultado buscarISBN(Nodo *raiz, char *isbn);
//TITULO
Resultado buscarTitulo(Nodo *raiz, char *titulo);
//AUTOR
Resultado buscarAutor(Nodo *raiz, char *autor);
//FECHA
void buscarFecha(Nodo *raiz, int fecha);

int imprimirAutor(Nodo *raiz, char *autor);
int imprimirTitulo(Nodo *raiz, char *titulo);

void subconjuntoTitulo(Nodo *raizTitulo, FiltroCHAR filtro);
void subconjuntoAutor(Nodo *raizAutor, FiltroCHAR filtro);
void subconjuntoFecha(Nodo *raizFechas, FiltroNUM filtro);



//IMPLEMENTAR LAS SIGUIENTE FUNCION
//Libera memoria de todos los nodos y asigna nulo a la raiz.
void liberar_arbol(Nodo**); 
//Elimina el arbol en postorden

Nodo *crear_nodo(Libro *libro);




#endif