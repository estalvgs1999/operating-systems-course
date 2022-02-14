#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
#include <errno.h>

int num_threads = 1, num_files;
char *path, *name, *ext;

void *create_files(void *id_ptr) {
    int id = *(int*)id_ptr;
    int files_to_create = num_files / num_threads;
    int start_file = files_to_create * id;
    int end_file = start_file + files_to_create;

    if (id == num_threads - 1) {
        end_file = num_files;
    }

    char file[256];

    for (int i = start_file; i < end_file; i++) {
        sprintf(file, "%s/%s%03i.%s", path, name, i+1, ext);
        FILE *f = fopen(file, "w");
        printf("\033[01;33m[thread %02i]\033[0m creating file: \033[01;32m%s\033[0m\n", id, file);
    }

    pthread_exit(0);
}

void start_threads() {
    pthread_t threads[num_threads];
    int t_ids[num_threads];

    for (int i = 0; i < num_threads; i++) {
        t_ids[i] = i;
        pthread_create(&threads[i], NULL, create_files, (void*)&t_ids[i]);
    }
    
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    exit(0);
}

void eval_args(int argc, char **argv) {
    if (argc < 5) {
        printf("Uso:\n %s <path> <name> <ext> <number of files> ...\n", argv[0]);
        exit(-1);
    }

    DIR *dir = opendir(argv[1]);
    if (errno == ENOENT) {
        printf("Directorio %s no existe ...\n", argv[1]);
        exit(-1);
    }
    closedir(dir);

    path = argv[1];
    name = argv[2];
    ext = argv[3];
    num_files = atoi(argv[4]);

    if (argc == 6) {
        num_threads = atoi(argv[5]);
    }

    if (num_threads > num_files) {
        printf("La cantidad de hilos debe ser mayor o igual al número de archivos ...\n");
        exit(-1);
    }

    printf("%s\n", path);
}

int main(int argc, char **argv) {
    eval_args(argc, argv);
    start_threads();
    return 0;
}

// time(1000, 4): ./files Test test py 1000 42  0,00s user 0,05s system 35% cpu 0,146 total
// En C es más veloz por dos razones: (a) Los hilos, (b) El código es nativo.