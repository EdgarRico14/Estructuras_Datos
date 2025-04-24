
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef struct
{
	int min;
	int max;
}FiltroNUM;

typedef struct
{
	char min;
	char max;
}FiltroCHAR;

int captura_FiltroNUM(FiltroNUM*);
int captura_FiltroCHAR(FiltroCHAR*);
void actualizar_lista(Lista*,Lista,Lista,Lista);

//VERIFICAR CUMPLE FILTRO
int cumple_filtro_Matricula(Alumno *alumno, FiltroNUM filtro);
int cumple_filtro_Semestre(Alumno *alumno, FiltroNUM filtro);
int cumple_filtro_Inicial(Alumno *alumno, FiltroCHAR filtro);

//FILTRADO A LISTAS ENLAZADAS
void filtrar_agregarMatricula(Lista *lista, Alumno **alumnos, FiltroNUM filtro, int n);
void filtrar_agregarSemestre(Lista *lista, Alumno **alumnos, FiltroNUM filtro, int n);
void filtrar_agregarInicial(Lista *lista, Alumno **alumnos, FiltroCHAR filtro, int n);
 
int main(void)
{
	int opcion;
    int n,i;
    Alumno **alumnos;
    //CARGAR DATOS
	alumnos = obtener_estudiantes(&n);
   	FiltroNUM f_matricula;
	FiltroNUM f_semestre;
	FiltroCHAR f_inicial;
	//DEFAULTS
	f_matricula = (FiltroNUM){.min=0,.max=99999999};
	f_semestre  = (FiltroNUM){.min=0,.max=99999999};
	f_inicial 	= (FiltroCHAR){.min='a',.max='z'};
	//LISTAS
	Lista l_matricula;
	Lista l_semestre;
	Lista l_inicial;
	Lista l_cuarta;
	inicializar_lista(&l_matricula);
	inicializar_lista(&l_semestre);
	inicializar_lista(&l_inicial);
	inicializar_lista(&l_cuarta);
	
    
	
	do
	{        
        //BORRAR CUARTA LISTA
        //ACTUALIZAR CUARTA LISTA
        
		LIMPIAR_PANTALLA;
		printf("\n    FILTRO MATRICULA -> MIN: %d MAX: %d",f_matricula.min,f_matricula.max);
		printf("\n    FILTRO SEMESTRE -> MIN: %d MAX: %d",f_semestre.min,f_semestre.max);
		printf("\n    FILTRO INICIAL -> MIN: %c MAX: %c",f_inicial.min,f_inicial.max);
		printf("\n\n ---MENU---");
		printf("\n [1]CAPTURAR FILTRO MATRICULA");
		printf("\n [2]CAPTURAR FILTRO SEMESTRE");
		printf("\n [3]CAPTURAR FILTRO INICIAL APELLIDO");
		printf("\n [4]MOSTRAR LISTA FILTRADA POR MATRICULA");
		printf("\n [5]MOSTRAR LISTA FILTRADA POR SEMESTRE");
		printf("\n [6]MOSTRAR LISTA FILTRADA POR INICIAL APELLIDO");
		printf("\n [7]MOSTRAR LISTA CON 3 FILTROS APLICADOS ASCENDENTE");
		printf("\n [8]MOSTRAR LISTA CON 3 FILTROS APLICADOS DESCENDENTE");
		printf("\n [9]SALIR");
		printf("\n\n SELECCIONAR OPCION: ");

		fflush(stdin);
		scanf("%d",&opcion);
		switch(opcion)
		{
			case 1:
                    //ELIMINAR LISTA
                    eliminar_lista(&l_matricula);
                    //CAPTURA NUEVO FILTRO
					captura_FiltroNUM(&f_matricula);
                    //CREAR LISTA
                    filtrar_agregarMatricula(&l_matricula, alumnos, f_matricula, n);
					break;
			case 2:
                    //ELIMINAR LISTA
                    eliminar_lista(&l_semestre);
                    //CAPTURA NUEVO FILTRO
					captura_FiltroNUM(&f_semestre);
                    //CREAR LISTA
                    filtrar_agregarSemestre(&l_semestre, alumnos, f_semestre, n);
					break;
			case 3:
                    //ELIMINAR LISTA
                    eliminar_lista(&l_inicial);
                    //CAPTURA NUEVO FILTRO
					captura_FiltroCHAR(&f_inicial);
                    //CREAR LISTA
                    filtrar_agregarInicial(&l_inicial, alumnos, f_inicial, n);
					break;
			case 4:
					printf("\n");
					recorrer_lista(l_matricula);
					break;
			case 5:
					printf("\n");
					recorrer_lista(l_semestre);
					break;
			case 6:
					printf("\n");
					recorrer_lista(l_inicial);
					break;
			case 7:			               
					printf("\n");
					inicializar_lista(&l_cuarta);
					actualizar_lista(&l_cuarta, l_matricula, l_semestre, l_inicial);
					recorrer_lista(l_cuarta);
					break;
			case 8:			               
					printf("\n");
					recorrer_lista_descendente(l_cuarta);
					break;
			case 9:
					break;
			default:
					break;
		}
		printf("\n");
		ESPERAR;
	}while(opcion!=9);
    //ELIMINAR NODOS EN LISTAS
    eliminar_lista(&l_matricula);
    eliminar_lista(&l_semestre);
    eliminar_lista(&l_inicial);
    eliminar_lista(&l_cuarta);
    //LIBERAR DATOs
	for(i=0;i<n;i++)
    {
		free((*(alumnos[i])).nombre);
		free((*(alumnos[i])).apellido);
		free(alumnos[i]);
    } 
	free(alumnos);      	  
    printf("\n\n");
    return 0;
}

void actualizar_lista(Lista* cuarta, Lista a, Lista b, Lista c) {
    Nodo *nodoMatricula = a.inicio;
    while (nodoMatricula != NULL) {
        if (alumno_existe(nodoMatricula->alumno, b) && alumno_existe(nodoMatricula->alumno, c)) {
           
            agregar_alumno_ordenado(cuarta, nodoMatricula->alumno);
        }
        nodoMatricula = nodoMatricula->siguiente;
    }
    printf("\nLista filtrada\n");
}


int captura_FiltroNUM(FiltroNUM* filtro)
{
	int tmp;
	printf("\n Captura valor minimo: ");
	fflush(stdin);
	scanf("%d",&(filtro->min));
	printf("\n Captura valor maximo: ");
	fflush(stdin);
	scanf("%d",&(filtro->max));
	
	if(filtro->min > filtro->max)
	{
		tmp = filtro->max;
		filtro->max = filtro->min;
		filtro->min = tmp;
	}
	return 0;
}

int captura_FiltroCHAR(FiltroCHAR* filtro)
{
	char tmp;
	printf("\n Captura valor minimo: ");
	fflush(stdin);
	scanf("%c",&(filtro->min));
	printf("\n Captura valor maximo: ");
	fflush(stdin);
	scanf("%c",&(filtro->max));

	filtro->min = tolower(filtro->min);
	filtro->max = tolower(filtro->max);
		
	if(filtro->min > filtro->max)
	{
		tmp = filtro->max;
		filtro->max = filtro->min;
		filtro->min = tmp;
	}
	return 0;
}

int cumple_filtro_Matricula(Alumno *alumno, FiltroNUM filtro) {
    return alumno->matricula >= filtro.min && alumno->matricula <= filtro.max;
}

int cumple_filtro_Semestre(Alumno *alumno, FiltroNUM filtro) {
    return alumno->semestre >= filtro.min && alumno->semestre <= filtro.max;
}

int cumple_filtro_Inicial(Alumno *alumno, FiltroCHAR filtro) {
    return alumno->apellido[0] >= filtro.min && alumno->apellido[0] <= filtro.max;
}

void filtrar_agregarMatricula(Lista *lista, Alumno **alumnos, FiltroNUM filtro, int n) {
    for (int i = 0; i < n; i++) {
        if (cumple_filtro_Matricula(*(alumnos+i), filtro)) {
            agregar_alumno(lista, *(alumnos+i));
        }
    }
}

void filtrar_agregarSemestre(Lista *lista, Alumno **alumnos, FiltroNUM filtro, int n) {
    for (int i = 0; i < n; i++) {
        if (cumple_filtro_Semestre(*(alumnos+i), filtro)) {
            agregar_alumno(lista, *(alumnos+i));
        }
    }
}

void filtrar_agregarInicial(Lista *lista, Alumno **alumnos, FiltroCHAR filtro, int n) {
    for (int i = 0; i < n; i++) {
        if (cumple_filtro_Inicial(*(alumnos + i), filtro)) {
            agregar_alumno(lista, *(alumnos + i));
        }
    }
}
