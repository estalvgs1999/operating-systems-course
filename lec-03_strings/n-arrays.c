#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char c[2][8] = {"Hola", "Mensaje"}; // En C debemos saber de antemano el espacio que vamos a utilizar.
    printf("%s %s\n", c[0], c[1]);

    // Declarar una matriz en el Heap
    char **strings = malloc(sizeof(char*) * 2); // ** -> un puntero que apunta a punteros
    // Nota: como parámetro al malloc pasamos el tamaño de un puntero de char

    char *msg1 = malloc(sizeof(char) * 8);
    char *msg2 = malloc(sizeof(char) * 8);
    strcpy(msg1, "Hola");
    strcpy(msg2, "Mensaje");

    // Asignar los punteros al contenido de la matriz
    strings[0] = msg1;
    strings[1] = msg2;

    printf("%s %s\n", strings[0], strings[1]);

    /*
    
    strings -> [ 0x04c |     0x08c ] <- Es un puntero que apunta a un bloque de memoria
            ...
            -> [ 0x080 |     0x02c ] <- Bloque de memoria apartado con el malloc
            -> [ 0x084 |     0x030 ] <- Almacena punteros
            ...
            ...
            ...
    msg1    -> [ 0x02c |     0x000 ] <- Punteros char a los mensajes
    msg2    -> [ 0x030 |     0x008 ] 
            ...
            -> [ 0x000 | "Hello"   ] <- mensajes como chars[]
            -> [ 0x008 | "Mensaje" ]
    
    */

    return 0;
}
