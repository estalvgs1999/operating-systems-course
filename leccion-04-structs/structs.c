#include <stdio.h>
#include <stdlib.h>

// Los structs se manejan correctamente en el HEAP

// Esta manera de programar un struct obliga a usar <struct name var = { ... }>
struct Point {
    double x;
    double y;
};

// Esta otra manera nos permite obviar el struct y que sea un tipo de dato
typedef struct {
    int passengers;
    int license;
} Car;


int main() {
    struct Point my_point = { .x = 0.5, .y = 5.9 }; // Declaración e inicialización de un struct
    printf("{ x: %f , y: %f }\n", my_point.x, my_point.y); // Acceso a las propiedades del struct

    Car my_car = { 4, 12344 };
    printf("{ passengers: %i , license: %i }\n", my_car.passengers, my_car.passengers);
    
    // Inicializar un struct en el HEAP
    struct Point *pt = malloc(sizeof(struct Point));
    pt -> x = 0.4;
    pt -> y = 1.2;
    printf("{ x: %f , y: %f }\n", pt->x, pt->y);
    free(pt);

    // Esto nos ayuda a pasar los punteros como argumentos de las funciones

    return 0;
}