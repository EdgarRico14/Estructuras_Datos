#include <stdio.h>
#include <stdlib.h>

#define VERDADERO 1
#define FALSO 0

typedef struct nodo {
    int dato;
    struct nodo *siguiente;
} Nodo;

void insertar_nodo(Nodo **, int);
void crear_nodo(Nodo **, int);
void recorrer_nodos(Nodo *);
int eliminar_nodo_final(Nodo **);

int main(void) {

    Nodo *inicio_lista = NULL;
    insertar_nodo(&inicio_lista, 1);
    insertar_nodo(&inicio_lista, 2);
    insertar_nodo(&inicio_lista, 3);
    insertar_nodo(&inicio_lista, 4);
    recorrer_nodos(inicio_lista);
    eliminar_nodo_final(&inicio_lista);

    return 0;
}

void insertar_nodo(Nodo **inicio, int dato) {
    if (*inicio == NULL) {
        crear_nodo(inicio, dato);
    } else {
        Nodo *nuevo_nodo = NULL;
        crear_nodo(&nuevo_nodo, dato);
        Nodo *p = *inicio;

        while (p->siguiente != NULL) {
            p = p->siguiente;
        }
        p->siguiente = nuevo_nodo;
    }
}

void crear_nodo(Nodo **nodo, int valor) {
    (*nodo) = (Nodo *)malloc(sizeof(Nodo));
    (*nodo)->dato = valor;
    (*nodo)->siguiente = NULL;
}

void recorrer_nodos(Nodo *inicio) {
    Nodo *p = inicio;
    if (p != NULL) {
        while (p != NULL) {
            printf("%d", p->dato);
            p = p->siguiente;
            if (p != NULL) {
                printf("-> ");
            }
        }
        printf("\n");
    }
}

int eliminar_nodo_final(Nodo **inicio) {
    Nodo *p, *q;
    q = NULL;
    p = *inicio;
    if (p != NULL) {
        while (p->siguiente != NULL) {
            q = p;
            p = p->siguiente;
        }
        if (q != NULL) {
            q->siguiente = NULL;
            free(p);
            p = NULL;
        } else {
            free(p);
            *inicio = NULL;
        }
        recorrer_nodos(inicio);
        return VERDADERO;
    }
    return FALSO;
}


