
#include "Header.h"

void realizar_operacion(Monton *monton, int opc) {
    switch (opc) {
        case 0: { 
            invertir_heap(monton);
            break;
        }

        case 1: {
            if(monton->cantidad == 0)
                break;
            printf("Mostrando cola de impresion...\n");
            mostrar_cola(monton);
            break;
        }

        case 2: { 
            Documento doc;

			limpiar_buffer();
            printf("\nNombre del archivo: ");
            doc.nombre = captura_cadena();
            printf("\nAutor del archivo: ");
            doc.autor = captura_cadena();
            printf("\nNumero de paginas: ");
            scanf(" %d", &doc.paginas);
            push_Heap(monton, doc);
            break;
        }

        case 3: { 
            pop_Heap(monton);
            break;
        }

        case 4: { 
            if (monton->cantidad == 0) {
                printf("El heap esta vacio. No hay archivos para eliminar.\n");
                break;
            }

            printf("Archivos en la cola de impresion:\n");
            mostrar_cola(monton);

            int indice;
            printf("Selecciona el indice del archivo a eliminar (1 a %d): ", monton->cantidad);
            scanf(" %d", &indice);

            if (indice < 1 || indice > monton->cantidad) {
                printf("Indice no valido. Operacion cancelada.\n");
                break;
            }

            indice--;

            liberar_cadenas(&monton->nodos[indice]->documento);
            free(monton->nodos[indice]);

            for (int i = indice; i < monton->cantidad - 1; i++) {
                monton->nodos[i] = monton->nodos[i + 1];
            }

            monton->cantidad--;

            if (monton->cantidad > 0) {
                Nodo **temp = NULL;
                while (!temp) {
                    temp = realloc(monton->nodos, sizeof(Nodo*) * monton->cantidad);
                }
                monton->nodos = temp;

                heapify(monton);
                enlazar_nodos(monton);
            } else {
                free(monton->nodos);
                monton->nodos = NULL;
            }

            printf("Archivo eliminado correctamente.\n");
            break;
        }

        case 5: { 
			if(monton->cantidad == 0) {
				printf("El heap esta vacio. \n");
				break;
			}
            liberar_heap(monton);
            break;
        }

        case 6: { 
    		printf("Terminando programa...\n");

    		if (monton->nodos != NULL) {
        		printf("Liberando memoria del heap...\n");
        		liberar_heap(monton);
    		}

 			free(monton);
    		monton = NULL;

    		printf("Programa terminado correctamente.\n");
    		break;
		}

        default:
            printf("Opcion no valida.\n");
            break;
    }

    if (monton->cantidad > 0) {
        printf("\nEstado del heap despues de la operacion, primeros 5:\n");
        printf("Como arreglo:\n");
        imprimir_heap(monton);
        printf("\nComo arbol:\n");
        imprimir_arbol(monton->nodos[0], 0);
    } else {
        printf("\nEl heap esta vacio. No hay nada que mostrar.\n");
    }
}

void mostrar_cola(Monton *monton){
	int i;
	for(i = 0; i < monton->cantidad; i++){
		printf("[%d] Nombre: %s, Autor: %s, Paginas: %d\n", i+1 , monton->nodos[i]->documento.nombre, monton->nodos[i]->documento.autor, monton->nodos[i]->documento.paginas);
	}
}

void push_Heap(Monton *monton, Documento documento){

	Nodo **aux;
	Nodo *nuevo = crear_nodo(documento);
	monton->cantidad++;

	aux = NULL;
	while(!aux)
		aux = realloc(monton->nodos, sizeof(Nodo*) * monton->cantidad);
	monton->nodos = aux;

	monton->nodos[monton->cantidad - 1] = nuevo;
	heapify(monton);
	enlazar_nodos(monton);

}

void heapify_minimo(Monton *monton, int i){
	int menor = i;
	int izq = 2 * i + 1;
	int dch = 2 * i + 2;

	if(izq < monton->cantidad && monton->nodos[izq]->documento.paginas < monton->nodos[menor]->documento.paginas)
		menor = izq;
	if(dch < monton->cantidad && monton->nodos[dch]->documento.paginas < monton->nodos[menor]->documento.paginas)
		menor = dch;
	if(menor != i){
		Nodo *aux = monton->nodos[i];
		monton->nodos[i] = monton->nodos[menor];
		monton->nodos[menor] = aux;
		heapify_minimo(monton, menor);
	}
}

void heapify_maximo(Monton *monton, int i){
	int mayor = i;
	int izq = 2 * i + 1;
	int dch = 2 * i + 2;

	if(izq < monton->cantidad && monton->nodos[izq]->documento.paginas > monton->nodos[mayor]->documento.paginas)
		mayor = izq;
	if(dch < monton->cantidad && monton->nodos[dch]->documento.paginas > monton->nodos[mayor]->documento.paginas)
		mayor = dch;
	if(mayor != i){
		Nodo *aux = monton->nodos[i];
		monton->nodos[i] = monton->nodos[mayor];
		monton->nodos[mayor] = aux;
		heapify_maximo(monton, mayor);
	}
}

void heapify(Monton *monton) {
    for (int i = (monton->cantidad / 2) - 1; i >= 0; i--) {
        if (monton->tipo == MAXIMO)
            heapify_maximo(monton, i);
        else if (monton->tipo == MINIMO)
            heapify_minimo(monton, i);
    }

    enlazar_nodos(monton); 
}


void pop_Heap(Monton *monton) {
    if (monton->cantidad == 0) {
        printf("El heap esta vacio.\n");
        return;
    }

    Nodo *aux = monton->nodos[0];
    printf("Procesando archivo...\nNombre: %s, Autor: %s, Paginas: %d\n", aux->documento.nombre, aux->documento.autor, aux->documento.paginas);
    liberar_cadenas(&aux->documento);

    monton->nodos[0] = monton->nodos[monton->cantidad - 1];
    monton->cantidad--;
    free(aux);

    if (monton->cantidad == 0) {
        free(monton->nodos);
        monton->nodos = NULL;
        return;
    }

    Nodo **temp = NULL;
    while (!temp) {
        temp = realloc(monton->nodos, sizeof(Nodo*) * monton->cantidad);
    }
    monton->nodos = temp;

    heapify(monton);
    enlazar_nodos(monton);
}

void invertir_heap(Monton *monton) {
    if (monton->tipo == MINIMO) {
        monton->tipo = MAXIMO; 
        printf("Cambiando a heap maximo.\n");
    } else {
        monton->tipo = MINIMO; 
        printf("Cambiando a heap minimo.\n");
    }
    heapify(monton); 
	enlazar_nodos(monton); 	
}

void imprimir_heap(Monton *monton){
	int i;
	for(i = 0; i < monton->cantidad && i < 5; i++){
		printf("[%d] Nombre: %s, Autor: %s, Paginas: %d\n", i+1 , monton->nodos[i]->documento.nombre,monton->nodos[i]->documento.autor,monton->nodos[i]->documento.paginas);
	}
}



void imprimir_arbol(Nodo *nodo, int nivel) {
    int i;
    if (nodo != NULL) {
        printf(" Nombre: %s, Autor: %s, Paginas: %d", nodo->documento.nombre, nodo->documento.autor, 
		nodo->documento.paginas);

        if (nodo->dch) {
            printf("\n");
            for (i = 0; i < nivel + 1; i++) {
                if (i == nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1);
        }

        if (nodo->izq) {
            printf("\n");
            for (i = 0; i < nivel + 1; i++) {
                if (i == nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1);
        }
    }
}

void liberar_heap(Monton *monton) {
    if (monton->nodos != NULL) { 
        for (int i = 0; i < monton->cantidad; i++) {
            if (monton->nodos[i] != NULL) { 
                liberar_nodo(monton->nodos[i]);
                monton->nodos[i] = NULL; 
            }
        }
        free(monton->nodos); 
        monton->nodos = NULL;
    }
    monton->cantidad = 0;
}

void liberar_nodo(Nodo *nodo){
	if(nodo){
		liberar_cadenas(&nodo->documento);
		free(nodo);
	}
}

Nodo * crear_nodo(Documento documento){
	Nodo *nuevo = calloc(1, sizeof(Nodo));
	nuevo->documento = documento;
	nuevo->izq = NULL;
	nuevo->dch = NULL;
	return nuevo;
}

void limpiar_buffer(void)
{
	char c;
	while( (c=getchar()) != '\n' && c!=EOF);
}

void reemplazar(char *cadena,char og,char rem)
{
	//REEMPLAZO DE UN UNICO CARACTER
	while( *cadena != '\0')
	{
		if (*cadena == og)
		{
			*cadena = rem;
			break;
		}
		cadena++;
	}
}

void setup_buffer(char *buffer) 
{
	int i;
	for(i = 0; i < TEXT_MAX; i++)
		buffer[i] = '\0';
	if(TEXT_MAX >=2)
		buffer[TEXT_MAX-2] = '\n';
}

char *captura_cadena(void)
{
	char buffer[TEXT_MAX];
	char *cadena;
	setup_buffer(buffer); //RELACIONADO CON LIMPIAR BUFFER
	fgets(buffer,TEXT_MAX,stdin);
	if(TEXT_MAX>=2 && buffer[TEXT_MAX-2]!='\n')
		limpiar_buffer(); //SOLO CUANDO ES NECESARIO	
	reemplazar(buffer,'\n','\0');
	cadena = NULL;
	while(!cadena)
		cadena = strdup(buffer); //COPIA EN MEMORIA DINAMICA
	return cadena;
}

void liberar_cadenas(Documento* documento)
{
	free(documento->nombre);
	free(documento->autor);
	documento->nombre = NULL;
	documento->autor = NULL;	
}


void enlazar_nodos(Monton *monton) {
    if (monton->cantidad == 0) {
        printf("No hay nodos para enlazar.\n");
        return;
    }

    for (int i = 0; i < monton->cantidad; i++) {
        int indice_izq = 2 * i + 1;
        int indice_dch = 2 * i + 2;

        if (indice_izq < monton->cantidad) {
            monton->nodos[i]->izq = monton->nodos[indice_izq];
        } else {
            monton->nodos[i]->izq = NULL; 
        }

		if (indice_dch < monton->cantidad) {
            monton->nodos[i]->dch = monton->nodos[indice_dch];
        } else {
            monton->nodos[i]->dch = NULL; 
        }

    }
}

