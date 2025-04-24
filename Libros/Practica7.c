#include <stdio.h>
#include <stdlib.h>

#include "Arbol.h"
#include "Libro.h"

#include <string.h>
#include <ctype.h>
#include <math.h>



int main(void){
	//VARIABLE PARA MANEJAR INDICES
    int i, opcion = 0;
	//PUNTERO QUE ALMACENA LA REFERENCIA DEL INICIO DE LOS DATOS
    Libro *libros;
    libros = obtener_libros();

    Nodo *raizISBN = NULL;
    Nodo *raizTitulo = NULL;
    Nodo *raizAutor = NULL;
    Nodo *raizFechas = NULL;
    
    FiltroCHAR f_titulo;
	FiltroCHAR f_autor;
	FiltroNUM f_fecha;

	f_titulo = (FiltroCHAR){.min='a',.max='z'};
	f_autor = (FiltroCHAR){.min='a',.max='z'};
	f_fecha = (FiltroNUM){.min=0,.max=99999999};
    
    for(i = 0 ; i < CANT_LIBROS ; i++)
    {
        printf("\n ");
        imprimir(libros[i]);
		//AGREGAR A ARBOLES
		//ARBOL ISBN
        crearArbol_ISBN(&raizISBN, &libros[i]);
		//ARBOL TITULO
        crearArbol_Titulo(&raizTitulo, &libros[i]);
		//ARBOL AUTOR
        crearArbol_Autor(&raizAutor, &libros[i]);
		//ARBOL FECHAS
        crearArbol_Fecha(&raizFechas, &libros[i]);
    }
	
	//MENU DE BUSQUEDAS
	do{
        menu();
        scanf(" %d", &opcion);
        printf("\n");

        switch (opcion){
        case 1:
            printf("Ingresa ISBN a buscar: ");
            char isbn[MAX_ISBN];
            fflush(stdin);
            scanf(" %[^\n]", isbn);
            if(isbn[0] == '0'){
                printf("No se puede buscar un libro sin ISBN\n");
                break;
            }
            
            Resultado resultadoISBN = buscarISBN(raizISBN, isbn);
            if(resultadoISBN.igual){
                printf("Libro encontrado:\n");
                imprimir(*resultadoISBN.igual->libro);
                
            }else{
                printf("Los libros mas cercanos son:\n");
                if(resultadoISBN.menor != NULL){
                    printf("Libro menor:\n");
                    imprimir(*resultadoISBN.menor->libro);
                }else{
                    printf("No hay libros menores al buscado\n");
                }

                if(resultadoISBN.mayor != NULL){
                    printf("\nLibro mayor:\n");
                    imprimir(*resultadoISBN.mayor->libro);  
                }else{
                    printf("No hay libros mayores al buscado\n");
                }
            }
            break;

        case 2:{
            printf("[1] Buscar por Titulo\n");
            printf("[2] Buscar en rango de Titulo\n");
            printf("Opcion -> ");
            int opcionTitulo;
            scanf(" %d", &opcionTitulo);
            if(opcionTitulo == 1){

                char titulo[MAX_TITULO];
                printf("Ingresa Titulo a buscar: ");
                fflush(stdin);
                scanf(" %[^\n]", titulo);

                if(titulo[0] == '0'){
                    printf("No se puede buscar un libro sin titulo\n");
                    break;
                }
                int encontrados = imprimirTitulo(raizTitulo, titulo);

                if (encontrados == 0) {
                    Resultado resultado = buscarTitulo(raizTitulo, titulo);
                    Nodo *cercano = NULL;
                
                    if (resultado.menor && resultado.mayor) {
                        cercano = (strcmp(titulo, resultado.menor->libro->titulo) - strcmp(resultado.mayor->libro->titulo, titulo) < 0)
                                    ? resultado.menor : resultado.mayor;
                    } else if (resultado.menor) {
                        cercano = resultado.menor;
                    } else if (resultado.mayor) {
                        cercano = resultado.mayor;
                    }
                
                    if (cercano) {
                        printf("\nTitulo no encontrado. Mostrando libro con el titulo mas cercano:\n");
                        imprimir(*(cercano->libro));
                    } else {
                        printf("No se encontró ningún título ni cercano.\n");
                    }
                }
            }else if(opcionTitulo == 2){
                printf("Ingresa rango de Titulo a buscar: ");
                fflush(stdin);
                captura_FiltroCHAR(&f_titulo);
                printf("\nFILTRO TITULO -> MIN: %c MAX: %c",f_titulo.min,f_titulo.max);
                printf("\n\nLibros en rango:\n");
                subconjuntoTitulo(raizTitulo, f_titulo);
                
            }else{
                printf("Opcion no valida\n");
            }
            
            break;
        }

        case 3: {
            printf("[1] Buscar por Autor\n");
            printf("[2] Buscar en rango de Autor\n");
            printf("Opcion -> ");
            int opcionAutor;
            scanf(" %d", &opcionAutor);
        
            if (opcionAutor == 1) {
                char autor[MAX_AUTOR];
                printf("Ingresa Autor a buscar: ");
                fflush(stdin);
                scanf(" %[^\n]", autor);
                
                if (autor[0] == '0') {
                    printf("No se puede buscar un libro sin autor\n");
                    break;
                }

                int encontrados = imprimirAutor(raizAutor, autor);

                if (encontrados == 0) {

                    Resultado resultado = buscarAutor(raizAutor, autor);
                    Nodo *cercano = NULL;
                
                    if (resultado.menor && resultado.mayor) {
                        cercano = (strcmp(autor, resultado.menor->libro->autor) - strcmp(resultado.mayor->libro->autor, autor) < 0)
                                    ? resultado.menor : resultado.mayor;
                    } else if (resultado.menor) {
                        cercano = resultado.menor;
                    } else if (resultado.mayor) {
                        cercano = resultado.mayor;
                    }
                
                    if (cercano) {
                        printf("\nAutor no encontrado. Mostrando libro del autor mas cercano: \n");
                        imprimir(*(cercano->libro));
                    } else {
                        printf("No se encontró ningún autor ni cercano.\n");
                    }
                }

            } else if (opcionAutor == 2) {
                printf("Ingresa rango de Autor a buscar: ");
                fflush(stdin);
                captura_FiltroCHAR(&f_autor);
                printf("\nFILTRO AUTOR -> MIN: %c MAX: %c", f_autor.min, f_autor.max);
                printf("\n\nLibros en rango:\n");
                subconjuntoAutor(raizAutor, f_autor);
            } else {
                printf("\nOpcion no valida. Regresando al menu principal.\n");
            }
            break;
        }
        case 4:{
            printf("[1] Buscar por Fecha\n");
            printf("[2] Buscar en rango de Fecha\n");
            printf("Opcion -> ");
            int opcionFecha;
            scanf(" %d", &opcionFecha);
            if(opcionFecha == 1){
                int fecha;
                printf("Ingresa Fecha a buscar: ");
                fflush(stdin);
                scanf(" %d", &fecha);

                if(fecha == 0){
                    printf("No se puede buscar un libro sin fecha\n");
                    break;
                }
                buscarFecha(raizFechas, fecha);
                
            }else if(opcionFecha == 2){
                printf("Ingresa rango de Fecha a buscar: ");
                fflush(stdin);
                captura_FiltroNUM(&f_fecha);
                printf("\nFILTRO FECHA -> MIN: %d MAX: %d",f_fecha.min,f_fecha.max);
                printf("\n\nLibros en rango:\n");
                subconjuntoFecha(raizFechas, f_fecha);

            }else{
                printf("Opcion no valida\n");
            }
            break;
        }
        case 5:
            printf("Saliendo del programa...\n");
            if(raizISBN == NULL && raizTitulo == NULL && raizAutor == NULL && raizFechas == NULL){
                printf("No hay arboles creados\n");
                break;
            }
            
            liberar_arbol(&raizISBN);
            liberar_arbol(&raizTitulo);
            liberar_arbol(&raizAutor);
            liberar_arbol(&raizFechas);
            printf("Memoria liberada\n");

            break;

        default:
            printf("\nOpcion no valida\n");
            printf("Por favor elige una opcion valida\n");
            break;
        }

    }while(opcion != 5);
	
    printf("\n\nFIN DE PROGRAMA\n\n");
    return 0;
}

void menu(){
    printf("\n=============================================================\n");
    printf("Elige una opcion\n");
    printf("\n [1]Buscar por ISBN");
    printf("\n [2]Buscar por Titulo");
    printf("\n [3]Buscar por Autor");
    printf("\n [4]Buscar por Fecha");
    printf("\n [5]Terminar programa\n\n");
    printf("Opcion-> ");

}