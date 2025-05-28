#ifndef HASH_H
#define HASH_H

#include "Libro.h"
#include "Arbol.h"
#include <math.h>
#include <string.h>


#define ISBN 0
#define TITULO 1
#define AUTOR 2
#define FECHA 3
#define TITULO_INICIAL 4
#define AUTOR_INICIAL 5 

typedef struct
{
	int size;
	int stored;
	char key;
	Libro **books; 
	unsigned int *indices; 
	int (*folding)(char*);
}HashTable;

int folding_cadena(char*);
int folding_inicial(char*);
HashTable* crear_tabla(char,int (*folding)(char*));
float factor(HashTable);
int hash(HashTable,int);
int rehash(HashTable,int,int);
int get_key(HashTable *,Libro *);
void insertar_indices(HashTable **hashtable, int index);
void insertar(HashTable **hashtable, Libro* book);
void insertar_book(HashTable**,Libro*);
void eliminar_libro_tabla(HashTable **tabla, Libro *book);
void eliminar_book(HashTable **tablaISBN, HashTable **tablaTitulo, HashTable **tablaTituloInicial, 
                   HashTable **tablaAutor, HashTable **tablaAutorInicial, HashTable **tablaFecha, 
                   char *isbn, Libro *libros);
void liberar_hash(HashTable **tabla);
HashTable* remap(HashTable*);
Libro* buscar_por_isbn(HashTable *tablaISBN, char *isbn);
Libro* buscar_por_titulo(HashTable *tablaTitulo, char *titulo);
void buscar_por_autor(HashTable **hashtable, Nodo **raiz, char *autor);	
void rango_por_iniciales(HashTable **hashtable, Nodo **raiz, char inicial);
void rango_por_fechas(HashTable **hashtable, Nodo **raiz, int fecha);


#endif