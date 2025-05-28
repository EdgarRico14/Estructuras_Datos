#ifndef ARBOL_H
#define ARBOL_H

#include "Libro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo
{
	Libro *libro;
	struct nodo *izq;
	struct nodo *dch;
}Nodo;


//PROTOTIPOS AGREGAR DATOS AL LOS ARBOLES
// Autor inicial rango
void insertar_arbolAutor(Nodo **raiz, Libro *book);
// Titulo incial rango
void insertar_arbolTitulo(Nodo **raiz, Libro *book);
// Fecha rango
void insertar_arbolFecha(Nodo **raiz, Libro *book);
//IMPLEMENTAR LAS SIGUIENTE FUNCION
//Libera memoria de todos los nodos y asigna nulo a la raiz.
Nodo* crear_nodo(Libro *book);
void liberar_arbol(Nodo**);
void inorden(Nodo *raiz);



#endif