#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// POSIX THREADS : estándar para sistemas UNIX
// gcc threads.c -o thread -l pthread

void *sum(void *arg) {
    int valor_pasado_a_entero = *(int*)arg; // obtener un argumento en el hilo
    printf("El valor recibido es %i ...\n", valor_pasado_a_entero);
    pthread_exit(0);
}

int main(int argc, char **argv) {
    pthread_t thread_1, thread_2;
    int valor_t1 = 1, valor_t2 = 2;
    pthread_create(&thread_1, NULL, sum, &valor_t1); // pasar argumentos del hilo
    pthread_create(&thread_2, NULL, sum, &valor_t2); // El orden de ejecución de los hilos no está garantizado
    // El orden lo define el algoritmo de calendarización de procesos del SO
    printf("Hilo principal ...\n");
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    return 0;
}
