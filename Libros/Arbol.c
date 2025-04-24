
#include "Arbol.h"
#include "Libro.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>


void crearArbol_ISBN(Nodo **raiz, Libro *libro){
    if(*raiz == NULL){
        *raiz = crear_nodo(libro);
    }
    else if(strcmp((*raiz)->libro->isbn, libro->isbn) > 0){
        crearArbol_ISBN(&(*raiz)->izq, libro);
    }
    else{
        crearArbol_ISBN(&(*raiz)->dch, libro);
    }
}

void crearArbol_Titulo(Nodo **raiz, Libro *libro)
{
    if(*raiz == NULL){
        *raiz = crear_nodo(libro);
    }
    else if(strcmp((*raiz)->libro->titulo, libro->titulo) > 0){
        crearArbol_Titulo(&(*raiz)->izq, libro);
    }
    else{
        crearArbol_Titulo(&(*raiz)->dch, libro);
    }
}

void crearArbol_Autor(Nodo **raiz, Libro *libro)
{
    if(*raiz == NULL){
        *raiz = crear_nodo(libro);
    }
    else if(strcmp((*raiz)->libro->autor, libro->autor) > 0){
        crearArbol_Autor(&(*raiz)->izq, libro);
    }
    else{
        crearArbol_Autor(&(*raiz)->dch, libro);
    }
}

void crearArbol_Fecha(Nodo **raiz, Libro *libro)
{
    if (*raiz == NULL) {
        *raiz = crear_nodo(libro);
    }
    else if ((*raiz)->libro->fecha > libro->fecha) {
        crearArbol_Fecha(&(*raiz)->izq, libro);
    }
    else {
        crearArbol_Fecha(&(*raiz)->dch, libro);
    }
}


Resultado buscarISBN(Nodo *raiz, char *isbn){
    Resultado resultado = {NULL, NULL, NULL};
    
    if (raiz == NULL) return resultado;
    
    if (strcmp(raiz->libro->isbn, isbn) == 0) {
        resultado.igual = raiz;
        return resultado;
    }
    
    if (strcmp(raiz->libro->isbn, isbn) > 0) {
        resultado = buscarISBN(raiz->izq, isbn);
        if (resultado.mayor == NULL) {
            resultado.mayor = raiz; 
        }

    } else {
        resultado = buscarISBN(raiz->dch, isbn);
        if (resultado.menor == NULL) {
            resultado.menor = raiz; 
        }
    }
    
    return resultado;
}

Resultado buscarTitulo(Nodo *raiz, char *titulo){
    Resultado resultado = {NULL, NULL, NULL};
    
    if(raiz == NULL) return resultado;
    
    if(strcmp(raiz->libro->titulo, titulo) == 0){
        resultado.igual = raiz;
        return resultado;
    }
    
    if(strcmp(raiz->libro->titulo, titulo) > 0){
        resultado = buscarTitulo(raiz->izq, titulo);
        if(resultado.mayor == NULL){
            resultado.mayor = raiz; 
        }
    
    }else{
        resultado = buscarTitulo(raiz->dch, titulo);
        if(resultado.menor == NULL){
            resultado.menor = raiz; 
        }
    }
    
    return resultado;
}

int imprimirTitulo(Nodo *raiz, char *titulo) {
    if (raiz == NULL) return 0;

    int encontrados = 0;
    encontrados += imprimirTitulo(raiz->izq, titulo);

    if (strcmp(raiz->libro->titulo, titulo) == 0) {
        imprimir(*raiz->libro);
        printf("\n");
        encontrados++;
    }

    encontrados += imprimirTitulo(raiz->dch, titulo);

    
    return encontrados;
}


void subconjuntoTitulo(Nodo *raizTitulo, FiltroCHAR filtro){

    if (!raizTitulo) return;

    if (raizTitulo->libro->titulo[0] >= filtro.min && raizTitulo->libro->titulo[0] <= filtro.max)
    {
        subconjuntoTitulo(raizTitulo->izq, filtro);

        imprimir(*raizTitulo->libro);
        printf("\n");

        subconjuntoTitulo(raizTitulo->dch, filtro);
    }

    else
    {
        if (raizTitulo->libro->titulo[0] < filtro.min)
            subconjuntoTitulo(raizTitulo->dch, filtro);

        if (raizTitulo->libro->titulo[0] > filtro.max)
            subconjuntoTitulo(raizTitulo->izq, filtro);
    }
}

Resultado buscarAutor(Nodo *raiz, char *autor)
{
    Resultado resultado = {NULL, NULL, NULL};
    
    if(raiz == NULL) return resultado;
    
    if(strcmp(raiz->libro->autor, autor) == 0){
        resultado.igual = raiz;
        return resultado;
    }
    
    if(strcmp(raiz->libro->autor, autor) > 0){
        resultado = buscarAutor(raiz->izq, autor);
        if(resultado.mayor == NULL){
            resultado.mayor = raiz; 
        }
    
    }else{
        resultado = buscarAutor(raiz->dch, autor);
        if(resultado.menor == NULL){
            resultado.menor = raiz; 
        }
    }
    
    return resultado;
}

int imprimirAutor(Nodo *raiz, char *autor) {
    if (raiz == NULL) return 0;

    int encontrados = 0;
    encontrados += imprimirAutor(raiz->izq, autor);

    if (strcmp(raiz->libro->autor, autor) == 0) {
        imprimir(*raiz->libro);
        printf("\n");
        encontrados++;
    }

    encontrados += imprimirAutor(raiz->dch, autor);

    
    return encontrados;
}


void subconjuntoAutor(Nodo *raizAutor, FiltroCHAR filtro){

    if (!raizAutor) return;

    if (raizAutor->libro->autor[0] >= filtro.min && raizAutor->libro->autor[0] <= filtro.max)
    {
        subconjuntoAutor(raizAutor->izq, filtro);

        imprimir(*raizAutor->libro);
        printf("\n");

        subconjuntoAutor(raizAutor->dch, filtro);
    }

    else
    {
        if (raizAutor->libro->autor[0] < filtro.min)
            subconjuntoAutor(raizAutor->dch, filtro);

        if (raizAutor->libro->autor[0] > filtro.max)
            subconjuntoAutor(raizAutor->izq, filtro);
    }
}

void buscarFecha(Nodo *raiz, int fecha) {
    if (raiz == NULL) return;

    buscarFecha(raiz->izq, fecha);

    if (raiz->libro->fecha == fecha) {
        imprimir(*raiz->libro);
        printf("\n");
    } 

    buscarFecha(raiz->dch, fecha);
}


void subconjuntoFecha(Nodo *raizFechas, FiltroNUM filtro){

    if (!raizFechas) return;

    if (raizFechas->libro->fecha >= filtro.min && raizFechas->libro->fecha <= filtro.max)
    {
        subconjuntoFecha(raizFechas->izq, filtro);

        imprimir(*raizFechas->libro);
        printf("\n");

        subconjuntoFecha(raizFechas->dch, filtro);
    }

    else
    {
        if (raizFechas->libro->fecha < filtro.min)
            subconjuntoFecha(raizFechas->dch, filtro);

        if (raizFechas->libro->fecha > filtro.max)
            subconjuntoFecha(raizFechas->izq, filtro);
    }
}

Nodo *crear_nodo(Libro *libro){
    Nodo *nuevo = (Nodo*)calloc(1, sizeof(Nodo));
    nuevo->libro = libro;
    nuevo->izq = NULL;
    nuevo->dch = NULL;
    return nuevo;
}

void liberar_arbol(Nodo **raiz)
{
    if(*raiz != NULL){
        liberar_arbol(&(*raiz)->izq);
        liberar_arbol(&(*raiz)->dch);
        free(*raiz);
        *raiz = NULL;
    }
}

