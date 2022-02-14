#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100

int num_threads;
int *array;
int *t_result;

void *sum(void *arg) {
    int id = *(int*) arg;
    int nums_to_sum = SIZE / num_threads;
    int start = nums_to_sum * id;
    int end = start + nums_to_sum;

    if (id == num_threads - 1) {
        end = SIZE;
    }

    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += array[i];
    }
    
    t_result[id] = sum;
    printf("[thread %i] result: %i ...\n", id, sum);
    pthread_exit(0);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("El programa debe recibir el número de hilos ...\n");
        exit(-1);
    }

    num_threads = atoi(argv[1]);
    array = malloc(sizeof(int) * SIZE);
    t_result = malloc(sizeof(int) * num_threads);

    for (int i = 0; i < SIZE; i++) {
        array[i] = i + 1;
    }

    pthread_t threads[num_threads];
    int t_ids[num_threads];

    int total = 0;

    // Se crean los hilos y se ponen a correr
    for (int i = 0; i < num_threads; i++) {
        t_ids[i] = i;
        pthread_create(&threads[i], NULL, sum,(void*)&t_ids[i]);
    }

    // Se vuelven a unir los hilos al programa principal
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total += t_result[i];
    }
    
    
    printf("total: %i\n", total);

    free(array);
    free(t_result);
    return 0;
}
