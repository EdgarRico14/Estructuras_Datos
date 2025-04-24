#include <stdio.h>
#include <stdlib.h>
#define VALIDO 1
#define INVALIDO 0

typedef struct nodo {
    int dato;
    struct nodo *siguiente;
} Nodo;

typedef struct lista {
    Nodo *inicio;
    int cantidad;
    int longitud;
} Lista;

Nodo *crear_nodo(int);
void agregar_nodo(Lista*, int);
int insertar_nodo(Lista*, int, int);
int eliminar_nodo(Lista*, int);
void recorrer(Lista*);

int main(void) {
    Lista *listilla = (Lista*)malloc(sizeof(Lista));
    listilla->cantidad = 0;
    listilla->longitud = 10;
    listilla->inicio = NULL;

    agregar_nodo(listilla, 1);
    agregar_nodo(listilla, 3);
    insertar_nodo(listilla, 2, 9);
    recorrer(listilla);
    printf("\n");

    eliminar_nodo(listilla, 2);
    recorrer(listilla);
    printf("\n");

    free(listilla);
    return 0;
}

Nodo* crear_nodo(int dato) {
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->dato = dato;
    nuevo_nodo->siguiente = NULL;
    return nuevo_nodo;
}


void agregar_nodo(Lista* lista, int dato) {
    Nodo *p = lista->inicio;
    if (lista->inicio == NULL) {
        lista->inicio = crear_nodo(dato);
        lista->cantidad++;
        return;
    }

    while (p->siguiente != NULL) {
        p = p->siguiente;
    }
    p->siguiente = crear_nodo(dato);
    lista->cantidad++;
}

void recorrer(Lista* lista) {
    Nodo *p = lista->inicio;
    while (p != NULL) {
        printf("%d ", p->dato);
        p = p->siguiente;
        if (p != NULL) {
            printf("-> ");
        }
    }
    printf("\nCantidad de nodos: %d\n", lista->cantidad);
}

int insertar_nodo(Lista* lista, int posicion, int dato) {
    if (!(posicion >= 0 && posicion <= lista->cantidad)) {
        return INVALIDO;
    }
    Nodo *nuevo_nodo = crear_nodo(dato);
    Nodo *p = lista->inicio;
    int i = 0;
    if (posicion == 0) {
        nuevo_nodo->siguiente = lista->inicio;
        lista->inicio = nuevo_nodo;
    } else {
        for (i = 0; i < posicion - 1; i++) {
            p = p->siguiente;
        }
        nuevo_nodo->siguiente = p->siguiente;
        p->siguiente = nuevo_nodo;
    }
    lista->cantidad++;
    return VALIDO;
}

int eliminar_nodo(Lista* lista, int posicion) {
    if (lista->cantidad == 0 || !(posicion >= 0 && posicion < lista->cantidad)) {
        return INVALIDO;
    }
    Nodo *p = lista->inicio;
    Nodo *nodo_eliminar;
    int i = 0;

    if (posicion == 0) {
        lista->inicio = p->siguiente;
        free(p);
    } else {
        for (i = 0; i < posicion - 1; i++) {
            p = p->siguiente;
        }
        nodo_eliminar = p->siguiente;
        p->siguiente = nodo_eliminar->siguiente;
        free(nodo_eliminar);
    }
    lista->cantidad--;
    printf("Nodo eliminado\n");
    return VALIDO;
}
