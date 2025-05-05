
#include "Header.h"

void realizar_operacion(Monton *monton, int opc) {
    printf("\nEstado del heap antes de la operación, primeros 5:\n");
    printf("Como arreglo:\n");
    imprimir_heap(monton);
    printf("\nComo árbol:\n");
    imprimir_arbol(monton->nodos[0], 0);

    switch (opc) {

		case 0: { // Cambiar tipo de heap
			invertir_heap(monton);
			break;
		}

		case 1: { // Mostrar cola de impresión
			printf("Mostrando cola de impresión...\n");
			mostrar_cola(monton);
			break;
		}

        case 2: { // Agregar archivo
            Documento doc;
            doc.nombre = captura_cadena();
            doc.autor = captura_cadena();
            printf("Número de páginas: ");
            scanf("%d", &doc.paginas);
            push_Heap(monton, doc);
            break;
        }

        case 3: { // Procesar/Imprimir archivo
            pop_Heap(monton);
            break;
        }
        case 4: { // Eliminar archivo
			

            break;
        }
        case 5: { // Eliminar todos los archivos
            liberar_heap(monton);
            break;
        }
		case 6: { // Terminar programa
			printf("Terminando programa...\n");
			liberar_heap(monton);
			free(monton);
			monton = NULL;
			break;
		}
        default:
            printf("Opción no válida.\n");
            break;
    }

    printf("\nEstado del heap después de la operación, primeros 5:\n");
    printf("Como arreglo:\n");
    imprimir_heap(monton);
    printf("\nComo árbol:\n");
    imprimir_arbol(monton->nodos[0], 0);
}

void mostrar_cola(Monton *monton){
	int i;
	for(i = 0; i < monton->cantidad; i++){
		printf("[%d] Nombre: %s, Autor: %s, Paginas: %d\n", i+1 , monton->nodos[i]->documento.nombre,monton->nodos[i]->documento.autor,monton->nodos[i]->documento.paginas);
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

void heapify(Monton *monton){
	if(monton->tipo == MAXIMO)
		heapify_maximo(monton, 0);
	else if(monton->tipo == MINIMO)
		heapify_minimo(monton, 0);
	else
		return;
}


void pop_Heap(Monton *monton) {
    if (monton->cantidad == 0) {
        printf("El heap está vacío. No hay nada que procesar.\n");
        return;
    }

    Nodo *aux = monton->nodos[0];
    printf("Procesando archivo: %s, Autor: %s, Paginas: %d\n", aux->documento.nombre, aux->documento.autor, aux->documento.paginas);
    liberar_cadenas(&aux->documento);

    monton->nodos[0] = monton->nodos[monton->cantidad - 1];
    monton->cantidad--;
    free(aux);

    // Si el heap está vacío, liberar la memoria y asignar NULL
    if (monton->cantidad == 0) {
        free(monton->nodos);
        monton->nodos = NULL;
        return;
    }

    // Reducir el tamaño del arreglo
    Nodo **temp = realloc(monton->nodos, sizeof(Nodo*) * monton->cantidad);
    if (!temp) {
        fprintf(stderr, "Error: No se pudo reasignar memoria para el heap.\n");
        exit(EXIT_FAILURE);
    }
    monton->nodos = temp;

    // Reorganizar el heap
    heapify(monton);
}

void invertir_heap(Monton *monton) {
    if (monton->tipo == MINIMO) {
        monton->tipo = MAXIMO; // Cambiar a heap máximo
        printf("Cambiando a heap máximo (prioridad: mayor cantidad de páginas primero).\n");
    } else {
        monton->tipo = MINIMO; // Cambiar a heap mínimo
        printf("Cambiando a heap mínimo (prioridad: menor cantidad de páginas primero).\n");
    }
    heapify(monton); // Reorganizar el heap según el nuevo tipo
}

void imprimir_heap(Monton *monton){
	int i;
	for(i = 0; i < monton->cantidad && i < 5; i++){
		printf("[%d] Nombre: %s, Autor: %s, Paginas: %d\n", i+1 , monton->nodos[i]->documento.nombre,monton->nodos[i]->documento.autor,monton->nodos[i]->documento.paginas);
	}
}


void imprimir_arbol(Nodo *nodo, int nivel){
	int i;
	if (nodo != NULL)
	{
		for (i = 0; i < nivel; i++)
			printf(" |      ");
		printf(" |____Nombre: %s, Autor: %s, Paginas: %d\n", nodo->documento.nombre,nodo->documento.autor,nodo->documento.paginas);
		imprimir_arbol(nodo->izq, nivel + 1);
		imprimir_arbol(nodo->dch, nivel + 1);
	}
}

void liberar_heap(Monton *monton){
	int i;
	for(i = 0; i < monton->cantidad; i++){
		liberar_nodo(monton->nodos[i]);
	}
	free(monton->nodos);
	monton->nodos = NULL;
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

