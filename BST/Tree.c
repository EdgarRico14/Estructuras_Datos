#include <stdio.h> 
#include <stdlib.h>
#include <math.h>


typedef struct nodo
{
    int cantidad_nodos;
    int dato;
    struct nodo *izq;
    struct nodo *dch;    
}Nodo;

Nodo *crearNodo(int);
void insertar(Nodo **,int);
int eliminar(Nodo**, int);
void eliminarPostorden(Nodo**);
int sumaDatos(Nodo *);
int estructura(Nodo *, Nodo*);
int profundidades(Nodo *);
void guardarOrden(Nodo*, int *, int *);
void eliminarPostorden(Nodo**);
void menu();
void imprimir_arbol(Nodo*, int);
void balancear(Nodo **, int *, int, int);
int estaEquilibrado(Nodo *);
int contarNodos(Nodo *);

int main(){
    
    Nodo *raizA = NULL;
    Nodo *raizB = NULL;
    int valorA, valorB, opc = 0, iA = 0, iB = 0;

    do{ 
        menu();
        scanf(" %d", &opc);
        switch (opc)
        {
        case 1:
            
            do{ 
                printf("Ingresa valor entero para insertar en Arbol A ((-1) para detenerse): ");
                scanf(" %d", &valorA);
                if(valorA != -1){
                    insertar(&raizA, valorA);
                    if (raizA->dato)
                        printf("Dato ingresado correctamente\n");
                    else   
                        printf("Dato no registrado\n");
                }    
            }while(valorA != -1);
            printf("\nDatos registrados\n");
            break;
        case 2:

            do{ 
                printf("Ingresa valor entero para insertar en Arbol B ((-1) para detenerse): ");
                scanf(" %d", &valorB);
                if(valorB != -1){
                    insertar(&raizB, valorB);
                    if (raizB->dato)
                        printf("Dato ingresado correctamente\n");
                    else   
                        printf("Dato no registrado\n");
                }
            }while(valorB != -1);
            printf("\nDatos registrados\n");
            break;

        case 3:{
            if(!raizA || !raizB){
                printf("No se puede comparar arboles\n");
                break;
            } 

            int sumaA = sumaDatos(raizA);
            int sumaB = sumaDatos(raizB);
            int mismaEstructura = estructura(raizA, raizB);

            printf("\n\n==== COMPARACION ARBOLES =====\n");
            if ((sumaA == sumaB) && mismaEstructura){
                printf("Datos iguales\n");
                printf("Misma estructura\n");

            }else if((sumaA != sumaB) && mismaEstructura){
                printf("Datos diferentes\n");
                printf("Misma estructura\n");
            }
            else if((sumaA == sumaB) && !mismaEstructura){
                printf("Datos iguales\n");
                printf("Diferente estructura\n");
            }
            else if((sumaA != sumaB) && !mismaEstructura){
                printf("Datos diferentes\n");
                printf("Diferente estructura\n");
            }
            
            break;
        }
        case 4:{
            if(!raizA){
                printf("Arbol A no disponible\n");
                break;
            }
            int A;
            printf("\nIngresa dato a eliminar en Arbol A: ");
            scanf(" %d", &A);
            if (eliminar(&raizA, A)) {
                printf("\nDato eliminado\n");
                raizA->cantidad_nodos = contarNodos(raizA);
            } else {
                printf("\nDato no encontrado\n");
            }

            break;
        }
        case 5:{
            if(!raizB){
                printf("Arbol B no disponible\n");
                break;
            }
            int B;
            printf("\nIngresa dato a eliminar en Arbol B: ");
            scanf(" %d", &B);
            if (eliminar(&raizB, B)) {
                printf("\nDato eliminado\n");
                raizB->cantidad_nodos = contarNodos(raizB);
            } else {
                printf("\nDato no encontrado\n");
            }
            break;
        }
        case 6:{
            int profA = profundidades(raizA);
            int profB = profundidades(raizB);
            printf("\n\n==== PROFUNDIDADES DE LOS ARBOLES ====\n");
            printf("Produndidad de A: %d\n", profA);
            printf("Produndidad de B: %d\n", profB);
            break;
        }
        case 7:{
            if(raizA){
                if(!estaEquilibrado(raizA)){
                    printf("Arbol A: Esta desequilibrado\n");
                    int nodosA = raizA->cantidad_nodos;
                    int *arregloA = (int *)calloc(nodosA, sizeof(int));
                    iA = 0;
                    guardarOrden(raizA, &iA, arregloA);
                    eliminarPostorden(&raizA);

                    balancear(&raizA, arregloA, 0, nodosA-1);
                    free(arregloA);

                    if(estaEquilibrado(raizA)){
                        printf("El arbol A se equilibro correctamente\n");
                    }
                } else {
                    printf("\nEl arbol A ya esta equilibrado\n");
                }
            }
            if(raizB){
                if(!estaEquilibrado(raizB)){
                    printf("Arbol B: Esta desequilibrado\n");
                    int nodosB = raizB->cantidad_nodos;
                    int *arregloB = (int *)calloc(nodosB, sizeof(int));
                    iB = 0;
                    guardarOrden(raizB, &iB, arregloB); 
                    eliminarPostorden(&raizB);

                    balancear(&raizB, arregloB, 0, nodosB-1);
                    free(arregloB);

                    if(estaEquilibrado(raizB)){
                        printf("El arbol B se equilibro correctamente\n");
                    }
                }else {
                    printf("\nEl arbol B ya esta equilibrado\n");
                }
            }
            
            break;
        }
        case 8:
            printf("\n\n ==== Arbol A ====\n");
            if(raizA)
                imprimir_arbol(raizA,0);
            else
                printf("Arbol A no disponible\n");

            printf("\n\n\n ==== Arbol B ====\n");
            if(raizB)
                imprimir_arbol(raizB,0);
            else
                printf("Arbol B no disponible\n");

            break;

        case 9:
            printf("\nTerminando programa\n");
            break;
        default:
            printf("\nIngresa opcion valida\n");
            break;
        }

    }while(opc!=9);

    if(raizA){
        eliminarPostorden(&raizA);
        if(!raizA)
            printf("Arbol A: Memoria liberada correctamente\n");
        else
            printf("Arbol A: Memoria no se libero correctamente\n");
    
    }else{
        printf("Arbol A no disponible\n");
    }

    if(raizB){
        eliminarPostorden(&raizB);
        if(!raizB)
            printf("Arbol B: Memoria liberada correctamente\n");
        else
            printf("Arbol B: Memoria no se libero correctamente\n");

    }else{
        printf("Arbol B no disponible\n");
    }

    return 0;
}

void insertar(Nodo **raiz,int dato)
{
    
    if(*raiz==NULL)
    {
        *raiz = crearNodo(dato);
        return;
    }
    
    if (dato == (*raiz)->dato)
        return;
    
    if( dato < (*raiz)->dato )        
    insertar(&(*raiz)->izq,dato);
    
    if( dato > (*raiz)->dato )
    insertar(&(*raiz)->dch,dato);    
    
    (*raiz)->cantidad_nodos = contarNodos(*raiz);
}

int eliminar(Nodo** raiz, int dato) {
    if (*raiz == NULL) return 0; 
    
    if (dato < (*raiz)->dato) {
        eliminar(&(*raiz)->izq, dato); 
    } else if (dato > (*raiz)->dato) {
        eliminar(&(*raiz)->dch, dato); 
    } else {
        // Caso 1: Nodo sin hijos (hoja)
        if ((*raiz)->izq == NULL && (*raiz)->dch == NULL) {
            free(*raiz);
            *raiz = NULL;
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
            Nodo* anterior_sucesor = *raiz;

            while (sucesor->izq != NULL) {
                anterior_sucesor = sucesor;
                sucesor = sucesor->izq;
            }

            (*raiz)->dato = sucesor->dato;
           
            if (anterior_sucesor->izq == sucesor) {
                anterior_sucesor->izq = sucesor->dch;
            } else {
                anterior_sucesor->dch = sucesor->dch;
            }
            
            free(sucesor);
        }
        
        return 1;
    }
} 

int contarNodos(Nodo *raiz) {
    if (raiz == NULL) 
        return 0;

    return contarNodos(raiz->izq) + contarNodos(raiz->dch) + 1;
}


int sumaDatos(Nodo *raiz){
    if(raiz!=NULL){
        int izq = sumaDatos(raiz->izq);
        int der = sumaDatos(raiz->dch);
        return izq + der + raiz->dato;
    }
    return 0;
}

int estructura(Nodo *raizA, Nodo* raizB){

    if(!raizA && !raizB)
        return 1;
    
    if((!raizA && raizB) || (raizA && !raizB))
        return 0;
   
    int izquierda = estructura(raizA->izq, raizB->izq);
    int derecha = estructura(raizA->dch, raizB->dch);

    return izquierda && derecha;
}

int profundidades(Nodo *raiz){
    if(raiz!=NULL){
        int x = profundidades(raiz->izq);
        int y = profundidades(raiz->dch);
        if(x>y){
            return x + 1;
        }else{
            return y + 1;
        }
    }
    return 0;
}

void balancear(Nodo **raiz, int *arreglo, int inicio, int fin) {
    if (inicio > fin) return; 
    
    int medio = (inicio + fin) / 2;

    if (medio % 2 == 0 && medio > inicio) 
        medio++;
    
    *raiz = crearNodo(arreglo[medio]);
    (*raiz)->cantidad_nodos = contarNodos(*raiz);

    
    balancear(&(*raiz)->izq, arreglo, inicio, medio - 1); 
    balancear(&(*raiz)->dch, arreglo, medio + 1, fin); 

}


void guardarOrden(Nodo* raiz, int *i, int *x){
    if (raiz == NULL) return;

    guardarOrden(raiz->izq, i, x);
    // printf("Guardando %d en la posicion %d\n", raiz->dato, *i);
    x[*i] = raiz->dato; 
    (*i)++;
    guardarOrden(raiz->dch, i, x);
    
}

int estaEquilibrado(Nodo *raiz) {
    if (raiz == NULL) {
        return 1;
    }

    if (!estaEquilibrado(raiz->izq) || !estaEquilibrado(raiz->dch)) {
        return 0;  
    }

    int alturaIzq =  profundidades(raiz->izq);
    int alturaDch =  profundidades(raiz->dch);

    if ((alturaDch - alturaIzq) < -1 || (alturaDch - alturaIzq) > 1) {
        return 0;  
    }

    return estaEquilibrado(raiz->izq) && estaEquilibrado(raiz->dch);
    
}


void eliminarPostorden(Nodo** raiz) {
    if (*raiz == NULL) return;

    eliminarPostorden(&((*raiz)->izq));
    eliminarPostorden(&((*raiz)->dch));
    free(*raiz);
    *raiz = NULL;  

}

Nodo *crearNodo(int dato){
    Nodo *nuevo = (Nodo*)calloc(1,sizeof(Nodo));
    nuevo->dato = dato;
    nuevo->cantidad_nodos = 1;
    return nuevo; 
}

void menu(){
    printf("\n\n=============================================================\n");
    printf("Elige una opcion\n");
    printf("\n [1]Insertar en Arbol A");
    printf("\n [2]Insertar en Arbol B");
    printf("\n [3]Comparar arboles");
	printf("\n [4]Eliminar dato en Arbol A");
	printf("\n [5]Eliminar dato en Arbol B");
	printf("\n [6]Mostrar Profundidades de los Arboles");
    printf("\n [7]Equilibrar Arboles");
    printf("\n [8]Mostrar Arboles");
    printf("\n [9]Terminar programa");
    printf("\n\n=============================================================\n");
    printf("Opcion-> ");
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