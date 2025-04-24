#include <stdio.h>

int main() {
  int myAge = 43;
int* ptr = &myAge;  // ptr es un puntero a int
int** ptrPtr = &ptr;  // ptrPtr es un puntero a puntero a int


  // Output the value of myAge (43)
printf("%d\n", myAge);    // Imprime el valor de myAge (43)
printf("%d\n", *ptr);     // Imprime el valor apuntado por ptr (43)
printf("%d\n", **ptrPtr); // Imprime el valor apuntado por ptrPtr (43)

printf("%p\n", &myAge);   // Imprime la dirección de memoria de myAge
printf("%p\n", ptr);      // Imprime la dirección de memoria almacenada en ptr (misma que la de myAge)
printf("%p\n", *ptrPtr);  // Imprime la dirección de memoria almacenada en ptr (misma que la de myAge)

printf("%p\n", &ptr);     // Imprime la dirección de memoria de ptr
printf("%p\n", ptrPtr);   // Imprime la dirección de memoria almacenada en ptrPtr (misma que la de ptr)
printf("%p\n", &ptrPtr);  // Imprime la dirección de memoria de ptrPtr

  return 0;
}