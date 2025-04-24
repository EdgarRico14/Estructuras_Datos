#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// Checking for windows OS with 
// _WIN32 macro 
#ifdef _WIN32 
	#define LIMPIAR_PANTALLA system("cls")
	#define ESPERAR system("pause")
  
// Checking for mac OS with 
// __APPLE__ macro 
#elif __APPLE__ 
	#define LIMPIAR_PANTALLA system("clear")
	#define ESPERAR getchar()  
	
#elif TARGET_OS_MAC
	#define LIMPIAR_PANTALLA system("clear")
	#define ESPERAR getchar()  
#endif

#include "Estructuras.h"
#include "Estudiantes.h"

typedef struct {
    int min;
    int max;
} FiltroNum;

typedef struct {
    char min;
    char max;
} FiltroChar;

void menu();
int capturaFiltroNum(FiltroNum*);
int capturaFiltroChar(FiltroChar*);
int cumple_filtro_matricula(Alumno *, FiltroNum);
int cumple_filtro_semestre(Alumno *, FiltroNum);
int cumple_filtro_inicial(Alumno *, FiltroChar);
void inicializar_lista(Lista*);
void filtrar_y_agregarMatricula(Lista *, Alumno **, int, FiltroNum);
void filtrar_y_agregarSemestre(Lista *, Alumno **, int, FiltroNum);
void filtrar_y_agregarInicial(Lista *, Alumno **, int, FiltroChar);
Nodo* crear_nodo(Alumno*);
void agregar_nodo(Lista*, Alumno*);
void recorrerLista(Lista *);
void filtrar_y_agregar(Lista *, Lista *, Lista *, Lista *);
int esta_en_lista(Lista *, Alumno *);
void vaciar_lista(Lista *lista);
void eliminar_filtro(Lista *, Lista *, Lista *, Lista *, Lista *, FiltroNum *, FiltroNum *, FiltroChar *);

int main(void) {
    Lista listaMatricula;
    Lista listaSemestre;
    Lista listaInicial;
    Lista listaCombinada;
    int n, i, opcion,filtroEliminar;
    Alumno **alumnos;
    FiltroNum matricula;
    FiltroNum semestre;
    FiltroChar inicial;
    
    alumnos = obtener_estudiantes(&n);

    matricula = (FiltroNum){.min = 0, .max = 99999999};
    semestre = (FiltroNum){.min = 0, .max = 99999999};
    inicial = (FiltroChar){.min = 'a', .max = 'z'};

    do {
        printf("\n\nFILTRO MATRICULA -> MIN: %d MAX: %d", matricula.min, matricula.max);
        printf("\nFILTRO SEMESTRE -> MIN: %d MAX: %d", semestre.min, semestre.max);
        printf("\nFILTRO INICIAL -> MIN: %c MAX: %c", inicial.min, inicial.max);
        menu();
        fflush(stdin);
        scanf(" %d", &opcion);
        switch (opcion) {
            case 1:
                capturaFiltroNum(&matricula);
                inicializar_lista(&listaMatricula); 
                filtrar_y_agregarMatricula(&listaMatricula, alumnos, n, matricula);
                break;
            case 2:
                capturaFiltroNum(&semestre);
                inicializar_lista(&listaSemestre); 
                filtrar_y_agregarSemestre(&listaSemestre, alumnos, n, semestre);
                break;
            case 3:
                capturaFiltroChar(&inicial);
                inicializar_lista(&listaInicial); 
                filtrar_y_agregarInicial(&listaInicial, alumnos, n, inicial);
                break;
            case 4:
                recorrerLista(&listaMatricula);
                break;
            case 5:
                recorrerLista(&listaSemestre);
                break;
            case 6:
                recorrerLista(&listaInicial);
                break;
            case 7:
                inicializar_lista(&listaCombinada);
                filtrar_y_agregar(&listaMatricula, &listaSemestre, &listaInicial, &listaCombinada);                   
                break;
            case 8:
                recorrerLista(&listaCombinada);
                break;
            case 9:
                printf("\nSelecciona el filtro a eliminar:\n");
                printf("[1]...Filtro matricula\n");
                printf("[2]...Filtro semestre\n");
                printf("[3]...Filtro inicial\n");
                printf("Opcion-> ");
                scanf(" %d", &filtroEliminar);
                switch (filtroEliminar) {
                    case 1:
                        vaciar_lista(&listaMatricula);
                        matricula.min = 0;
                        matricula.max = 99999999;
                        break;
                    case 2:
                        vaciar_lista(&listaSemestre);
                        semestre.min = 0;
                        semestre.max = 99999999;
                        break;
                    case 3:
                        vaciar_lista(&listaInicial);
                        inicial.min = 'a';
                        inicial.max = 'z';
                        break;
                    default:
                        printf("\nOpción inválida.\n");
                        break;
                }
                break;
            default:
                printf("\nElija opcion valida\n");
                break;
        }
        printf("\n");
        ESPERAR;
    }while (opcion != 10);
    LIMPIAR_PANTALLA;

    for (i = 0; i < n; i++) {
        free(alumnos[i]->nombre);
        free(alumnos[i]->apellido);
        free(alumnos[i]);
    }
    free(alumnos);

    printf("\n\n");
    return 0;
}

void inicializar_lista(Lista *lista) {
    lista->inicio = NULL;
    lista->fin = NULL;
    lista->cantidad = 0;
}

int capturaFiltroNum(FiltroNum* filtro) {
    printf("Ingresa valor minimo: ");
    scanf(" %d", &(filtro->min));
    printf("Ingresa valor maximo: ");
    scanf(" %d", &(filtro->max));
    if (filtro->min > filtro->max) {
        int temp = filtro->min;
        filtro->min = filtro->max;
        filtro->max = temp;
    }
    return 0;
}

int capturaFiltroChar(FiltroChar* filtro) {
    printf("Ingresa letra inicial minima: ");
    scanf(" %c", &filtro->min);
    printf("Ingresa letra inicial maxima: ");
    scanf(" %c", &filtro->max);
    if (filtro->min > filtro->max) {
        char temp = filtro->min;
        filtro->min = filtro->max;
        filtro->max = temp;
    }
    return 0;
}

int cumple_filtro_matricula(Alumno *alumno, FiltroNum filtro) {
    return alumno->matricula >= filtro.min && alumno->matricula <= filtro.max;
}

int cumple_filtro_semestre(Alumno *alumno, FiltroNum filtro) {
    return alumno->semestre >= filtro.min && alumno->semestre <= filtro.max;
}

int cumple_filtro_inicial(Alumno *alumno, FiltroChar filtro) {
    return alumno->nombre[0] >= filtro.min && alumno->nombre[0] <= filtro.max;
}

void filtrar_y_agregarMatricula(Lista *lista, Alumno **alumnos, int n, FiltroNum filtro) {
    for (int i = 0; i < n; i++) {
        if (cumple_filtro_matricula(*(alumnos+i), filtro)) {
            agregar_nodo(lista, *(alumnos+i));
        }
    }
}

void filtrar_y_agregarSemestre(Lista *lista, Alumno **alumnos, int n, FiltroNum filtro) {
    for (int i = 0; i < n; i++) {
        if (cumple_filtro_semestre(*(alumnos+i), filtro)) {
            agregar_nodo(lista, *(alumnos+i));
        }
    }
}

void filtrar_y_agregarInicial(Lista *lista, Alumno **alumnos, int n, FiltroChar filtro) {
    for (int i = 0; i < n; i++) {
        if (cumple_filtro_inicial(*(alumnos+i), filtro)) {
            agregar_nodo(lista, *(alumnos+i));
        }
    }
}

void filtrar_y_agregar(Lista *listaMatricula, Lista *listaSemestre, Lista *listaInicial, Lista *listaCombinada){
        Nodo *nodoMatricula = listaMatricula -> inicio;
        while (nodoMatricula != NULL) {
            if (esta_en_lista(listaSemestre, nodoMatricula->alumno) && esta_en_lista(listaInicial, nodoMatricula->alumno)) {
                
                agregar_nodo(listaCombinada, nodoMatricula->alumno);
            }
                nodoMatricula = nodoMatricula->siguiente;
            }
        printf("\nLista filtrada\n");
}

int esta_en_lista(Lista *lista, Alumno *alumno) {
    Nodo *actual = lista->inicio;
    while (actual != NULL) {
        if (actual->alumno == alumno) {
            return 1;
        } 
        actual = actual->siguiente;
    }
    return 0;
}

void vaciar_lista(Lista *lista) {
    Nodo *actual = lista->inicio;
    Nodo *temp;
    while (actual != NULL) {
        temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    printf("\nLista vaciada\n");
}

Nodo* crear_nodo(Alumno *alumno) {
    Nodo *nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->alumno = alumno;
    nuevo_nodo->siguiente = NULL;
    return nuevo_nodo;
}

void agregar_nodo(Lista *lista, Alumno *alumno) {
    Nodo *nuevo_nodo = crear_nodo(alumno);
    if (lista->inicio == NULL) {
        lista->inicio = nuevo_nodo;
        lista->fin = nuevo_nodo;
    } else {
        lista->fin->siguiente = nuevo_nodo;
        lista->fin = nuevo_nodo;
    }
    lista->cantidad++;
}

void recorrerLista(Lista *lista) {
    Nodo *actual = lista->inicio;
    while (actual != NULL) {
        imprimir_alumno(*(actual->alumno));
        actual = actual->siguiente;
    }
    printf("\nCantidad de Alumnos: %d\n", lista->cantidad);
}

void menu(){
        printf("\n\n-------Menu--------\n\n");
        printf("Selecciona una opcion:\n");
        printf("[1]...Capturar filtro matricula\n");
        printf("[2]...Capturar filtro semestre\n");
        printf("[3]...Capturar filtro inicial\n");
        printf("[4]...Mostrar lista filtrada por matricula\n");
        printf("[5]...Mostrar lista filtrada por semestre\n");
        printf("[6]...Mostrar lista filtrada por incial\n");
        printf("[7]...Aplicar todos los filtros\n");
        printf("[8]...Mostrar los filtros juntos\n");
        printf("[9]...Eliminar filtro\n");
        printf("[10]...Salir\n");
        printf("Opcion-> ");
}