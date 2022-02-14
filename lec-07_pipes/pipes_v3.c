#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// [ps -elf] -> | -> [cut -c5-12] -> | -> [sort -u]

void redirect_stdout(int _pipe[]) {
    // pipeout -> stdout
    close(_pipe[0]);
    close(1);
    dup(_pipe[1]);
    close(_pipe[1]);
}

void redirect_stdin(int _pipe[]) {
    // pipein -> stdin
    close(_pipe[1]);
    close(0);
    dup(_pipe[0]);
    close(_pipe[0]);
}

int main(int argc, char const *argv[]) {
    int pipe_1[2];
    pipe(pipe_1);

    if (fork()) {
        // cut
        redirect_stdin(pipe_1);
        execlp("cut", "cut", "-c5-12", NULL);
        printf("Error cut ...\n");
    } else {
        // ps
        redirect_stdout(pipe_1);
        execlp("ps", "ps", "-efl", NULL);
        printf("Error ps ...\n");
    }

    return 0;
}
