#include "Hash.h"
#include "Arbol.h"
#include <ctype.h>


int folding_cadena(char *cadena){
	int hash = 5381;

	int c; 
	
	while ((c = *cadena++)) {
		hash = ((hash << 5) + hash) + c;
	}
	
	return hash;
}

HashTable* crear_tabla(char key, int (*folding)(char*)) {
	HashTable *nueva = calloc(1, sizeof(HashTable));
	nueva->books = calloc(1, sizeof(Libro*));
	nueva->indices = calloc(1, sizeof(int));
	nueva->size = 1;
	nueva->key = key;
	nueva->folding = folding;
	return nueva;
}

float factor(HashTable hashtable)
{
	return (float)hashtable.stored / hashtable.size;
}


int hash(HashTable hashtable,int key)
{
	key *= (key<0) ? -1:1;
	return key%hashtable.size;
}

int rehash(HashTable hashtable, int index, int i)
{	
	return (index + i*i) % hashtable.size;
}

int get_key(HashTable *hashtable,Libro *book)
{
	switch (hashtable->key)
	{
		case ISBN:
				return hashtable->folding(book->isbn);
		case TITULO:
				return hashtable->folding(book->titulo);
		case TITULO_INICIAL:
				return book->titulo[0]; 
		case AUTOR:
				return hashtable->folding(book->autor);
		case AUTOR_INICIAL:
				return book->autor[0]; 
		case FECHA:
				return book->fecha;				
	}
}
void insertar_indices(HashTable **hashtable, int index) {
	int size = (*hashtable)->stored;	
	unsigned int* aux;
	aux = NULL;
	while(!aux)
		aux = realloc((*hashtable)->indices, sizeof(unsigned int)*size);
	(*hashtable)->indices = aux;
	(*hashtable)->indices[size-1] = index;
}

void insertar(HashTable **hashtable, Libro* book) {

	float carga_factor = factor(**hashtable);
	if (carga_factor > 0.70) {
		*hashtable = remap(*hashtable);
	}
	insertar_book(hashtable, book);
}

void insertar_book(HashTable **hashtable, Libro *book)
{
	int i = 0;
    int key = get_key(*hashtable, book); 
    int index = hash(**hashtable, key); 

	while ((*hashtable)->books[index] != NULL) { 
		if (i >= (*hashtable)->size) {  
			*hashtable = remap(*hashtable);
			index = hash(**hashtable, key); 
			i = 0;
		} else {
			i++;
			index = rehash(**hashtable, index, i);
		}
	}

	(*hashtable)->books[index] = book; 
	(*hashtable)->stored++;
	insertar_indices(hashtable, index);
}


void eliminar_book(HashTable **tablaISBN, HashTable **tablaTitulo, HashTable **tablaTituloInicial,
                  HashTable **tablaAutor, HashTable **tablaAutorInicial, HashTable **tablaFecha,
                  char *isbn, Libro *libros) {
    if (!tablaISBN || !(*tablaISBN) || !isbn || !libros) {
        return;
    }
    
    Libro *libro = buscar_por_isbn(*tablaISBN, isbn);
    if (!libro) {
        printf("\nNo se encontro ningun libro con el ISBN %s\n", isbn);
        return;
    }
    
    eliminar_libro_tabla(tablaISBN, libro);
    eliminar_libro_tabla(tablaTitulo, libro);
    eliminar_libro_tabla(tablaTituloInicial, libro);
    eliminar_libro_tabla(tablaAutor, libro);
    eliminar_libro_tabla(tablaAutorInicial, libro);
    eliminar_libro_tabla(tablaFecha, libro);
    
	
	for (int i = 0; i < CANT_LIBROS; i++) {
        if (strcmp(libros[i].isbn, isbn) == 0) {
            strcpy(libros[i].isbn, " ");
			strcpy(libros[i].titulo, " ");
			strcpy(libros[i].autor, " ");
			libros[i].fecha = 0;
            break;
        }
    }
}

void eliminar_libro_tabla(HashTable **tabla, Libro *book) {
    if (!tabla || !(*tabla) || !book) return;
    
    int key = get_key(*tabla, book);
    int index = hash(**tabla, key);
    int i = 0;
    
    while (i < (*tabla)->size) {
        if ((*tabla)->books[index] == NULL) {
            return;
        }
        
        if ((*tabla)->books[index] == book) {
            (*tabla)->books[index] = NULL;
            (*tabla)->indices[index] = -1;
            (*tabla)->stored--;
			printf("\nLibro eliminado de la tabla\n");
            return;
        }

        i++;
        index = rehash(**tabla, index, i);
    }
}

HashTable* remap(HashTable *hashtable){
	int i;

	int stored = hashtable->stored; 

	HashTable *nueva = crear_tabla(hashtable->key ,  hashtable->folding );

	free(nueva->indices);
	free(nueva->books);

	nueva->size = (stored == 0) ? 2 : (int) ceil( (float)stored*100/60 );

	nueva->books = calloc( nueva->size ,sizeof(Libro*));
	if (stored == 0)
		nueva->indices = calloc(1, sizeof(unsigned int));
	else
		nueva->indices = calloc(stored, sizeof(unsigned int));
	
	nueva->stored = 0;

	
	for( i = 0; i < hashtable->stored ; i++){
		Libro *book = hashtable->books[hashtable->indices[i]];
		insertar_book(&nueva, book);
	}

	free(hashtable->books);
	free(hashtable->indices);
	free(hashtable);

	return nueva;
}


Libro* buscar_por_isbn(HashTable *tablaISBN, char *isbn) {
    if (!tablaISBN || !isbn) {
        return NULL;
    }
    
    int clave = folding_cadena(isbn);
    int index = hash(*tablaISBN, clave);
    int i = 0;

	while (i < tablaISBN->size) {
		if (tablaISBN->books[index] == NULL) {
			return NULL;
		}
        
		if (strcmp(tablaISBN->books[index]->isbn, isbn) == 0) {
			return tablaISBN->books[index];
		}
		i++;
		index = rehash(*tablaISBN, index, i);
	}

	return NULL;
}
Libro* buscar_por_titulo(HashTable *tablaTitulo, char *titulo) {
    if (!tablaTitulo || !titulo) {
        return NULL;
    }
    
    int clave = folding_cadena(titulo);
    int index = hash(*tablaTitulo, clave);
    int i = 0;

    while (i < tablaTitulo->size) {
        if (tablaTitulo->books[index] == NULL) {
            return NULL;
        }
        
        if (strcmp(tablaTitulo->books[index]->titulo, titulo) == 0) {
            return tablaTitulo->books[index];
        }
        
        i++;
        index = rehash(*tablaTitulo, index, i);
    }

    return NULL;
}

void buscar_por_autor(HashTable **hashtable, Nodo **raiz, char *autor) {
	if((*hashtable == NULL) || (autor == NULL))
		return;

	int key = (*hashtable)->folding(autor);
	int index = hash(**hashtable, key);
	int i = 0;

	while( i < (*hashtable)->size && (*hashtable)->books[index] != NULL) {

		if ((*hashtable)->books[index] == NULL)
			return;

		if (strcmp((*hashtable)->books[index]->autor, autor) == 0) {
			insertar_arbolAutor(raiz, (*hashtable)->books[index]);
		}

		i++;

		index = rehash(**hashtable, index, i);
	}
}


void rango_por_iniciales(HashTable **hashtable, Nodo **raiz, char inicial) {

	if ((*hashtable) == NULL)
		return;

	int i = 0;
	int index = hash(**hashtable, inicial);

	while (i < (*hashtable)->size && (*hashtable)->books[index] != NULL) {
		
		if ((*hashtable)->key == TITULO_INICIAL ) {
			if ((*hashtable)->books[index]->titulo[0] == inicial) {
				 insertar_arbolTitulo(raiz, (*hashtable)->books[index]);
			}
		}

		if ((*hashtable)->key == AUTOR_INICIAL) {
			if ((*hashtable)->books[index]->autor[0] == inicial) {
				insertar_arbolAutor(raiz, (*hashtable)->books[index]);
			}
		}
		
		i++;
		index = rehash(**hashtable, index, i);
	}

}

void rango_por_fechas(HashTable **hashtable, Nodo **raiz, int fecha) {
	if ((*hashtable) == NULL)
		return;

	int index = hash(**hashtable, fecha);
	int i = 0;

	while (i < (*hashtable)->size && (*hashtable)->books[index] != NULL) {

		if ((*hashtable)->books[index]->fecha == fecha) {
			insertar_arbolFecha(raiz, (*hashtable)->books[index]);
		}
		i++;
		index = rehash(**hashtable, index, i);
	}
}

void liberar_hash(HashTable **tabla) {
    if (!tabla || !(*tabla)) return;
    
    free((*tabla)->books);
    free((*tabla)->indices);
    
    free(*tabla);
    
    *tabla = NULL;
}
