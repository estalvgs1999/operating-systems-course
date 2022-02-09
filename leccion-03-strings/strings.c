#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char c[] = {'H','e','l','l','o','\0'}; // Símbolo de escape -> \0
    printf("%s\n", c);

    char msg[] = "Hey"; // Un atajo es hacerlo en formato string, el compilador lo trabaja por nosotros...
    printf("%s\n", msg);

    // Declarando un puntero char
    char *_c = malloc(sizeof(char) * 6);
    strcpy(_c, "Hello"); // <- hace un 'for' para llenar el arreglo de chars. (string_copy) strcpy(char*, const char*)
    printf("_c: %s\n", _c);
}