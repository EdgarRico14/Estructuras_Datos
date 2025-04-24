#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int dato;
    struct nodo* siguiente;
}Nodo;

typedef struct {
    Nodo* inicio;
    Nodo* fin;
    int cantidadNodos;
}Cola;

void inicializar(Cola* );
int vacia(Cola);
void insertar(Cola *, int);
int* peek(Cola);
Nodo* sacar(Cola*);
Nodo* crear_nodo(int);

void insertar_ordenado(Cola* cola, int dato) {
    Cola aux;
    inicializar(&aux);
    Nodo* temp;
    int insertado = 0;

    // Recorremos la cola original
    while (!vacia(*cola)) {
        temp = sacar(cola);
        
        // Insertamos el nuevo dato en su posición correcta
        if (!insertado && temp->dato > dato) {
            insertar(&aux, dato);
            insertado = 1;
        }

        insertar(&aux, temp->dato);
    }

    // Si el dato es el mayor, se inserta al final
    if (!insertado) {
        insertar(&aux, dato);
    }

    // Restauramos la cola original con los datos ordenados
    *cola = aux;
}

void insertar(Cola *cola, int dato){

    if (llena(cola)){
        printf("Overflow\n");
        return;
    }
    Nodo *nodo = crear_nodo(dato);
    if(vacia(*cola)){
        cola->inicio = nodo;
        cola->fin = nodo;
    }else{
        cola->fin->siguiente = nodo;
        cola->fin = nodo;
    }
    cola->cantidadNodos++;

}

