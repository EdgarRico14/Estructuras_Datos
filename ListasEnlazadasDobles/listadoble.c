#include <stdio.h>
#include <stdlib.h>
#define string_NULL "NULL"

typedef struct nodo {
    int dato;
    struct nodo* ant;
    struct nodo* sig;
} Nodo;

void crear_nodo(Nodo **nodo, int dato) {
    *nodo = (Nodo *)malloc(sizeof(Nodo));
    if (*nodo != NULL) {
        (*nodo)->ant = NULL;
        (*nodo)->dato = dato;
        (*nodo)->sig = NULL;
    }
}

void insertar_nodo(Nodo **inicio, int dato) {
    if (*inicio == NULL) {
        crear_nodo(inicio, dato);
    } else {
        Nodo *nuevo_nodo;
        crear_nodo(&nuevo_nodo, dato);
        if (nuevo_nodo != NULL) {
            Nodo *p = *inicio;
            while (p->sig != NULL) {
                p = p->sig;
            }
            nuevo_nodo->ant = p;
            p->sig = nuevo_nodo;
        }
    }
}


int eliminar_nodo_final(Nodo **inicio) {
    Nodo *p = *inicio, *q = NULL;
    if (p == NULL) {
        return 0;
    }
    while (p->sig != NULL) {
        q = p;
        p = p->sig;
    }
    if (q != NULL) {
        q->sig = NULL;
    } else {
        *inicio = NULL;
    }
    free(p);
    return 1;
}


void recorrer_nodos(Nodo *inicio) {
    Nodo *p = inicio;
    if (p == NULL) {
        // VERIFICAR QUE LA LISTA NO ESTE VACIA
        printf("\n\r %s", string_NULL);
        return;
    }
    while (p != NULL) {
        // ITERAR LA LISTA HASTA LLEGAR AL ULTIMO NODO
        printf("\n\r ");
        (p->ant) ? printf("%08x <- ant | | ", p->ant) : printf("%s <- ant | | ", string_NULL);
        printf("Direccion: %08x - ", p);
        printf("Dato: %3d | | ", p->dato);
        (p->sig) ? printf("sig -> %08x ", p->sig) : printf("sig -> %s ", string_NULL);
        p = p->sig;
    }
}

int main() {
    Nodo *inicio_lista = NULL;
    insertar_nodo(&inicio_lista, 4);
    insertar_nodo(&inicio_lista, 8);
    insertar_nodo(&inicio_lista, 9);
    recorrer_nodos(inicio_lista);
    eliminar_nodo_final(&inicio_lista);
    printf("\n");
    recorrer_nodos(inicio_lista);
    return 0;
}
