#include "unity.h"
#include "Arbol.h"
#include "Hash.h"
#include "Libro.h"

// Variables globales para las pruebas
Nodo *raiz = NULL;
HashTable *tabla = NULL;
Libro *libros = NULL;

void setUp(void) {
    // Inicializar libros y estructuras
    libros = obtener_libros();
    tabla = crear_tabla('t', folding_cadena);
}

void tearDown(void) {
    // Liberar memoria
    free(tabla->books);
    free(tabla->indices);
    free(tabla);
    raiz = NULL;
}

void test_insertar_libros_en_arbol(void) {
    insertar_arbolTitulo(&raiz, &libros[0]);
    insertar_arbolTitulo(&raiz, &libros[1]);
    TEST_ASSERT_NOT_NULL(raiz);
    TEST_ASSERT_EQUAL_STRING("El Quijote", raiz->libro->titulo);
    TEST_ASSERT_EQUAL_STRING("1984", raiz->izq->libro->titulo);
}

void test_insertar_libros_en_tabla_hash(void) {
    tabla->stored = 0;
    insertar_en_tabla(tabla, &libros[0]);
    insertar_en_tabla(tabla, &libros[1]);
    TEST_ASSERT_EQUAL(2, tabla->stored);
    TEST_ASSERT_EQUAL_STRING("El Quijote", tabla->books[0]->titulo);
}

void test_buscar_libro_en_estructuras(void) {
    insertar_arbolTitulo(&raiz, &libros[0]);
    insertar_en_tabla(tabla, &libros[0]);

    Nodo *nodo_encontrado = buscar_arbolTitulo(raiz, "El Quijote");
    TEST_ASSERT_NOT_NULL(nodo_encontrado);
    TEST_ASSERT_EQUAL_STRING("El Quijote", nodo_encontrado->libro->titulo);

    int indice = buscar_en_tabla(tabla, "El Quijote");
    TEST_ASSERT_NOT_EQUAL(-1, indice);
    TEST_ASSERT_EQUAL_STRING("El Quijote", tabla->books[indice]->titulo);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_insertar_libros_en_arbol);
    RUN_TEST(test_insertar_libros_en_tabla_hash);
    RUN_TEST(test_buscar_libro_en_estructuras);
    return UNITY_END();
}