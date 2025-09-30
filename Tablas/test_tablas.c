
#include "Unity/unity.h"
#include "Hash.h"
#include "Arbol.h"
#include "Libro.h"
#include <string.h>
#include <stdio.h>

#ifndef NULL
#define NULL ((void*)0)
#endif
// Prueba estructural: eliminar libro de la tabla hash
void test_HashEliminar_libro(void) {
    HashTable *tabla = crear_tabla(ISBN, folding_cadena);
    Libro *libros = obtener_libros();
    insertar(&tabla, &libros[0]);
    insertar(&tabla, &libros[1]);
    int i, encontrados = 0;
    eliminar_libro_tabla(&tabla, &libros[0]);
    for(i = 0; i < tabla->size; i++) {
        if(tabla->books[i] != NULL && strcmp(tabla->books[i]->isbn, libros[0].isbn) == 0) encontrados++;
    }
    TEST_ASSERT_EQUAL_INT(0, encontrados); // El libro debe eliminarse
}

// Prueba estructural: insertar en árbol por autor
void test_insertar_arbolAutor(void) {
    Nodo *raiz = NULL;
    Libro *libros = obtener_libros();
    insertar_arbolAutor(&raiz, &libros[0]); // "Miguel de Cervantes"
    insertar_arbolAutor(&raiz, &libros[2]); // "Harper Lee"
    // "Harper Lee" debe ir a la izquierda de "Miguel de Cervantes" (alfabéticamente)
    TEST_ASSERT_NOT_NULL(raiz);
    TEST_ASSERT_NOT_NULL(raiz->izq);
    TEST_ASSERT_EQUAL_STRING(libros[2].autor, raiz->izq->libro->autor);
}

// Prueba estructural: imprimir libro no disponible
void test_imprimir_libro_no_disponible(void) {
    char buffer[200];
    FILE *tmp = freopen("test_output.txt", "w+", stdout);
    Libro libro = {"456", "TituloND", "AutorND", 2021, 0};
    imprimir(libro);
    fflush(stdout);
    freopen("CON", "w", stdout);
    FILE *f = fopen("test_output.txt", "r");
    fgets(buffer, sizeof(buffer), f);
    fclose(f);
    remove("test_output.txt");
    TEST_ASSERT_NOT_NULL(strstr(buffer, "PRESTADO"));
}

// Prueba estructural: obtener_libros retorna arreglo válido
void test_obtener_libros(void) {
    Libro *libros = obtener_libros();
    TEST_ASSERT_NOT_NULL(libros);
    TEST_ASSERT_TRUE(strlen(libros[0].isbn) > 0);
    TEST_ASSERT_TRUE(strlen(libros[0].titulo) > 0);
}




// Prueba estructural: insertar en HashTable y validar remapeo
void test_HashInsert_remap(void) {
    HashTable *tabla = crear_tabla(ISBN, folding_cadena);
    Libro *libros = obtener_libros();
    int i;
    // Insertar suficientes libros para forzar remapeo (factor de carga > 0.7)
    for(i = 0; i < 5; i++) {
        insertar(&tabla, &libros[i]);
    }
    // Validar que la tabla creció (size > 1)
    TEST_ASSERT_GREATER_THAN(1, tabla->size);
    // Validar que los libros están almacenados
    int encontrados = 0;
    for(i = 0; i < tabla->size; i++) {
        if(tabla->books[i] != NULL) encontrados++;
    }
    TEST_ASSERT_EQUAL_INT(5, encontrados);
}

// Prueba estructural: insertar en árbol binario por título
void test_insertar_arbolTitulo(void) {
    Nodo *raiz = NULL;
    Libro *libros = obtener_libros();
    // Insertar dos libros con títulos distintos
    insertar_arbolTitulo(&raiz, &libros[0]); // "El Quijote"
    insertar_arbolTitulo(&raiz, &libros[1]); // "1984"
    // El libro "1984" debe estar a la izquierda de "El Quijote"
    TEST_ASSERT_NOT_NULL(raiz);
    TEST_ASSERT_NOT_NULL(raiz->izq);
    TEST_ASSERT_EQUAL_STRING(libros[1].titulo, raiz->izq->libro->titulo);
    // Insertar un libro con el mismo título pero fecha menor
    Libro libro_igual = libros[0];
    libro_igual.fecha = 1500;
    insertar_arbolTitulo(&raiz, &libro_igual);
    // Debe insertarse a la izquierda del nodo raíz
    TEST_ASSERT_NOT_NULL(raiz->izq->izq);
    TEST_ASSERT_EQUAL_INT(1500, raiz->izq->izq->libro->fecha);
}

// Prueba estructural: imprimir libro (validar flujo de impresión)
void test_imprimir_libro(void) {
    // Redirigir stdout a un buffer temporal
    char buffer[200];
    FILE *tmp = freopen("test_output.txt", "w+", stdout);
    Libro libro = {"123", "TituloTest", "AutorTest", 2020, 1};
    imprimir(libro);
    fflush(stdout);
    freopen("CON", "w", stdout); // Restaurar stdout
    // Leer el archivo temporal
    FILE *f = fopen("test_output.txt", "r");
    fgets(buffer, sizeof(buffer), f);
    fclose(f);
    remove("test_output.txt");
    // Validar que el flujo contiene los datos esperados
    TEST_ASSERT_NOT_NULL(strstr(buffer, "TituloTest"));
    TEST_ASSERT_NOT_NULL(strstr(buffer, "AutorTest"));
    TEST_ASSERT_NOT_NULL(strstr(buffer, "DISPONIBLE"));
}

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_HashInsert_remap);
    RUN_TEST(test_insertar_arbolTitulo);
    RUN_TEST(test_imprimir_libro);
    RUN_TEST(test_HashEliminar_libro);
    RUN_TEST(test_insertar_arbolAutor);
    RUN_TEST(test_imprimir_libro_no_disponible);
    RUN_TEST(test_obtener_libros);
    return UNITY_END();
}
