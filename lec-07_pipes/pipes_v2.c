#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int pipe_1[2];
    pipe(pipe_1);
    char s[64];

    if (fork()) {
        close(pipe_1[1]);
        close(0); // 0 : stdin
        dup(pipe_1[0]); // ps[0] = pipe_1[0] <- Redirigir la entrada standars 
        close(pipe_1[0]);
        // scanf("%s", s); // Ahora lee directamente del "stdin" ...
        read(0, s, 64);
        printf("[0] Se ha leído desde stdin la cadena: \"%s\" ...\n", s);
    } else {
        strcpy(s, "Hello world from SSOO");
        close(pipe_1[0]);
        close(1); // 1 : stdout
        dup(pipe_1[1]); // ps[1] = pipe_1[1] <- Redirigir la salida standars 
        close(pipe_1[1]);
        printf("%s", s); // Ahora escribe directamente al pipe ...
    }

    return 0;
}