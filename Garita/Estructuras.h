#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMERO_CASETAS 4
#define HABILITADA 1
#define DESHABILITADA 0
#define MIN_TICKS_ESPERA 2
#define MAX_TICKS_ESPERA 8

typedef struct 
{
	char* marca;
	unsigned short int anio;
	unsigned char* color;
}Vehiculo;

typedef struct nodo
{
	Vehiculo vehiculo;
	int ticks_espera;
	struct nodo* anterior;
	struct nodo* siguiente;
}Nodo;

typedef struct
{
	Nodo* inicio;
	Nodo* fin;
	int longitud;
	int cantidad_datos;
	char estado;
}Cola;

Vehiculo generar_vehiculo(void);
void desplegar_vehiculo(Vehiculo vehiculo);
void desplegar_casetas(Cola *);


void inicializar_cola(Cola*,int);
Nodo* crear_nodo(Vehiculo);
int cola_vacia(Cola);
int cola_llena(Cola);
void agregar(Cola*,Vehiculo);
int agregar_nodo(Cola*,Nodo*);
Vehiculo* eliminar(Cola*);
Nodo* eliminar_nodo(Cola*);
void desplegar_cola(Cola);


#endif