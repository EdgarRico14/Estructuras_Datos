#include "Arbol.h"

Nodo* crear_nodo(Libro *book) {
    Nodo* nuevo = (Nodo*) calloc(1, sizeof(Nodo));
	nuevo->libro = book;
	return nuevo;
}



void insertar_arbolTitulo(Nodo **raiz,Libro *libro){
	if (raiz == NULL)
		return;

	if (*raiz == NULL) {
		(*raiz) = crear_nodo(libro);
		return;
	}

	int cmp = strcasecmp(libro->titulo, (*raiz)->libro->titulo);

	if (cmp < 0)
		insertar_arbolTitulo(&(*raiz)->izq, libro);
	else if (cmp > 0)
		insertar_arbolTitulo(&(*raiz)->dch, libro);
	else {
		if (libro->fecha <= (*raiz)->libro->fecha) {
			insertar_arbolTitulo(&(*raiz)->izq, libro);
		}else {
			insertar_arbolTitulo(&(*raiz)->dch, libro);
		}
	}
}

void insertar_arbolAutor(Nodo **raiz,Libro *libro){
	if (raiz == NULL)
		return;

	if (*raiz == NULL) {
		(*raiz) = crear_nodo(libro);
		return;
	}

	int cmp = strcasecmp(libro->autor, (*raiz)->libro->autor);

	if (cmp < 0)
		insertar_arbolAutor(&(*raiz)->izq, libro);
	else if (cmp > 0)
		insertar_arbolAutor(&(*raiz)->dch, libro);
	else {
		if (libro->fecha <= (*raiz)->libro->fecha) {
			insertar_arbolAutor(&(*raiz)->izq, libro);
		}else {
			insertar_arbolAutor(&(*raiz)->dch, libro);
		}
	}
}

void insertar_arbolFecha(Nodo **raiz,Libro *libro){
	if (raiz == NULL)
		return;

	if (*raiz == NULL) {
		(*raiz) = crear_nodo(libro);
		return;
	}
    if(libro->fecha < (*raiz)->libro->fecha){
        insertar_arbolFecha(&(*raiz)->izq, libro);
    }else if(libro->fecha > (*raiz)->libro->fecha){
        insertar_arbolFecha(&(*raiz)->dch, libro);
    }
    else{
        if(strcmp(libro->titulo, (*raiz)->libro->titulo) <= 0){
            insertar_arbolFecha(&(*raiz)->izq, libro);
        }else{
            insertar_arbolFecha(&(*raiz)->dch, libro);
        }
    }
}

void inorden(Nodo *raiz) {
    if (raiz == NULL) return;
    
    inorden(raiz->izq);
    printf("\n ");
    imprimir(*(raiz->libro));
    inorden(raiz->dch);
}

void liberar_arbol(Nodo **raiz)
{
	if(*raiz == NULL)
		return;
	liberar_arbol(&(*raiz)->izq);
	liberar_arbol(&(*raiz)->dch);
	free(*raiz);
	*raiz = NULL;
}


