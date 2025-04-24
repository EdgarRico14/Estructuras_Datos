
#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALIDO 1
#define INVALIDO 0


typedef struct date
{
	int year;
	int month;
	int day;
}Date;

typedef struct alumno
{
	int matricula;
	int semestre;
	char *nombre;
	char *apellido;
	Date fecha;
}Alumno;

typedef struct nodo
{
	Alumno *alumno;
	struct nodo *anterior;
	struct nodo *siguiente;
}Nodo;

typedef struct lista
{
	Nodo *inicio;
	Nodo *fin;
	int cantidad;
}Lista;

//PROTOTIPOS - ESTRUCTURAS UTILIZADAS: ALUMNO,DATE
Alumno crear_alumno(int,int,char*,char*,int,int,int);
void imprimir_alumno(Alumno);

//INICIALIZAR CREAR LISTA/NODO
void inicializar_lista(Lista*);
Nodo* crear_Nodo(Alumno*);

//RECORRER
void recorrer_lista(Lista);
void recorrer_lista_descendente(Lista);
//INSERTAR
void agregar_alumno(Lista*,Alumno*);
void agregar_alumno_ordenado(Lista*,Alumno*);
//ELIMINAR
void eliminar_lista(Lista*);
//VERIFICAR
int alumno_existe(Alumno*,Lista);

#endif