#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct alumno {
    int matricula;
    char *nombre;
    char *apellido;
} Alumno;

typedef struct nodo {
    Alumno *alumno;
    struct nodo *siguiente;
} Nodo;

typedef struct lista {
    Nodo *inicio;
    Nodo *fin;
    int cantidad;
} Lista;

// Prototipos
Nodo *crear_nodo(Alumno *);
void imprimir_lista(Lista *);
void menu();
void inicializar_lista(Lista *);
void ordenarListaMatriculaAscendente(Lista *, Alumno[], int);
void ordenarListaApellidoAscendente(Lista *, Alumno[], int);
void recorrerLista(Lista *);
void liberarMemoria(Lista *);
void insercionNodoMatriculaAscendente(Lista *, Alumno *);
void insercionNodoApellidoAscendente(Lista *, Alumno *);
void imprimir_alumno(Alumno);

int main() {
    int opcion = 0;
    Lista lista;

    Alumno alumnos[] = {
        {1234, "Jose", "Flores"},
        {1354, "Alberto", "Beta"},
        {1246, "Pedro", "Lopez"},
        {2465, "Edgar", "Perez"},
        {1999, "Gabriel", "Valdez"}
    };

    int n = sizeof(alumnos) / sizeof(alumnos[0]);

    while (opcion != 5) {
        menu();
        scanf(" %d", &opcion);
        switch (opcion) {
            case 1:
                inicializar_lista(&lista);
                ordenarListaMatriculaAscendente(&lista, alumnos, n);
                recorrerLista(&lista);
                liberarMemoria(&lista);
                break;
            case 2:
                inicializar_lista(&lista);
                ordenarListaApellidoAscendente(&lista, alumnos, n);
                recorrerLista(&lista);
                liberarMemoria(&lista);
                break;
            case 5:
                printf("\nAdios!\n");
                break;
            default:
                printf("\nOpción no válida. Intenta de nuevo.\n");
                break;
        }
    }

    return 0;
}

void inicializar_lista(Lista *lista) {
    lista->inicio = NULL;
    lista->fin = NULL;
    lista->cantidad = 0;
}


Nodo *crear_nodo(Alumno *alumno) {
    Nodo *nuevo_nodo = (Nodo *)calloc(1, sizeof(Nodo));
    nuevo_nodo->alumno = alumno;
    return nuevo_nodo;
}

void insercionNodoMatriculaAscendente(Lista *lista, Alumno *alum) {
    Nodo *cabeza = lista->inicio;
    Nodo *anterior = NULL;
    Nodo *nuevo_nodo = crear_nodo(alum);

    if (cabeza == NULL) {
        lista->inicio = nuevo_nodo;
        lista->cantidad++;
        return;
    }

    while (cabeza != NULL && cabeza->alumno->matricula < alum->matricula) {
        anterior = cabeza;
        cabeza = cabeza->siguiente;
    }

    if (anterior == NULL) {
        lista->inicio = nuevo_nodo;
    } else {
        anterior->siguiente = nuevo_nodo;
    }

    nuevo_nodo->siguiente = cabeza;
    lista->cantidad++;
}

void insercionNodoApellidoAscendente(Lista *lista, Alumno *alum) {
    Nodo *cabeza = lista->inicio;
    Nodo *anterior = NULL;
    Nodo *nuevo_nodo = crear_nodo(alum);

    if (cabeza == NULL) {
        lista->inicio = nuevo_nodo;
        lista->cantidad++;
        return;
    }

    while (cabeza != NULL && strcmp(cabeza->alumno->apellido, alum->apellido) < 0) {
        anterior = cabeza;
        cabeza = cabeza->siguiente;
    }

    if (anterior == NULL) {
        lista->inicio = nuevo_nodo;
    } else {
        anterior->siguiente = nuevo_nodo;
    }

    nuevo_nodo->siguiente = cabeza;
    lista->cantidad++;
}

void ordenarListaMatriculaAscendente(Lista *lista, Alumno alumnos[], int n) {
    for (int i = 0; i < n; i++) {
        insercionNodoMatriculaAscendente(lista, &alumnos[i]);
    }
}

void ordenarListaApellidoAscendente(Lista *lista, Alumno alumnos[], int n) {
    for (int i = 0; i < n; i++) {
        insercionNodoApellidoAscendente(lista, &alumnos[i]);
    }
}

void imprimir_alumno(Alumno alumno) {
    printf("Matricula: %d\n", alumno.matricula);
    printf("Nombre: %s\n", alumno.nombre);
    printf("Apellido: %s\n\n", alumno.apellido);
}

void recorrerLista(Lista *lista) {
    Nodo *actual = lista->inicio;
    while (actual != NULL) {
        imprimir_alumno(*(actual->alumno));
        actual = actual->siguiente;
    }
    printf("Cantidad de Alumnos: %d\n", lista->cantidad);
}


void liberarMemoria(Lista *lista) {
    if (lista == NULL) 
        return;
    Nodo *actual = lista->inicio;
    Nodo *siguiente;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

void menu() {
    printf("\n=============================================================\n");
    printf("Elige una opcion\n");
    printf("[1] Ordenar lista por matricula en orden ascendente\n");
    printf("[2] Ordenar lista por apellido en orden ascendente\n");
    printf("[5] Salir\n");
    printf("=============================================================\n");
    printf("Opcion-> ");
}
