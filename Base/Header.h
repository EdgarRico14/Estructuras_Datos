#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMO 1
#define MINIMO 0
#define TEXT_MAX 256


typedef struct
{
	char *nombre;
	int paginas;
	char *autor;	
}Documento;

typedef struct nodo
{
	Documento documento;
	struct nodo *izq;
	struct nodo *dch;	
}Nodo;

typedef struct
{
	Nodo **nodos;
	int cantidad;
	int tipo;
}Monton;

void limpiar_buffer(void);
void reemplazar(char *,char ,char );
void setup_buffer(char *);
char *captura_cadena(void);
void liberar_cadenas(Documento*);
void menu();
Nodo*crear_nodo(Documento);
void liberar_nodo(Nodo*);
void realizar_operacion(Monton *, int);
void mostrar_cola(Monton *);
void push_Heap(Monton *, Documento);
void pop_Heap(Monton *);
void heapify(Monton *);
void heapify_minimo(Monton *, int);
void heapify_maximo(Monton *, int);
void invertir_heap(Monton *);
void liberar_heap(Monton *);
void imprimir_heap(Monton *);
void imprimir_arbol(Nodo *, int);
void enlazar_nodos(Monton *);




#endif