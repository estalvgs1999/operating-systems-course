#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

// cmd: props <file>
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Hace falta un fichero ...\n");
        exit(-1);
    }

    struct stat data;
    char file_type[32];

    if(stat(argv[1], &data) != 0) { // Guarda los datos de un fichero en el struct data
        printf("Ha fallado la llamada a stat ...\n");
        exit(-1);
    }
    
    // Se hace un & con la bit mask S_IFMT para obtener el tipo del archivo...
    switch (data.st_mode & __S_IFMT) {
        case __S_IFREG:
            strcpy(file_type, "fichero regular");
            break;
        case __S_IFDIR:
            strcpy(file_type, "directorio");
            break;
        default:
            printf("Error, no es ni un directorio ni un fichero ...\n");
            exit(-1);
    }

    printf("\033[01;33mFICHERO:\033[0m        %s\n", argv[1]);
    printf("\033[01;33mTIPO:\033[0m           %s\n", file_type);
    printf("\033[01;33mPERMISOS:\033[0m       %o\n", data.st_mode & 0777); // 0num <- octal
    printf("\033[01;33mPROPIETARIO:\033[0m    %i\n", data.st_uid);
    printf("\033[01;33mENLACES:\033[0m        %lu\n", data.st_nlink);
    printf("\033[01;33mTAMAÑO:\033[0m         %lu\n", data.st_size);
    printf("\033[01;33mINODO:\033[0m          %lu\n", data.st_ino);
    printf("\033[01;33mULTIMO ACCESO:\033[0m  %s\n", ctime(&data.st_mtime));
    return 0;
}
