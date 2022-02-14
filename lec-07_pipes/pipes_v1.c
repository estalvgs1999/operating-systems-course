/*
    cmd = ps -elf | cut -c5-12 | sort -u
    Hay tres procesos:
        (1) ps -elf
        (2) cut -c5-12
        (3) sort -u

    [1] -> | -> [2] -> | -> [3]
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    /*
    VECTOR DE UN PROCESO:
    --------------------
     [ 0 | stdin    ] < (teclado)
     [ 1 | stdout   ] > (pantalla)
     [ 2 | stderr   ] 2>
     [ 3 | file.txt ]    (descriptor de fichero)
     
    Los pipes cambian el stdin:
     [ 0 | pipe     ] < (salida proceso anterior)
     [ 1 | stdout   ] > (pantalla)
     [ 2 | stderr   ] 2>
     [ 3 | file.txt ]

    */

    int pipe_1[2];
    pipe(pipe_1);
    char s[64];

    if (fork()) {
        close(pipe_1[1]);
        read(pipe_1[0], s, 64);
        close(pipe_1[0]);
        printf("[0] Se ha leído desde el descriptor [%i] la cadena: \"%s\" ...\n", pipe_1[0], s);
    } else {
        strcpy(s, "Hello world from SSOO");
        close(pipe_1[0]);
        write(pipe_1[1], s, strlen(s));
        close(pipe_1[1]);
        printf("[1] Se ha escrito la cadena: \"%s\" en el descriptor [%i] ...\n", s, pipe_1[1]);
    }

    return 0;
}
