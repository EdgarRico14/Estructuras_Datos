#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Estructuras.h"

// Funciones de gestión de listas
void inicializar_lista(Lista *lista);
void eliminar_lista(Lista *lista);
void actualizar_lista(Lista* cuarta, Lista* matricula, Lista* inicial);
void recorrer_lista(Lista lista);
void recorrer_lista_descendente(Lista lista);

// Funciones de gestión de nodos y alumnos
Nodo* crear_Nodo(Alumno* alumno);
void agregar_alumno(Lista* lista, Alumno* alumno);
void agregar_alumno_ordenado(Lista* lista, Alumno* alumno);
Alumno* crearAlumno(void);
void desplegarAlumno(Alumno alumno);
void eliminar_Alumno(Alumno* alumno);
int alumno_existe(Alumno* alumno, Lista lista);

// Funciones de filtrado
int cumple_filtro_Matricula(Alumno *alumno, FiltroNUM filtro);
int cumple_filtro_Inicial(Alumno *alumno, FiltroCHAR filtro);
void agregar_filtroMatricula(Lista *lista, Alumno *alumno, FiltroNUM filtro);
void agregar_filtroInicial(Lista *lista, Alumno *alumno, FiltroCHAR filtro);
void recorrer_y_agregarMatricula(Lista *l_principal, Lista *l_matricula, FiltroNUM f_matricula);
void recorrer_y_agregarInicial(Lista *l_principal, Lista *l_inicial, FiltroCHAR f_inicial);

// Funciones de eliminación de alumnos
void eliminarAlumnoDeTodasLasListas(Lista* principal, Lista* matricula, Lista* inicial, Lista* cuarta, unsigned int matriculaID);
void eliminarAlumnoDeListaPorMatricula(Lista *lista, unsigned int matricula);


void menu(void);

int main(void)
{
    int opcion = 0;
    FiltroNUM f_matricula;
	FiltroCHAR f_inicial;
	
	f_matricula = (FiltroNUM){.min=0,.max=99999999};
	f_inicial 	= (FiltroCHAR){.min='A',.max='Z'};
	
    Lista l_principal;
	Lista l_matricula;
	Lista l_inicial;
	Lista l_cuarta;

	inicializar_lista(&l_principal);
	inicializar_lista(&l_matricula);
	inicializar_lista(&l_inicial);
    inicializar_lista(&l_cuarta);

    do
    {   
        printf("\n\n    FILTRO MATRICULA -> MIN: %d MAX: %d",f_matricula.min,f_matricula.max);
		printf("\n    FILTRO INICIAL -> MIN: %c MAX: %c",f_inicial.min,f_inicial.max);
        menu();
        scanf(" %d", &opcion);
        switch (opcion)
        {
        case 1:
            agregar_alumno(&l_principal, crearAlumno());
            break;
        case 2:
            printf("\nCaptura matricula a eliminar: ");
            unsigned int matriculaID;
            scanf(" %u", &matriculaID);
            eliminarAlumnoDeTodasLasListas(&l_principal, &l_matricula, &l_inicial, &l_cuarta, matriculaID);
            break;
    
        case 3:
            printf("\n");
            recorrer_lista(l_principal);
            break;

        case 4:
            eliminar_lista(&l_matricula);
            captura_FiltroNUM(&f_matricula);
            recorrer_y_agregarMatricula(&l_principal, &l_matricula, f_matricula);
            actualizar_lista(&l_cuarta, &l_matricula, &l_inicial);
            break;
        
        case 5:
            eliminar_lista(&l_inicial);
            captura_FiltroCHAR(&f_inicial);
            recorrer_y_agregarInicial(&l_principal, &l_inicial, f_inicial);
            actualizar_lista(&l_cuarta, &l_matricula, &l_inicial);
            break;
        
        case 6:
            printf("\n");
            recorrer_lista(l_matricula);
            break;
        case 7:
            printf("\n");
            recorrer_lista(l_inicial);
            break;
        case 8:
            printf("\n");
            recorrer_lista(l_cuarta);
            break;
        case 9:
            printf("\n");
			recorrer_lista_descendente(l_cuarta);
            break;
        case 10:
            printf("\nAdios!\n");
            break;
    
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 10);
    
    eliminar_lista(&l_principal);
    eliminar_lista(&l_matricula);
    eliminar_lista(&l_inicial);
    eliminar_lista(&l_cuarta);
	

    return 0;
}

void actualizar_lista(Lista* cuarta, Lista* matricula, Lista* inicial) {
    eliminar_lista(cuarta); 
    Nodo *nodoMatricula = matricula->inicio;
    while (nodoMatricula != NULL) {
        if (alumno_existe(nodoMatricula->alumno, *inicial)) {
            agregar_alumno_ordenado(cuarta, nodoMatricula->alumno);
        }
        nodoMatricula = nodoMatricula->sig;
    }
    printf("\nLista filtrada actualizada\n");
}


void inicializar_lista(Lista *lista)
{
	lista->inicio = NULL;
	lista->fin = NULL;
	lista->cantidad_nodos = 0;
}

Nodo* crear_Nodo(Alumno* alumno)
{
	Nodo* nuevo_nodo = (Nodo*)calloc(1, sizeof(Nodo));
    nuevo_nodo->ant = NULL;
    nuevo_nodo->alumno = alumno;
    nuevo_nodo->sig = NULL;
    return nuevo_nodo;
}

void agregar_alumno(Lista* lista, Alumno* alumno)
{
    Nodo *nuevo_nodo = crear_Nodo(alumno);
	if (nuevo_nodo == NULL) {
        printf("Error al crear el nodo\n");
        return;
    }
    if (lista->inicio == NULL) {
        lista->inicio = nuevo_nodo;
        lista->fin = nuevo_nodo;
    } else {
        lista->fin->sig = nuevo_nodo;
        nuevo_nodo -> ant = lista -> fin;
        lista->fin = nuevo_nodo;
    }
    lista->cantidad_nodos++;
}

void agregar_alumno_ordenado(Lista* lista, Alumno* alumno) {
    Nodo *nuevo = crear_Nodo(alumno);
    if (!nuevo) return;

    if (lista->inicio == NULL) {
        lista->inicio = nuevo;
        lista->fin = nuevo;
    } else {
        Nodo *actual = lista->inicio;
        
        // Buscar la posición correcta
        while (actual != NULL && strcmp(nuevo->alumno->apellido, actual->alumno->apellido) > 0) {
            actual = actual->sig;
        }

        if (actual == lista->inicio) {
            // Insertar al inicio
            nuevo->sig = lista->inicio;
            lista->inicio->ant = nuevo;
            lista->inicio = nuevo;
        } else if (actual == NULL) {
            // Insertar al final
            nuevo->ant = lista->fin;
            lista->fin->sig = nuevo;
            lista->fin = nuevo;
        } else {
            // Insertar en medio
            nuevo->sig = actual;
            nuevo->ant = actual->ant;
            actual->ant->sig = nuevo;
            actual->ant = nuevo;
        }
    }
    lista->cantidad_nodos++;
}



void recorrer_lista(Lista lista)
{
	Nodo* p = lista.inicio;
	if (p == NULL) {
        printf("La lista esta vacia\n");
        return;
    }
	while(p!=NULL)
	{
		printf("\n");
		desplegarAlumno(*(p->alumno));
		p= p->sig;
	}
	printf("\n\nCantidad de alumnos: %d", lista.cantidad_nodos);
}

void recorrer_lista_descendente(Lista lista)
{
	Nodo* p = lista.fin;
	if (p == NULL) {
        printf("La lista esta vacia\n");
        return;
    }
	while(p!=NULL)
	{
		printf("\n");
		desplegarAlumno(*(p->alumno));
		p= p->ant;
	}
}

void eliminar_lista(Lista* lista) {
    Nodo *actual = lista->inicio;
    while (actual != NULL) {
        Nodo *temp = actual;
        actual = actual->sig;
        free(temp->alumno); 
        free(temp);
    }
    printf("\nLista vaciada\n");
    inicializar_lista(lista);
}



int alumno_existe(Alumno* alumno, Lista lista) {
    if (lista.inicio == NULL) return 0; 

    Nodo *actual = lista.inicio;
    while (actual != NULL) {
        if (actual->alumno->matricula == alumno->matricula) {
            return 1;
        }
        actual = actual->sig;
    }
    return 0;
}


void menu(){
    printf("\n=============================================================\n");
    printf("Elige una opcion\n");
    printf("\n [1]AGREGAR ALUMNO");
    printf("\n [2]ELIMINAR ALUMNO");
    printf("\n [3]MOSTRAR PRIMER LISTA");
	printf("\n [4]CAPTURAR FILTRO MATRICULA");
	printf("\n [5]CAPTURAR FILTRO INICIAL APELLIDO");
	printf("\n [6]MOSTRAR LISTA FILTRADA POR MATRICULA");
    printf("\n [7]MOSTRAR LISTA FILTRADA POR INICIAL APELLIDO");
    printf("\n [8]MOSTRAR LISTA CON 2 FILTROS APLICADOS ASCENDENTE");
    printf("\n [9]MOSTRAR LISTA CON 2 FILTROS APLICADOS DESCENDENTE");
    printf("\n [10]SALIR");
    printf("\n=============================================================\n");
    printf("Opcion-> ");
}

int cumple_filtro_Matricula(Alumno *alumno, FiltroNUM filtro) {
    return alumno->matricula >= filtro.min && alumno->matricula <= filtro.max;
}

int cumple_filtro_Inicial(Alumno *alumno, FiltroCHAR filtro) {
    return alumno->apellido[0] >= filtro.min && alumno->apellido[0] <= filtro.max;
}

void agregar_filtroMatricula(Lista *lista, Alumno *alumno, FiltroNUM filtro) {
    if (cumple_filtro_Matricula(alumno, filtro)) {
        agregar_alumno(lista, alumno);
    }
}

void agregar_filtroInicial(Lista *lista, Alumno *alumno, FiltroCHAR filtro) {
    if (cumple_filtro_Inicial(alumno, filtro)) {
        agregar_alumno(lista, alumno);
    }
}

void eliminarAlumnoDeListaPorMatricula(Lista *lista, unsigned int matriculaID) {
    Nodo *actual = lista->inicio;

    while (actual != NULL) {
        if (actual->alumno->matricula == matriculaID) {

            if (actual->ant) 
                actual->ant->sig = actual->sig;

            if (actual->sig) 
                actual->sig->ant = actual->ant;

            if (actual == lista->inicio) 
                lista->inicio = actual->sig;

            if (actual == lista->fin) 
                lista->fin = actual->ant;

            if (lista->inicio == NULL) { 
                eliminar_Alumno(actual->alumno);
            }

            free(actual);
            lista->cantidad_nodos--;
            return;
        }
        actual = actual->sig;
    }
}



void eliminarAlumnoDeTodasLasListas(Lista* principal, Lista* matricula, Lista* inicial, Lista* cuarta, unsigned int matriculaID) {
    Nodo *actual = principal->inicio;
    Alumno *alumnoAEliminar = NULL;

    while (actual != NULL) {
        if (actual->alumno->matricula == matriculaID) {
            alumnoAEliminar = actual->alumno;  
            break;
        }
        actual = actual->sig;
    }

    if (alumnoAEliminar == NULL) {
        printf("\nNo se encontró el alumno con matrícula %u en la lista principal.\n", matriculaID);
        return;
    }

    eliminarAlumnoDeListaPorMatricula(matricula, matriculaID);
    eliminarAlumnoDeListaPorMatricula(inicial, matriculaID);
    eliminarAlumnoDeListaPorMatricula(cuarta, matriculaID);

    eliminarAlumnoDeListaPorMatricula(principal, matriculaID);

    free(alumnoAEliminar->nombre);
    free(alumnoAEliminar->apellido);
    free(alumnoAEliminar);

    printf("\nAlumno con matricula %u eliminado correctamente de todas las listas.\n", matriculaID);
}

void recorrer_y_agregarInicial(Lista *l_principal, Lista *l_inicial, FiltroCHAR f_inicial) {
    Nodo *nodo = l_principal->inicio;
    while (nodo != NULL) {
        agregar_filtroInicial(l_inicial, nodo->alumno, f_inicial);
        nodo = nodo->sig;
    }
}

void recorrer_y_agregarMatricula(Lista *l_principal, Lista *l_matricula, FiltroNUM f_matricula) {
    Nodo *nodo = l_principal->inicio;
    while (nodo != NULL) {
        agregar_filtroMatricula(l_matricula, nodo->alumno, f_matricula);
        nodo = nodo->sig;
    }
}