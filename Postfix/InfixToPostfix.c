#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo{
    char dato;
    struct nodo *sig;
}Nodo;

typedef struct pila{
    Nodo *cima;
}Pila;

Nodo *crearNodo(char dato);
Nodo* pop(Pila* pila);
void push(Pila* pila, char dato);
int esOperando(char x);
int precedencia(char x);
char* postfix(char *infix);
int vacia(Pila *pila);
char peek(Pila* pila);
void liberarPila(Pila *pila);
void menu();
int infixValido(char * infix);

int main() {
    
    int opc = 0;
    
    do{
        menu();
        scanf(" %d", &opc);
        switch (opc)
        {
        case 1:{
            char infix[100];
            printf("\nIngrese expresion Infix: ");
            scanf(" %99s", infix);

            char *postfixExp = postfix(infix);
            if((postfixExp !=  NULL) && infixValido(infix)){
                printf("\n\nExpresion Infix: %s\n", infix);
                printf("Expresion Postfix: %s\n", postfixExp);
            }else{
                printf("Error. Expresion no valida.\n");
            }
            free(postfixExp); 
            break;
        }
        case 2:
            printf("\nFinalizando programa\n\n");
            break;
        
        default:
            printf("\nOpcion invalida\n\n");
            break;
        }
    }while(opc!=2);

    return 0;
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
                postfix[j++] = temp->dato;
                free(temp); 
            }
            free(pop(&pila));

        }
        else{

            while (!vacia(&pila) && precedencia(peek(&pila)) >= precedencia(infix[i])) {
                Nodo *temp = pop(&pila);
                postfix[j++] = temp->dato;
                free(temp); 
            }
            push(&pila, infix[i]);
                
        }
        i++;
    }
    
    while (!vacia(&pila)) {
        Nodo *temp = pop(&pila);
        postfix[j++] = temp->dato;
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

Nodo *crearNodo(char dato){
    Nodo *nuevo = (Nodo*)calloc(1, sizeof(Nodo));
    nuevo->dato = dato;
    nuevo->sig = NULL;
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
    return pila->cima->dato;
}

void liberarPila(Pila *pila){
    while(!vacia(pila)){
        free(pop(pila));
    }
    
}
void menu(){
    printf("\n\n=============================================================\n");
    printf("Elige una opcion\n");
    printf("\n [1]Infix a Postfix");
    printf("\n [2]Finalizar programa");
    printf("\n\n=============================================================\n");
    printf("Opcion-> ");
}