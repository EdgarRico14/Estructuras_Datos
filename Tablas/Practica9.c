#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Arbol.h"
#include "Libro.h"
#include "Hash.h"

void menu();

int main(void)
{
    int i;
    Libro *libros;
    libros = obtener_libros();
    Nodo *arbol = NULL;
    HashTable *tablaISBN = crear_tabla(ISBN, folding_cadena);
    HashTable *tablaTitulo = crear_tabla(TITULO, folding_cadena);
    HashTable *tablaTituloInicial = crear_tabla(TITULO_INICIAL, folding_cadena);
    HashTable *tablaAutor = crear_tabla(AUTOR, folding_cadena);
    HashTable *tablaAutorInicial = crear_tabla(AUTOR_INICIAL, folding_cadena);
    HashTable *tablaFecha = crear_tabla(FECHA, folding_cadena);


    for(i = 0 ; i < CANT_LIBROS ; i++)
    {
        printf("\n ");
		insertar(&tablaISBN, &libros[i]);
        insertar(&tablaTitulo, &libros[i]);
        insertar(&tablaTituloInicial, &libros[i]);
        insertar(&tablaAutor, &libros[i]);
        insertar(&tablaAutorInicial, &libros[i]);
        insertar(&tablaFecha, &libros[i]);
    }
	
	int opc;

    do{
        printf("\n\n----- LISTADO DE LIBROS DISPONIBLES -----\n");
        int contador = 0;
        for(i = 0; i < CANT_LIBROS; i++){
            if(strcmp(libros[i].isbn, " ") != 0) {
                printf("\n");
                imprimir(libros[i]);
            }
        }
        printf("\n");
        
        menu();
        scanf(" %d", &opc);
        fflush(stdin);
        switch (opc)
        {
        case 1: {
            char isbnBuscar[MAX_ISBN];
            printf("Ingrese el ISBN a buscar: ");
            scanf(" %[^\n]", isbnBuscar);

            Libro *resultado = buscar_por_isbn(tablaISBN, isbnBuscar);
            if (resultado) {
                printf("\nLibro encontrado:\n");
                imprimir(*resultado);
            } else {
                printf("\nNo se encontro ningun libro con ese ISBN.\n");
            }
            break;
        } 
        case 2: {
            int opc;
            printf("Ingrese la opcion 1 o 2: ");
            scanf(" %d", &opc);
            fflush(stdin);
            switch(opc){
                case 1: {
                    char tituloBuscar[MAX_TITULO];
                    printf("Ingrese el titulo a buscar: ");
                    scanf(" %[^\n]", tituloBuscar);

                    Libro *resultado = buscar_por_titulo(tablaTitulo, tituloBuscar);
                    if (resultado) {
                        printf("\nLibro encontrado:\n");
                        imprimir(*resultado);
                    } else {
                        printf("\nNo se encontro ningun libro con ese titulo.\n");
                    }
                    break;
                }
                case 2: {
                    char inicial_inf, inicial_sup;
                    printf("Ingrese la inicial inferior: ");
                    scanf(" %c", &inicial_inf);
                    printf("Ingrese la inicial superior: ");
                    scanf(" %c", &inicial_sup);
                    inicial_inf = toupper(inicial_inf);
                    inicial_sup = toupper(inicial_sup);
                    printf("\nRango de %c hasta %c: \n\n", inicial_inf, inicial_sup);

					for (i = inicial_inf; i <= inicial_sup; i++){
						rango_por_iniciales(&tablaTituloInicial, &arbol, i);
					}
                    
					if (arbol != NULL) {
                        printf("\n\nArbol: \n");
						inorden(arbol);
						liberar_arbol(&arbol);
					}
					else
						printf("\nTitulo no encontrado.\n");
						
                    break;
                }
                default:
                    printf("\nOpcion invalida.\n");
                    break;
              
            }
            break;
        }
        case 3: {
            int opc;
            printf("Ingrese la opcion 1 o 2: ");
            scanf(" %d", &opc);
            fflush(stdin);
            switch(opc){
                case 1: {   
                    char autorBuscar[MAX_AUTOR];
                    printf("Ingrese el autor a buscar: ");
                    scanf(" %[^\n]", autorBuscar);

                    buscar_por_autor(&tablaAutor, &arbol, autorBuscar);

                    if (arbol != NULL) {
                        printf("\n\nArbol: \n");
                        inorden(arbol);
                        liberar_arbol(&arbol);
                    } else {
                        printf("\nAutor no encontrado.\n");
                    }
                    break;
                }
                case 2: {
                    char inicial_inf, inicial_sup;
                    printf("Ingrese la inicial inferior: ");
                    scanf(" %c", &inicial_inf);
                    printf("Ingrese la inicial superior: ");
                    scanf(" %c", &inicial_sup);

                    inicial_inf = toupper(inicial_inf);
                    inicial_sup = toupper(inicial_sup);

                    printf("\nRango de %c hasta %c: \n\n", inicial_inf, inicial_sup);
                    
                    for (i = inicial_inf; i <= inicial_sup; i++){
						rango_por_iniciales(&tablaAutorInicial, &arbol, i);
					}
                    
                    if (arbol != NULL) {
                        printf("\n\nArbol: \n");
						inorden(arbol);
						liberar_arbol(&arbol);
					}
					else
						printf("\nAutor no encontrado.\n");

                    break;
                }
            }
            break;
        }
        case 4: {
            int opcion;
            printf("Ingrese la  opcion 1 o 2: ");
            scanf(" %d", &opcion);
            fflush(stdin);
            int min, max;
        
            if (opcion == 1) {
                printf("Ingrese el anio a buscar: ");
                scanf("%d", &min);
                max = min;
            } else {
                printf("Ingrese el anio minimo: ");
                scanf("%d", &min);
                printf("Ingrese el anio maximo: ");
                scanf("%d", &max);
            }
            for (i = min; i <= max; i++){
                rango_por_fechas(&tablaFecha, &arbol, i);
            }

            if (arbol != NULL) {
                printf("\n\nArbol: \n");
                inorden(arbol);
                liberar_arbol(&arbol);
            } else {
                printf("\nFecha no encontrada.\n");
            }
            break;
        }
          
        case 5: {
            char isbnEliminar[MAX_ISBN];
            printf("Ingrese el ISBN del libro a eliminar: ");
            scanf(" %[^\n]", isbnEliminar);
            
            eliminar_book(&tablaISBN, &tablaTitulo, &tablaTituloInicial, 
                          &tablaAutor, &tablaAutorInicial, &tablaFecha, 
                          isbnEliminar, libros);
            break;
        }
        default:
            break;
        }
    }while(opc != 0);

	liberar_hash(&tablaISBN);
    liberar_hash(&tablaTitulo);
    liberar_hash(&tablaTituloInicial);
    liberar_hash(&tablaAutor);
    liberar_hash(&tablaAutorInicial);
    liberar_hash(&tablaFecha);
    printf("\n\nFIN DE PROGRAMA\n\n");
    return 0;
}


void menu() {

    printf("\n\n----- MENU DE BUSQUEDA -----\n");
    printf("1. Buscar por ISBN\n");
    printf("2. Buscar por Titulo\n");
    printf("   1. Busqueda exacta\n");
    printf("   2. Busqueda por rango de iniciales\n");
    printf("3. Buscar por Autor\n");
    printf("   1. Busqueda exacta\n");
    printf("   2. Busqueda por rango de iniciales\n");
    printf("4. Buscar por Fecha\n");
    printf("   1. Busqueda exacta\n");
    printf("   2. Busqueda por rango\n");
    printf("5. Eliminar Libro\n");
    printf("0. Salir del programa\n");
    printf("Seleccione una opcion: ");

}


