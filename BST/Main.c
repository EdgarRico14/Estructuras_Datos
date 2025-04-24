#include <stdio.h> 
#include <stdlib.h>


typedef struct nodo
{
    int dato;
    struct nodo *izq;
    struct nodo *dch;    
}Nodo;


Nodo *crear_nodo(int);
void insertar(Nodo**,int);
void imprimir_arbol(Nodo*, int);
void preorden(Nodo*);
void orden(Nodo*);
void orden_invertido(Nodo*);
void postorden(Nodo*);
void eliminar(Nodo**,int );

Nodo* buscar(Nodo*,int);

int main(void)
{
    Nodo *raiz = NULL;
    Nodo *resultado;
    
    insertar(&raiz,10);
    insertar(&raiz,7);
    insertar(&raiz,13);
    insertar(&raiz,14);
    insertar(&raiz,12);
    insertar(&raiz,11);
    insertar(&raiz,6);
    insertar(&raiz,8);
    insertar(&raiz,9);
    insertar(&raiz,4);
    insertar(&raiz,2);
    imprimir_arbol(raiz,0);
    eliminar(&raiz,10);
    // eliminar(&raiz,13);
    printf("\n\n"); 
    imprimir_arbol(raiz,0);
    /*
    eliminar(&raiz,2);
    eliminar(&raiz,7);
    printf("\n\n"); 
    imprimir_arbol(raiz,0);
    */
    
    /*
    printf("\n\n PREORDEN: "); 
    preorden(raiz);
    printf("\n\n ORDEN: "); 
    orden(raiz);
    printf("\n\n ORDEN INVERTIDO: "); 
    orden_invertido(raiz);
    printf("\n\n POSTORDEN: "); 
    postorden(raiz);
    printf("\n\n");   
    resultado = buscar(raiz,8);
    if(resultado)
        printf("\n Nodo encotrado %X Dato %d",resultado,resultado->dato);
    else
        printf("\n Nodo no encotrado"); 
    resultado = buscar(raiz,6);
    if(resultado)
        printf("\n Nodo encotrado %X Dato %d",resultado,resultado->dato);
    else
        printf("\n Nodo no encotrado"); 
    resultado = buscar(raiz,10);
    if(resultado)
        printf("\n Nodo encotrado %X Dato %d",resultado,resultado->dato);
    else
        printf("\n Nodo no encotrado"); 
    */
    
    printf("\n\n"); 
    
    return 0;
}

Nodo *crear_nodo(int dato)
{
    Nodo *nuevo;
    nuevo = (Nodo*) calloc(1,sizeof(Nodo));
    nuevo->dato = dato;
    return nuevo;    
}


void insertar(Nodo **raiz,int dato)
{
    if(raiz==NULL)
        return;
    if(*raiz==NULL)
    {
        *raiz = crear_nodo(dato);
        return;
    }
    if( dato < (*raiz)->dato )        
        insertar(&(*raiz)->izq,dato);
    if( dato > (*raiz)->dato )
        insertar(&(*raiz)->dch,dato);    
}

void imprimir_arbol(Nodo* nodo, int nivel)
{
    int i;
    if (nodo != NULL)
        {
        printf(" %d", nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1);
        }
    }
}

void preorden(Nodo* raiz)
{
    if(raiz == NULL)
        return;
    printf("%d ",raiz->dato);
    preorden(raiz->izq);
    preorden(raiz->dch);
}

void orden(Nodo* raiz)
{
    if(raiz == NULL)
        return;
    orden(raiz->izq);
    printf("%d ",raiz->dato);
    orden(raiz->dch);
}

void orden_invertido(Nodo* raiz)
{
    if(raiz == NULL)
        return;
    orden_invertido(raiz->dch);
    printf("%d ",raiz->dato);
    orden_invertido(raiz->izq);
}


void postorden(Nodo* raiz)
{
    if(raiz == NULL)
        return;
    postorden(raiz->izq);
    postorden(raiz->dch);
    printf("%d ",raiz->dato);
}

Nodo* buscar(Nodo* raiz,int dato)
{    
    if(raiz == NULL)
        return NULL;
    
    if(raiz->dato == dato)
    {
        return raiz;
    }
    else if(dato < raiz->dato)
    {
        return buscar(raiz->izq,dato);
    }
    else
    {
        return buscar(raiz->dch,dato);
    }
}

void eliminar(Nodo** raiz, int dato) {
    if (*raiz == NULL) return; // Árbol vacío o nodo no encontrado

    if (dato < (*raiz)->dato) {
        eliminar(&(*raiz)->izq, dato); // Buscar en el subárbol izquierdo
    } else if (dato > (*raiz)->dato) {
        eliminar(&(*raiz)->dch, dato); // Buscar en el subárbol derecho
    } else {
        // Caso 1: Nodo sin hijos (hoja)
        if ((*raiz)->izq == NULL && (*raiz)->dch == NULL) {
            free(*raiz);
        }
        // Caso 2: Nodo con un solo hijo
        else if ((*raiz)->izq == NULL) {
            Nodo* temp = *raiz;
            *raiz = (*raiz)->dch;
            free(temp);
        } else if ((*raiz)->dch == NULL) {
            Nodo* temp = *raiz;
            *raiz = (*raiz)->izq;
            free(temp);
        }
        // Caso 3: Nodo con dos hijos
        else {
            Nodo* sucesor = (*raiz)->dch;
            Nodo* padre_sucesor = *raiz;

            // Encuentra el nodo sucesor (el menor del subárbol derecho)
            while (sucesor->izq != NULL) {
                padre_sucesor = sucesor;
                sucesor = sucesor->izq;
            }

            // Reemplaza el valor del nodo a eliminar con el valor del sucesor
            (*raiz)->dato = sucesor->dato;

            // Elimina el sucesor
            if (padre_sucesor->izq == sucesor) {
                padre_sucesor->izq = sucesor->dch;
            } else {
                padre_sucesor->dch = sucesor->dch;
            }

            free(sucesor);
        }
    }
}
