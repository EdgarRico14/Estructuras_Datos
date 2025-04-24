
#include "Estructuras.h"

Alumno crear_alumno(int m,int s,char* n,char* a,int y,int mt,int d)
{
	Alumno alumno;
	alumno.matricula = m;
	alumno.semestre = s;
	alumno.nombre = n;
	alumno.apellido = a;
	alumno.fecha.year = y;
	alumno.fecha.month = mt;
	alumno.fecha.day = d;
	return alumno;	
}

void imprimir_alumno(Alumno alumno)
{
	printf(" %09d",alumno.matricula);
	printf(" | %02d",alumno.semestre);
	printf(" | %-15s",alumno.apellido);
	printf("  %-15s",alumno.nombre);
	printf(" | %04d",alumno.fecha.year);
	printf(" %02d",alumno.fecha.month);
	printf(" %02d",alumno.fecha.day);
}


void inicializar_lista(Lista* lista)
{
	lista->inicio = NULL;
	lista->fin = NULL;
	lista->cantidad = 0;
}

void recorrer_lista(Lista lista)
{
	Nodo* p = lista.inicio;
	if (p == NULL) {
        printf("La lista esta vacia\n");
        return;
    }
	while(p!=NULL)
	{
		printf("\n");
		imprimir_alumno(*(p->alumno));
		p= p->siguiente;
	}
	printf("\n\nCantidad de alumnos: %d", lista.cantidad);
}
void recorrer_lista_descendente(Lista lista)
{
	Nodo* p = lista.fin;
	
	while(p!=NULL)
	{
		printf("\n");
		imprimir_alumno(*(p->alumno));
		p= p->anterior;
	}
}

Nodo* crear_Nodo(Alumno* alumno)
{
	Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->anterior = NULL;
    nuevo_nodo->alumno = alumno;
    nuevo_nodo->siguiente = NULL;
    return nuevo_nodo;
}
void agregar_alumno(Lista* lista, Alumno* alumno)
{
    Nodo *nuevo_nodo = crear_Nodo(alumno);
	if (nuevo_nodo == NULL) {
        printf("Error al crear el nodo\n");
        return;
    }
    if (lista->inicio == NULL) {
        lista->inicio = nuevo_nodo;
        lista->fin = nuevo_nodo;
    } else {
        lista->fin->siguiente = nuevo_nodo;
        nuevo_nodo -> anterior = lista -> fin;
        lista->fin = nuevo_nodo;
    }
    lista->cantidad++;
}

void agregar_alumno_ordenado(Lista* lista, Alumno* alumno) {
    Nodo *nuevo = crear_Nodo(alumno);
    Nodo *actual = lista->inicio;

    if (actual == NULL) {
        lista->inicio = nuevo;
        lista->fin = nuevo;

    } else {
        
        while (actual != NULL && strcmp(nuevo->alumno->apellido, actual->alumno->apellido) > 0) {
            actual = actual->siguiente;
        }
        
        if (actual == lista->inicio) {
            nuevo->siguiente = lista->inicio;
            lista->inicio->anterior = nuevo;
            lista->inicio = nuevo;

        } else if (actual == NULL) {
            nuevo->anterior = lista->fin;
            lista->fin->siguiente = nuevo;
            lista->fin = nuevo;

        } else {
            nuevo->siguiente = actual;
            nuevo->anterior = actual->anterior;
            actual->anterior->siguiente = nuevo;
            actual->anterior = nuevo;
        }
    }

    lista->cantidad++;
}


void eliminar_lista(Lista* lista)
{
    Nodo *actual = lista->inicio;
    Nodo *temp;
    while (actual != NULL) {
        temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    printf("\nLista vaciada\n");	
}


int alumno_existe(Alumno* alumno,Lista lista)
{
    Nodo *actual = lista.inicio;
    while (actual != NULL) {
         if (actual->alumno->matricula == alumno->matricula) {
            return 1;
        } 
        actual = actual->siguiente;
    }
    return 0;
}

