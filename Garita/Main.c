#include "Estructuras.h"

void main(void)
{	
	srand(time(NULL));
	Nodo *nodo_temp;
	Cola cola;
	Cola casetas[NUMERO_CASETAS];
	int i;
	for(i=0;i<NUMERO_CASETAS;i++)
	{		
		inicializar_cola(&(casetas[i]),20);
	}
	
	inicializar_cola(&cola,800);

	agregar(&cola,generar_vehiculo());
	agregar(&cola,generar_vehiculo());
	agregar(&cola,generar_vehiculo());
	agregar(&cola,generar_vehiculo());
	agregar(&cola,generar_vehiculo());
	agregar(&cola,generar_vehiculo());
	agregar(&cola,generar_vehiculo());
	agregar(&cola,generar_vehiculo());
			
	desplegar_cola(cola);
	
	agregar(&casetas[0],generar_vehiculo());
	agregar(&casetas[0],generar_vehiculo());
	agregar(&casetas[1],generar_vehiculo());
	agregar(&casetas[1],generar_vehiculo());
	agregar(&casetas[0],generar_vehiculo());
	agregar(&casetas[0],generar_vehiculo());
	
	desplegar_casetas(casetas);
	
	
	printf("\n\n");
		
}