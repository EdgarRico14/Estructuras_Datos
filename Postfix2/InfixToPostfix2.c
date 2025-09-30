#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct nodo
{
    char caracter;
    double *dato;
    struct nodo *sig;
    struct nodo *izq,*dch;    
}Nodo;

typedef struct pila{
    Nodo *cima;
}Pila;


Nodo *crearNodo(char caracter);
void eliminarPostorden(Nodo** raiz);

Nodo* pop(Pila* pila);
void push(Pila* pila, char dato);
void pushNodo(Pila* pila, Nodo* nodo);
int vacia(Pila *pila);
char peek(Pila* pila);

int esOperando(char x);
int precedencia(char x);
char* postfix(char *infix);
int infixValido(char *infix);

void limpiarArreglos(double *valores, int *capturados);
void crearArbolPostfix(Nodo **raiz, char *postfix);
void evaluarExpresion(Nodo *raiz, int *capturadosMinus, int *capturadosMayus, double *valoresMayus, double* valoresMinus);
void capturarValorOperando(char caracter, int *capturados, double *valores, int indice, Nodo* nodo);
double evaluarArbol(Nodo *raiz);
void imprimirCaracteresOrden(Nodo *raiz);
void imprimir_arbol(Nodo* nodo, int nivel);
void imprimirFlotantesOrden(Nodo *raiz); 

void menu();

int main() {
    
    int opc = 0;
    Nodo *raiz = NULL;
    double valoresMayus[26];
    double valoresMinus[26];
    int capturadosMayus[26] = {0};
    int capturadosMinus[26] = {0};

    do{
        menu();
        scanf(" %d", &opc);
        switch (opc)
        {
        case 0:{ 
            limpiarArreglos(valoresMayus, capturadosMayus);
            limpiarArreglos(valoresMinus, capturadosMinus);
            eliminarPostorden(&raiz);
            char infix[100];
            printf("\nIngrese expresion Infix: ");
            scanf(" %99s", infix);
            if(infixValido(infix)){
                char *postfixExp = postfix(infix);
                printf("\n\nExpresion Infix: %s\n", infix);
                printf("Expresion Postfix: %s\n", postfixExp);
                crearArbolPostfix(&raiz, postfixExp);
                free(postfixExp);
                if(raiz){
                    printf("\nArbol creado\n");
                }
            }else{
                printf("Error. Expresion no valida.\n");
            }
            break;
        }
        case 1:
            if(raiz){
                imprimir_arbol(raiz, 0);
            }else{
                printf("\nArbol no disponible\n");
            }
            break;
        case 2:{
            if (raiz) {
                evaluarExpresion(raiz, capturadosMinus, capturadosMayus, valoresMayus, valoresMinus);
                double resultado = evaluarArbol(raiz);
                printf("\n===== La expresion evaluada es: =====\n\n");
                imprimirCaracteresOrden(raiz);
                printf("\n");
                imprimirFlotantesOrden(raiz);
                printf(" = %0.2lf\n", resultado);
                printf("\n======================================\n\n");
            } else {
                printf("\nArbol no disponible\n");
            }
            
            break;
        }
        case 3: 
            printf("\nFinalizando programa\n\n");
            break;

        default:
            printf("\nOpcion invalida\n\n");
            break;
        }
    }while(opc!=3);
    
    if(raiz){
        eliminarPostorden(&raiz);
        if(!raiz)
            printf("Memoria liberada correctamente\n");
        else
            printf("Memoria no se libero correctamente\n");
    
    }else{
        printf("Arbol no disponible\n");
    }

    return 0;
}

void capturarValorOperando(char caracter, int *capturados, double *valores, int indice, Nodo* raiz) {
    if (!capturados[indice]) {
        printf("\nIngresa valor de %c -> ", caracter);
        scanf(" %lf", &valores[indice]);
        capturados[indice] = 1;
    }
    raiz->dato = (double *)malloc(sizeof(double));  
    *raiz->dato = valores[indice];  
    
}

void evaluarExpresion(Nodo *raiz, int *capturadosMinus, int *capturadosMayus, double *valoresMayus, double *valoresMinus) {
    if (raiz == NULL) return;

    evaluarExpresion(raiz->izq, capturadosMinus, capturadosMayus, valoresMayus, valoresMinus);
    evaluarExpresion(raiz->dch, capturadosMinus, capturadosMayus, valoresMayus, valoresMinus);

    if (esOperando(raiz->caracter)) {
        if (raiz->caracter >= 'A' && raiz->caracter <= 'Z') {
            int indiceMayus = raiz->caracter - 'A';
            capturarValorOperando(raiz->caracter, capturadosMayus, valoresMayus, indiceMayus, raiz);
        } else if (raiz->caracter >= 'a' && raiz->caracter <= 'z') {
            int indiceMinus = raiz->caracter - 'a';
            capturarValorOperando(raiz->caracter, capturadosMinus, valoresMinus, indiceMinus, raiz);
        }
    }
}

double evaluarArbol(Nodo *raiz) {

    if (raiz == NULL) return 0;

    if (esOperando(raiz->caracter)) return *raiz->dato; 

    double izq = evaluarArbol(raiz->izq);
    double der = evaluarArbol(raiz->dch);

    switch (raiz->caracter) {
        case '^': return pow(izq,der);
        case '/': return izq / der;
        case '*': return izq * der;
        case '+': return izq + der;
        case '-': 
            if(raiz->izq==NULL) return -der;
            return izq - der;
        default: return 0;
    }

   
}
void imprimirFlotantesOrden(Nodo *raiz) {
    if (raiz == NULL) return;

    if (esOperando(raiz->caracter)) {
        printf(" %0.2lf ", *raiz->dato); 
    }
    else {
        printf("(");
        imprimirFlotantesOrden(raiz->izq);  
        printf(" %c ", raiz->caracter);  
        imprimirFlotantesOrden(raiz->dch);  
        printf(")");
    }
}

void imprimirCaracteresOrden(Nodo *raiz) {
    if (raiz == NULL) return;

    if (!esOperando(raiz->caracter)) printf("("); 
    imprimirCaracteresOrden(raiz->izq);
    
    printf(" %c ", raiz->caracter); 
   
    imprimirCaracteresOrden(raiz->dch);
    if (!esOperando(raiz->caracter)) printf(")"); 
}


void crearArbolPostfix(Nodo **raiz, char *postfix) {
    int i = 0;
    Pila pila = {NULL};

    while (postfix[i] != '\0') {
        if (esOperando(postfix[i])) {
            Nodo *nuevo = crearNodo(postfix[i]); 
            pushNodo(&pila, nuevo);
        } else { 
            Nodo *nuevo = crearNodo(postfix[i]);
            nuevo->dch = pop(&pila);  
            nuevo->izq = pop(&pila);  
            pushNodo(&pila, nuevo);   
        }
        i++;
    }
    *raiz = pop(&pila);
}

char* postfix(char *infix){
    int i = 0, j = 0;
    Pila pila = {NULL};
    int n = strlen(infix);
    char *postfix = (char *)malloc((n + 1) * sizeof(char));
    if (!postfix) return NULL;

    while(infix[i] !='\0'){
        
        if(esOperando(infix[i])){
            postfix[j++] = infix[i];
        }
        else if(infix[i]=='('){
            push(&pila, infix[i]);

        }else if(infix[i]==')'){
            while(!vacia(&pila) && peek(&pila)!='('){
                Nodo *temp = pop(&pila);
                postfix[j++] = temp->caracter;
                free(temp); 
            }
            free(pop(&pila));

        }
        else{
            while (!vacia(&pila) && precedencia(peek(&pila)) >= precedencia(infix[i])) {
                Nodo *temp = pop(&pila);
                postfix[j++] = temp->caracter;
                free(temp); 
            }
            push(&pila, infix[i]);
        }
        i++;
    }
    
    while (!vacia(&pila)) {
        Nodo *temp = pop(&pila);
        postfix[j++] = temp->caracter;
        free(temp);
    }
    
    postfix[j]='\0';
    return postfix;

}

int infixValido(char *infix){
    int i = 0, balance = 0;
    while(infix[i]!='\0'){
        if(!esOperando(infix[i]) && (infix[i]!='(' && infix[i]!=')')){
           if (i == 0 || infix[i+1] == '\0') {
                return 0; 
           }

           if (!(esOperando(infix[i-1]) || infix[i-1] == ')') || 
               !(esOperando(infix[i+1]) || infix[i+1] == '(')) {
                return 0;   
            }

        }else if(esOperando(infix[i])){
            if (infix[i+1] == '(' || (i > 0 && infix[i-1] == ')')) {
                return 0;  
            }                           

        }else if(infix[i]=='('){
            balance++;
            if(infix[i+1]==')'){
                return 0;
            }
            
        }else if(infix[i]==')'){
            balance--;
            if(balance<0){
                return 0;
            }
        }
        i++;
    }
    return balance == 0;
}

Nodo *crearNodo(char caracter) {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->caracter = caracter;
    nuevo->dato = NULL;
    nuevo->sig = nuevo->izq = nuevo->dch = NULL;
    return nuevo;
}

Nodo* pop(Pila* pila) {
    if (vacia(pila)) return NULL;
    Nodo *top = pila->cima;
    pila->cima = pila->cima->sig;
    return top;
}

void push(Pila* pila, char dato){
    Nodo* nodo = crearNodo(dato);
    nodo->sig = pila->cima; 
    pila->cima = nodo; 
}

void pushNodo(Pila* pila, Nodo* nodo){
    nodo->sig = pila->cima;
    pila->cima = nodo;
}

int esOperando(char x) {
    return !(x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '(' || x == ')');
}

int precedencia(char x){
    if(x =='+' || x == '-')
        return 1;
    else if (x=='*' || x== '/')
        return 2;
    else if(x=='^')
        return 3;
    return 0;
}
int vacia(Pila *pila){
    return (pila->cima == NULL);
}

char peek(Pila* pila){
    if (vacia(pila)) return '\0';
    return pila->cima->caracter;
}


void eliminarPostorden(Nodo** raiz) {
    if (*raiz == NULL) return;

    eliminarPostorden(&((*raiz)->izq));
    eliminarPostorden(&((*raiz)->dch));
    free((*raiz)->dato); 
    free(*raiz); 
    *raiz = NULL;  
}

void limpiarArreglos(double *valores, int *capturados){
    for(int i =0; i < 26; i++){
        valores[i] = 0.0;
        capturados[i] = 0;
    }
}

void menu(){
    printf("\n\n=============================================================\n");
    printf("Elige una opcion\n");
    printf("\n [0]CAPTURAR EXPRESION");
    printf("\n [1]IMPRIMIR ARBOL DE EXPRESION");
    printf("\n [2]EVALUAR EXPRESION");
    printf("\n [3]TERMINAR PROGRAMA");
    printf("\n\n=============================================================\n");
    printf("Opcion-> ");
}

void imprimir_arbol(Nodo* nodo, int nivel)
{
    int i;
    if (nodo != NULL)
        {
        printf(" %c", nodo->caracter);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1);
        }
    }
}