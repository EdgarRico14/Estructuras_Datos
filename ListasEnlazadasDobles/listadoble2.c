#include <stdio.h>
#include <stdlib.h>
#define string_NULL "NULL"

typedef struct nodo {
    int dato;
    struct nodo *sig;
    struct nodo *ant;
} Nodo;

typedef struct lista {
    Nodo *inicio;
    int cantidad;
    int longitud;
} Lista;

Nodo* crear_nodo(int dato);
void agregar_nodo(Lista* lista, int dato);
int eliminar_nodo(Lista *lista, int pos);
void recorrer_nodos(Nodo* inicio) ;
int insertar_nodo(Lista* lista, int posicion, int dato);
void inicializar_lista(Lista *lista);
void vaciar_lista(Lista *lista);

int main(){
    
    Lista listilla;;
    inicializar_lista(&listilla);
    agregar_nodo(&listilla, 9);
    agregar_nodo(&listilla, 14);
    agregar_nodo(&listilla, 18);
    recorrer_nodos(listilla.inicio);
    insertar_nodo(&listilla, 1, 11);
    recorrer_nodos(listilla.inicio);
    eliminar_nodo(&listilla, 2);
    recorrer_nodos(listilla.inicio);
    vaciar_lista(&listilla);
}
void inicializar_lista(Lista *lista){
    lista->cantidad = 0;
    lista->longitud = 10;
    lista->inicio = NULL;
    
}
void vaciar_lista(Lista *lista) {
    Nodo *actual = lista->inicio;
    Nodo *temp;
    while (actual != NULL) {
        temp = actual;
        actual = actual->sig;
        free(temp);
    }
    inicializar_lista(lista);
}

Nodo* crear_nodo(int dato) {
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->ant = NULL;
    nuevo_nodo->dato = dato;
    nuevo_nodo->sig = NULL;
    return nuevo_nodo;
}

void agregar_nodo(Lista* lista, int dato) {
    Nodo *p = lista->inicio;
    if (lista->inicio == NULL) {
        lista->inicio = crear_nodo(dato);
        lista->cantidad++;
        return;
    }
    while (p->sig != NULL) {
        p = p->sig;
    }
    Nodo* nuevo_nodo = crear_nodo(dato);
    p -> sig = nuevo_nodo;
    nuevo_nodo -> ant = p;
    lista->cantidad++;
}

int eliminar_nodo(Lista *lista, int pos) {
    if (lista->cantidad == 0 || !(pos >= 0 && pos < lista->cantidad)) {
        return 0;
    }
    Nodo *p = lista->inicio;
    Nodo *nodo_eliminar;
    int i = 0;
    if (pos == 0) {
        lista->inicio = p->sig;
        free(p);
        p = NULL;
    } else {
        for (i = 0; i < pos - 1; i++) {
            p = p->sig;
        }
        nodo_eliminar = p->sig;
        p->sig = nodo_eliminar->sig;
        nodo_eliminar-> sig ->ant = p; 
        free(nodo_eliminar);
    }
    lista->cantidad--;
    printf(" Nodo eliminado\n");
    return 1;
}

void recorrer_nodos(Nodo* inicio) {
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
    printf("\n");
}

int insertar_nodo(Lista* lista, int posicion, int dato){
    if(!(posicion >= 0 && posicion<= lista->cantidad)){
        return 0;
    }
    Nodo *nuevo_nodo = crear_nodo(dato);
    Nodo *p;
    p = lista->inicio;
    int i = 0;
    if(posicion==0){
        nuevo_nodo -> sig = lista -> inicio;
        lista->inicio = nuevo_nodo;
        lista->cantidad+=1;
        return 1;

    }
    while(i!=posicion-1){
        p=p->sig;
        i++;
    }
    if (p->sig != NULL){
        nuevo_nodo->sig = p->sig;
        p->sig->ant = nuevo_nodo;
        p->sig = nuevo_nodo;
        nuevo_nodo -> ant = p;
    } else{
        nuevo_nodo -> ant = p;
        p -> sig = nuevo_nodo;
    }
    lista->cantidad+=1;
    return 1;

}