#include <stdio.h>
#include <stdlib.h>
#define VALIDO 1
#define INVALIDO 0

typedef struct nodo{
    int dato;
    struct nodo *siguiente;
} Nodo;

typedef struct lista{
    Nodo *inicio;
    int cantidad;
    int longitud;
} Lista;

Nodo *crear_nodo(int);
void agregar_nodo(Lista*, int);
int insertar_nodo(Lista*, int, int);
int eliminar_nodo(Lista*, int);
void recorrer(Nodo* inicio);

int main(void){
    Lista listilla;
    listilla.cantidad = 0;
    listilla.longitud = 10;
    listilla.inicio = NULL;

    agregar_nodo(&listilla, 8);
    insertar_nodo(&listilla, 0, 10);
    eliminar_nodo(&listilla, 1);
    recorrer(listilla.inicio);
    printf("\n\n");

    return 0;
}

Nodo* crear_nodo(int dato){
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->dato = dato;
    nuevo_nodo->siguiente = NULL;
    return nuevo_nodo;
}

void agregar_nodo(Lista* lista, int dato){
    Nodo *p = lista->inicio;
    if(lista->inicio == NULL){
        lista->inicio = crear_nodo(dato);
        lista->cantidad += 1;
        return;
    }

    while(p->siguiente != NULL){
        p = p->siguiente;
    }
    p->siguiente = crear_nodo(dato);
    lista->cantidad += 1;
}

void recorrer(Nodo* inicio){
    Nodo *p = inicio;
    while(p != NULL){
        printf("%d ", p->dato);
        p = p->siguiente;
    }
}

int insertar_nodo(Lista* lista, int posicion, int dato){
    if(!(posicion >= 0 && posicion <= lista->cantidad)){
        return INVALIDO;
    }
    Nodo *nuevo_nodo = crear_nodo(dato);
    Nodo *p = lista->inicio;
    int i = 0;
    if(posicion == 0){
        nuevo_nodo->siguiente = lista->inicio;
        lista->inicio = nuevo_nodo;
        lista->cantidad += 1;
        return VALIDO;
    }
    while(i != posicion - 1){
        p = p->siguiente;
        i++;
    }
    nuevo_nodo->siguiente = p->siguiente;
    p->siguiente = nuevo_nodo;
    lista->cantidad += 1;
    return VALIDO;
}

int eliminar_nodo(Lista* lista, int posicion){
    if(lista->cantidad == 0 || !(posicion >= 0 && posicion < lista->cantidad)){
        return INVALIDO;
    }
    int i = 0;
    Nodo *p = lista->inicio;
    Nodo *nodo_eliminar;
    if(posicion == 0){
        lista->inicio = p->siguiente;
        free(p);
        lista->cantidad -= 1;
        return VALIDO;
    }
    while(i != posicion - 1){
        p = p->siguiente;
        i++;
    }
    nodo_eliminar = p->siguiente;
    p->siguiente = nodo_eliminar->siguiente;
    free(nodo_eliminar);
    lista->cantidad -= 1;
    return VALIDO;
}
