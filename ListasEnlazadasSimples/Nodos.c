#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int dato;
    struct nodo *siguiente;
}Nodo;


Nodo *crear_nodo(int);
void agregar_nodo(Nodo**, int);

void recorrer (Nodo* inicio);

int main(void){
    Nodo *inicio;
    inicio = NULL;
    //inicio = crear_nodo(4);
    agregar_nodo(&inicio, 8);

    recorrer(inicio);
    printf("\n\n");

    return 0;
}
Nodo* crear_nodo(int dato){
    Nodo* nuevo_nodo;
    nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo -> dato = dato;
    nuevo_nodo -> siguiente = NULL;
    return nuevo_nodo;
}


void agregar_nodo(Nodo** inicio, int dato){
    Nodo *p;
    p = *inicio;
    if(*inicio == NULL){
        *inicio = crear_nodo(dato);
        return;
    }

    while(p->siguiente!=NULL){
        p = p -> siguiente; 
    }
    p->siguiente = crear_nodo(dato);
}

void recorrer(Nodo* inicio){
    Nodo *p = inicio;
    if(p!=NULL){
        while (p!=NULL){
            printf("%d ",p->dato);
            p = p-> siguiente;
            if(p!=NULL){
                printf("->");
            }
        }
    }
}
