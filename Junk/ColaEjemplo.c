#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
	float dato;
	struct nodo* anterior;
	struct nodo* siguiente;
}Nodo;

typedef struct
{
	Nodo* inicio;
	Nodo* fin;
	int longitud;
	int cantidad_datos;
}Cola;

void agregar(Cola*,float);
int agregar_nodo(Cola*,Nodo*);
float* eliminar(Cola*);
Nodo* eliminar_nodo(Cola*);
void imprimir(Cola);

//YA
void inicializar_cola(Cola*,int);
Nodo* crear_nodo(float);
int cola_vacia(Cola);
int cola_llena(Cola);
void main(void)
{
	Nodo *nodo_temp;
	float *dato_temp;
	Cola cola;
	inicializar_cola(&cola,7);
	
	agregar(&cola,2   );
	agregar(&cola,3.5 );
	agregar(&cola,5   );
	agregar(&cola,4   );
	agregar(&cola,3   );
	agregar(&cola,2   );
	agregar(&cola,1   );
	
	agregar(&cola,23  ); //NO SE AGREGA
	agregar(&cola,7.77); //NO SE AGREGA
	
	printf("\n Antes de eliminar");
	imprimir(cola);
	//ELIMINAR 2 ELEMENTOS
	dato_temp = eliminar(&cola);
	if(!dato_temp) free(dato_temp);
	nodo_temp = eliminar_nodo(&cola);
	if(!nodo_temp) free(nodo_temp);
	
	printf("\n Despues de eliminar");
	imprimir(cola);
	
	agregar(&cola,23  );
	agregar(&cola,7.77);
	
	printf("\n Despues de agregar");
	imprimir(cola);
	
	printf("\n\n");
		
}


void inicializar_cola(Cola* cola,int longitud)
{
	cola->inicio = NULL;
	cola->fin = NULL;
	cola->cantidad_datos = 0;
	cola->longitud = longitud;
}


Nodo* crear_nodo(float dato)
{
	Nodo* nuevo;
	nuevo = (Nodo*) calloc(1,sizeof(Nodo));
	nuevo->dato = dato;
	nuevo->anterior = NULL;
	nuevo->siguiente = NULL;
	return nuevo;	
}


int cola_vacia(Cola cola)
{
	return cola.inicio==NULL && cola.fin==NULL && cola.cantidad_datos==0;
}
int cola_llena(Cola cola)
{
	return cola.cantidad_datos == cola.longitud;
}

void agregar(Cola* cola,float dato)
{
	Nodo* nuevo;
	if(cola_llena(*cola))
		return;
	nuevo = crear_nodo(dato);
	if(cola_vacia(*cola))
	{
		cola->inicio = nuevo;
		cola->fin = nuevo;
	}
	else
	{
		cola->fin->siguiente = nuevo;
		nuevo->anterior = cola->fin;
		cola->fin = nuevo;		
	}

	cola->cantidad_datos++;	
}

int agregar_nodo(Cola* cola,Nodo* nuevo)
{
	if(cola_llena(*cola))
		return 0;
	if(cola_vacia(*cola))
	{
		cola->inicio = nuevo;
		cola->fin = nuevo;
	}
	else
	{
		cola->fin->siguiente = nuevo;
		nuevo->anterior = cola->fin;
		cola->fin = nuevo;		
	}	
	cola->cantidad_datos++;
	return 1;
}


float* eliminar(Cola* cola)
{
	Nodo* temp;
	float* dato;
	if(cola_vacia(*cola))
	{
		return NULL;
	}
	dato = (float*) calloc(1,sizeof(float));
	
	temp = cola->inicio;
	*dato = temp->dato;
	cola->inicio = cola->inicio->siguiente;
	free(temp);
	cola->cantidad_datos--;
	if(!cola->cantidad_datos)
		cola->fin = NULL;	
	else		
		cola->inicio->anterior = NULL;
	return dato;
}

Nodo* eliminar_nodo(Cola* cola)
{
	Nodo* temp;
	if(cola_vacia(*cola))
	{
		return NULL;
	}
	temp = cola->inicio;
	cola->inicio = cola->inicio->siguiente;	
	
	cola->cantidad_datos--;
	if(!cola->cantidad_datos)
		cola->fin = NULL;	
	else		
		cola->inicio->anterior = NULL;
	return temp;	
}


void imprimir(Cola cola)
{
	Cola temp;
	Nodo* nodo_temp;
	inicializar_cola(&temp,cola.longitud);
	
	while(!cola_vacia(cola))
	{
		nodo_temp = eliminar_nodo(&cola);
		printf("\n %.2f", nodo_temp->dato);
		agregar_nodo(&temp,nodo_temp);
	}
	
	while(!cola_vacia(temp))
	{
		nodo_temp = eliminar_nodo(&temp);
		agregar_nodo(&cola,nodo_temp);
	}

}