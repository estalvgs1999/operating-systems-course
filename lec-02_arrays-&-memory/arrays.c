#include <stdio.h>
#include <stdlib.h>

int main() {
    int array[] = { 1, 2, 3, 4, 5}; // Declarar un array de 5 elementos
    int first_elem = array[0]; // Obtener un elemento de un array
    array[0] = 10; // Cambiar el valor de un elemento del array

    /*
        STACK ↓ -> Almacena variables. Tiene un tamaño limitado
        [ int a = 1        ]
        [ int array[] = {} ]
        [ main()           ] <- Llamadas a funciones
        ...
        ...
        ...
        [ <Object_0x0>     ] <- Esta es la memoria que maneja el desarrollador
        [                  ] 
        [                  ]
        HEAP ↑ -> Almacena objetos, punteros, 
    */

    printf("guardando un bloque de memoria...\n");
    int length = 8;
    size_t size = sizeof(int) * length; // El tamaño del array se define indicando el tipo y la cantidad de espacios que tendrá el bloque.
    int *_array = malloc(size); // malloc almacena un bloque de memoria y retorna la dirección inicial.
    printf("bloque almacenado <_array> en: %p\n", _array);

    for(int i = 0; i < length; i++) {
        _array[i] = i + 1; // La sintaxis del index funciona también para los punteros
        printf("valor de _array[%i]: %i\n", i, _array[i]);
    }

    // memory leak: dejar un espacio en memoria ocupado, aún cuando ya no lo estamos utilizando.
    // ¿cómo solucionarlo? -> liberando la memoria.

    free(_array); // Se libera el espacio de memoria que se almacenó en _array.
    printf("memoria liberada ....\n");

    // ¿Cómo nos movemos en memoria cuando no conocemos el tamaño del array?
    // [SIGSEGV] -> segmentation fault -> Cuando se intenta acceder a una zona de memoria prohibida por el OS.
    // El OS detiene el proceso cuando ocurre un seg_fault... Esto ocurre solo en lenguajes compilados!
}