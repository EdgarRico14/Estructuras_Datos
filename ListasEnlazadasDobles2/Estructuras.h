
#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct
{
	unsigned int matricula;
	char *nombre;
	char *apellido;
	int promedio;
}Alumno;

typedef struct nodo
{
	Alumno *alumno;
	struct nodo *sig;
	struct nodo *ant;
}Nodo;


typedef struct
{
	Nodo *inicio;
	Nodo *fin;
	int cantidad_nodos;
}Lista;

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

#endif