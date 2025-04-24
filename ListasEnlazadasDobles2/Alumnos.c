#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Estructuras.h"

#define BUFFER_SIZE 100

Alumno* crearAlumno(void)
{	
	int c;
	char buffer[BUFFER_SIZE];
	
	Alumno *alumno = (Alumno*)calloc(1,sizeof(Alumno));
	
	printf("\n Captura matricula: ");
	scanf("%u",&alumno->matricula);
	//LIMPIAR BUFFER ENTRADA
	while ( (c = getchar()) != '\n' && c != EOF ) { }
	//NOMBRE
	printf(" Captura Nombre: ");

	fgets(buffer,BUFFER_SIZE,stdin);
	buffer[strlen(buffer)-1] = '\0';
	alumno->nombre = (char*) calloc(strlen(buffer)+1,sizeof(char));
	strcpy(alumno->nombre,buffer);
	
	//APELLIDO
	printf(" Captura Apellido: ");
	fgets(buffer,BUFFER_SIZE,stdin);
	buffer[strlen(buffer)-1] = '\0';
	alumno->apellido = (char*) calloc(strlen(buffer)+1,sizeof(char));
	strcpy(alumno->apellido,buffer);
	
	printf(" Captura Promedio: ");
	scanf("%d",&alumno->promedio);
	//LIMPIAR BUFFER ENTRADA
	while ( (c = getchar()) != '\n' && c != EOF ) { }
	return alumno;
	
	
}

void desplegarAlumno(Alumno alumno) {
    printf("\n %u %s %s %d", alumno.matricula, alumno.nombre, alumno.apellido, alumno.promedio);
}

void eliminar_Alumno(Alumno *alumno) {
    free(alumno->nombre);
    free(alumno->apellido);
    free(alumno);
}

int captura_FiltroNUM(FiltroNUM* filtro)
{
	int tmp;
	printf("\n Captura valor minimo: ");
	fflush(stdin);
	scanf(" %d",&(filtro->min));
	printf("\n Captura valor maximo: ");
	fflush(stdin);
	scanf(" %d",&(filtro->max));
	
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

	filtro->min = toupper(filtro->min);
	filtro->max = toupper(filtro->max);
		
	if(filtro->min > filtro->max)
	{
		tmp = filtro->max;
		filtro->max = filtro->min;
		filtro->min = tmp;
	}
	return 0;
}




