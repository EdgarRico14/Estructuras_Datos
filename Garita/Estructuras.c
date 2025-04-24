#include "Estructuras.h"

Vehiculo generar_vehiculo(void)
{
	static char *marcas[10] = {"Toyota\0","Nissa\0","Honda\0","Volvo\0","Dodge\0","Hyundai\0","Ford\0","Renault\0","BMW\0","Mercedez-Benz\0"};
	static char *colores[12] = {"Azul\0","Gris\0","Blanco\0","Negro\0","Rojo\0","Amarillo\0","Cafe\0","Verde\0","Morado\0","Rosa\0","Naranja\0","Dorado\0"};
	int min,max,index;
	Vehiculo nuevo;
	min = 0;
	max = 9;
	index = rand() % (max - min + 1) + min;
	nuevo.marca = marcas[index];
	min = 1990;
	max = 2025;
	nuevo.anio = rand() % (max - min + 1) + min;
	min = 0;
	max = 11;
	index = rand() % (max - min + 1) + min;
	nuevo.color = colores[index];
	return nuevo;
}

void desplegar_vehiculo(Vehiculo vehiculo)
{
	printf("\n V:%-15s C:%-15s A:%d",vehiculo.marca,vehiculo.color,vehiculo.anio);
}


void desplegar_casetas(Cola *casetas)
{
	int i,r;
	Nodo* nodo_temp;
	Cola temp[NUMERO_CASETAS];
	for(i=0;i<NUMERO_CASETAS;i++)
	{		
		inicializar_cola(&(temp[i]),casetas[i].longitud);
	}
	
	do
	{	
		printf("\n");
		r=0;
		//VERIFICAR SI UNA CASETA TIENE CARROS
		for(i=0;i<NUMERO_CASETAS;i++)
		{		
			r|= !cola_vacia(casetas[i]);
		}
		
		if(r)
		{
			for(i=0;i<NUMERO_CASETAS;i++)
			{		
				if(!cola_vacia(casetas[i]))
				{
					nodo_temp = eliminar_nodo(&casetas[i]);
					printf(" X ");
					agregar_nodo(&temp[i],nodo_temp);
				}
				else
				{					
					printf("   ");
				}
			}
			r=0;
			for(i=0;i<NUMERO_CASETAS;i++)
			{		
				r|= !cola_vacia(casetas[i]);
			}
		}		
	}while(r);
	
	for(i=0;i<NUMERO_CASETAS;i++)
	{		
		while(!cola_vacia(temp[i]))
		{
			nodo_temp = eliminar_nodo(&temp[i]);
			agregar_nodo(&casetas[i],nodo_temp);
		}
	}
}


void inicializar_cola(Cola* cola,int longitud)
{
	cola->inicio = NULL;
	cola->fin = NULL;
	cola->cantidad_datos = 0;
	cola->longitud = longitud;
	cola->estado = HABILITADA;
}


Nodo* crear_nodo(Vehiculo vehiculo)
{
	Nodo* nuevo;
	nuevo = (Nodo*) calloc(1,sizeof(Nodo));
	nuevo->vehiculo = vehiculo;
	nuevo->ticks_espera = rand() % (MAX_TICKS_ESPERA - MIN_TICKS_ESPERA + 1) + MIN_TICKS_ESPERA;
	nuevo->anterior = NULL;
	nuevo->siguiente = NULL;
	return nuevo;	
}

int cola_vacia(Cola cola)
{
	return 1;
}

int cola_llena(Cola cola)
{
	return 1;
}

void agregar(Cola* cola,Vehiculo vehiculo)
{
	//...
}

int agregar_nodo(Cola* cola,Nodo* nuevo)
{
	//...
	return 0;
}


Vehiculo* eliminar(Cola* cola)
{
	//...
	return NULL;
}

Nodo* eliminar_nodo(Cola* cola)
{
	//...
	return NULL;
}


void desplegar_cola(Cola cola)
{
	//...
}
