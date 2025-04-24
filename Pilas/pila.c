

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int dato;
    struct nodo *sig;
}Nodo;


typedef struct pila{
    Nodo *cima;
    int tam;
    int longitud_nodos;
}Pila;

int vacia(Pila *pila);
int llena(Pila* pila);

int main(void){
    
    Pila pila = {NULL,6,0};


    if(vacia(&pila)) 
        printf("\n Pila vacia");
}

int vacia(Pila *pila){
    return (pila->cima == NULL);
}

int llena(Pila* pila){
    return (pila->tam == pila->longitud_nodos);
}

void push(Pila* pila, int dato){
    if(llena(pila)){
        //overflow
        printf("Overflow\n");
        return;
    }
    Nodo* nodo = crear_nodo(dato);
    nodo->sig = pila->cima; 
    pila->cima = nodo; 
    pila->longitud_nodos++;

}

Nodo* pop(Pila* pila){
    if(vacia(pila)){
        //underflow 
        printf("Underflow\n");
        return NULL;
    }
    Nodo* aux = pila->cima;
    pila->cima = pila->cima->sig;
    pila->longitud_nodos--;
    return aux;
}

Nodo* peek(Pila* pila){
    return pila->cima;
}

void pushNodo(Pila* pila, Nodo* nodo){
    if(llena(pila)){
        //overflow
        printf("Overflow\n");
        return NULL;
    }
    nodo->sig = pila->cima;
    pila->cima = nodo;
    pila->longitud_nodos++;
}

void mostrar(Pila* pila){

}

int comparar(Pila* a,Pila* b)
{
	if(a->longitud_nodos != b->longitud_nodos)
		return 0;
	int son_iguales;
	Pila aux_a = {NULL,a->tam,0};
	Pila aux_b = aux_a;
	
	Nodo *nodo_a,*nodo_b;
	son_iguales = 1;
	while(!vacia(a))
	{
		nodo_a = pop(a);
		nodo_b = pop(b);
		push_nodo(&aux_a,nodo_a);
		push_nodo(&aux_b,nodo_b);
		if( nodo_a->dato !=nodo_b->dato)
		{
			son_iguales = 0;
			break;
		}
	}
	
	while(!vacia(&aux_a))
	{
		nodo_a = pop(&aux_a);
		nodo_b = pop(&aux_b);
		push_nodo(a,nodo_a);
		push_nodo(b,nodo_b);
	}
	return son_iguales;
	
}

void vaciarPila(Pila* pila){
    
    while(!vacia(&pila)){
        free(pop(&pila));
    }


}

Nodo* crear_nodo(int dato){
    Nodo *nuevo = (Nodo*)calloc(1, sizeof(Nodo));
    nuevo->dato = dato;
    nuevo->sig = NULL;
    return nuevo;
}
