#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    int result = fork();

    if (result < 0) {
        printf("Llamada a fork ha fallado ...\n");
        exit(-1);
    }

    /*
    > Código Ejemplo:
        if (result != 0) {
            printf("[0] Esperando a que acabe el proceso ...\n");
            wait(NULL); // Espera a que el proceso hijo termine!!
            printf("[0] Ejecutando ps ...\n");
        } else {
            printf("[1] Ejecutando ls ...\n");
            printf("[1] Proceso terminado ...\n");
        }
    > Salida: 
        [0] Esperando a que acabe el proceso ...
        [1] Ejecutando ls ...
        [1] Proceso terminado ...
        [0] Ejecutando ps ...
    */

    // El wait garantiza el orden de ejecución, obliga a que un proceso espere 
    // que un proceso termine para ejecutar algo más
    if (result != 0) {
        wait(NULL);
        printf("> Salida ps:\n");
        execlp("ps", "ps", (char*)NULL); // execpl: Reemplaza el proceso por el ejecutable que se corre
    } else {
        printf("> Salida ls:\n");
        execlp("ls", "ls", (char*)NULL);
        // Solo si hay un error se devuelve el control del código después de la llamada
        printf("Error ejecutando la llamada ...\n");
    }

    printf("[0] Proceso terminado ...\n");
    return 0;
}
