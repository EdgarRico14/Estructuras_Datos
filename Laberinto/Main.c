#include <stdio.h>
#include <stdlib.h>

#define REN 27
#define COL 26

typedef struct nodo {
    int x;
    int y;
    char direccion;
    struct nodo* siguiente;    
} Nodo;

typedef struct {
    Nodo *cima;
    int cant_nodos;
} Pila;

Nodo* crear_nodo(int , int , char );
void inicializar_pila(Pila*);
int push(Pila*, int , int , char);
Nodo* pop(Pila*);
int pila_vacia(Pila);
void desplegar(Pila);
void vaciar(Pila*);
unsigned char** crear_laberinto(void);
int encontrar_camino(unsigned char**, int, int, Pila*, int*);

int main(void) {
    int i, j;
    unsigned char **lab; 
    lab = crear_laberinto();
    
    /*for (i = 0; i < REN; i++) {
        printf("\n\r");
        for (j = 0; j < COL; j++) {
            printf("%c", lab[i][j]);
        }   
    }*/

    Pila pila;
    inicializar_pila(&pila);
    int movimientos = 0;
    int puntoX, puntoY;

    for (i = 0; i < REN; i++) {
        for (j = 0; j < COL; j++) {
            if (lab[i][j] == 'A'){
                puntoX = i;
                puntoY = j;
                break;
            }
        }
        if (lab[i][j] == 'A')
            break;   
    }
    if (encontrar_camino(lab, puntoX, puntoY, &pila, &movimientos)) {
        printf("\n\nCamino encontrado:\n");
        desplegar(pila);
        printf("Cantidad de movimientos: %d\n", movimientos);

    } else {
        printf("\n\nNo se encontro un camino.\n");
    }

    for (i = 0; i < REN; i++) {
        printf("\n\r");
        for (j = 0; j < COL; j++) {
            printf("%c ", lab[i][j]);
        }   
    }

    vaciar(&pila);
    for (i = 0; i < REN; i++) {
        free(lab[i]);
    }
    free(lab);

    return 0;
}

unsigned char** crear_laberinto(void) {
    int i, j;
    char *tmp = 
"xxxxxxxxxxxxxxxxxxxxxxxxxx\
xAx*****x****************x\
x*xxx*x*x*xxxxxxxxx*xxxx*x\
x*****x*x******x**x****x*x\
xxxxxxx*xxxxxx*xx*xxxx*xxx\
x*****x*x****x*x****xx***x\
x*xxx*x*xxxx*x*x*xxxxx*x*x\
x***x*x****x*****xxxxxxx*x\
xxx*x*xxxx*xxxxxxx****x**x\
x*x*x***xx****xx***xx*x*xx\
x*x*x*x*xxxxx**x*xxxx*x**x\
x*x*x*x***x*xx*x****x*xx*x\
x*x*x*xxx****x*x*xx*x****x\
x*x*x*xxxxxxxx*x**x*xxxx*x\
x***x********x*xx*x*x****x\
x*xxxxxxxxxx*x**xxx*x*xxxx\
x***x******x**x*****x**x*x\
xxx*x*xxxxxxx*xxxxxxxx*x*x\
x*x*x*******x****xx****x*x\
x*x*x*xxxxx*xxxx*xx*xxxx*x\
x*x*x****xx***x**xx*x****x\
x*x*xxxxxxx*x**x*xx*x*x*xx\
x*x*********xx*x*xx*xxx*xx\
x*xxxxxxxxxxx**x*********x\
x***x***x***x*xxxxxxxxxx*x\
x*x***x***x*************Bx\
xxxxxxxxxxxxxxxxxxxxxxxxxx\0";

    unsigned char **lab;
    lab = (unsigned char**) malloc(sizeof(unsigned char *) * REN);
    
    for (i = 0; i < REN; i++) {
        lab[i] = (unsigned char*) malloc(sizeof(unsigned char) * COL);
    }
    
    for (i = 0; i < REN; i++) {
        for (j = 0; j < COL; j++) {
            lab[i][j] = tmp[(i * COL) + j];
        }   
    }
    return lab;
}

int encontrar_camino(unsigned char** lab, int x, int y, Pila* pila, int* movimientos){

    if (x < 0 || x >= REN || y < 0 || y >= COL || lab[x][y] == 'x' || lab[x][y] == ' ') {
        return 0;
    }
    
    if (lab[x][y] == 'B') {
        push(pila, x, y, 'F'); 
        (*movimientos)++;
        return 1;
    }                                                                                                                                                                                            
    lab[x][y] = ' ';
    (*movimientos)++;

    if (encontrar_camino(lab, x, y+1 , pila, movimientos)) {
        push(pila, x, y, 'R'); // R de Right
        return 1;
    }
    else if (encontrar_camino(lab, x, y-1, pila, movimientos)) {
        push(pila, x, y, 'L'); // L de Left
        return 1;
    }
    else if (encontrar_camino(lab, x+1, y, pila, movimientos)) {
        push(pila, x, y, 'D'); // D de Down
        return 1;
    }
    else if(encontrar_camino(lab, x-1, y, pila, movimientos)) {
        push(pila, x, y, 'U'); // U de Up
        return 1;
    }
    else{ 
        Nodo *temp = pop(pila);
        free(temp);
        lab[x][y] = '-';
        (*movimientos)--;
        return 0;
    }
}



Nodo* crear_nodo(int x, int y, char direccion) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->x = x;
    nuevo->y = y;
    nuevo->direccion = direccion;
    nuevo->siguiente = NULL;
    return nuevo;
}

void inicializar_pila(Pila* pila) {
    pila->cima = NULL;
    pila->cant_nodos = 0;
}

int push(Pila* pila, int x, int y, char direccion) {
    Nodo* nuevo = crear_nodo(x, y, direccion);
    if (nuevo == NULL) 
        return 0;
    nuevo->siguiente = pila->cima;
    pila->cima = nuevo;
    pila->cant_nodos++;
    return 1;
}

Nodo* pop(Pila* pila) {
    if (pila_vacia(*pila)) 
        return NULL;
    Nodo* top = pila->cima;
    pila->cima = pila->cima->siguiente;
    pila->cant_nodos--;
    return top;
}

int pila_vacia(Pila pila) {
    return pila.cima == NULL;
}

void desplegar(Pila pila) {
    Nodo* actual = pila.cima;
    Nodo* cimaTemp = NULL;
    
    while (actual) {
        Nodo* nuevo = crear_nodo(actual->x, actual->y, actual->direccion);
        nuevo->siguiente = cimaTemp;
        cimaTemp = nuevo;
        actual = actual->siguiente;
    }
    
    actual = cimaTemp;

    while (actual) {
        printf("(x: %d, y: %d) -> %c\n", actual->x, actual->y, actual->direccion);
        Nodo* temp = actual;    
        actual = actual->siguiente;
        free(temp);
    }
}

void vaciar(Pila* pila) {
    while (!pila_vacia(*pila)) {
        Nodo* temp = pop(pila);
        free(temp);
    }
}
