#include <stdio.h>

int main() {
    // Declaración de variables
    int a = 5; // a -> [0x000 | 5] : El valor se almacena en una dirección de memoria.
    int b = a; // b -> [0x004 | 5] : La variable almacena (copia) el valor almacenado en a. Lo mismo que: [int b = 5;]
    printf("Valor de a: %i\n", a);
    printf("Valor de b: %i\n", b);

    // Punteros
    int *ptr_a = &a;                         // ptr_a -> [0x008 | 0x000] : El puntero (*) almacena la dirección de memoria de 'a' (&a).
    printf("Valor de ptr_a: %p\n", ptr_a);   // %p -> tipo puntero.
    printf("Valor de *ptr_a: %i\n", *ptr_a); // *ptr -> retorna el valor almacenado en la dirección a la que apunta.

    /*
    +---------+-------------------+
    | operador| descripcion       |
    +---------+-------------------+
    | &a      | mem_addr          |
    | *a      | value in &a       |
    +---------+-------------------+
    */

    int *ptr_x = ptr_a; // Se le asigna el valor de ptr_a. Por lo tanto, ahora ambos punteros apunta a la dirección de "a".
    printf("Valor de ptr_x: %p\n", ptr_x);
    int ptrs_are_equal = (ptr_a == ptr_x) && (ptr_a == &a);
    printf("Los valores son iguales?: %i\n", ptrs_are_equal); // 1: true, 0: false.

    // a:       [ 0x0 |   5]
    // b:       [ 0x4 |   5]
    // ptr_a:   [ 0x8 | 0x0]
    // ptr_x:   [ 0xC | 0x0]

    // Se pueden realizar cambios
    *ptr_a = 12;
    printf("Valor de a: %i\n", a);
}
