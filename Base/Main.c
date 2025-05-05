#include "Header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *cadena;
	int opc = 0;
	int i = 0;

	Monton *monton = NULL;
	monton = malloc(sizeof(Monton));
	monton->cantidad = 0;
	monton->nodos = NULL;
	monton->tipo = MINIMO;

	do{
		menu();
		scanf(" %d", opc);
		printf("\n");
		realizar_operacion(monton, opc);
	}while(opc != 6);
	
	return 0;
}


void menu(){
    printf("\n=============================================================\n");
    printf("Elige una opcion\n");
    printf("\n [0]Cambiar prioridad");
    printf("\n [1]Mostrar cola de impresion");
    printf("\n [2]Agregar archivo");
    printf("\n [3]Procesar/Imprimir archivo");
    printf("\n [4]Eliminar archivo");
    printf("\n [5]Eliminar todos los archivos");
    printf("\n [6]Terminar programa");
    printf("Opcion-> ");

}