#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// ps -elf | cut -c5-12 | sort -u > out.txt

void redirect_stdout(int _pipe[]) {
    // pipeout -> stdout
    close(_pipe[0]);
    close(1);
    dup(_pipe[1]);
    close(_pipe[1]);
}

void redirect_stdout_to_file(char *file) {
    // file -> stdout
    close(1);
    open(file, O_WRONLY | O_CREAT | O_TRUNC, 0755);
}

void redirect_stdin(int _pipe[]) {
    // pipein -> stdin
    close(_pipe[1]);
    close(0);
    dup(_pipe[0]);
    close(_pipe[0]);
}

void close_pipe(int _pipe[]) {
    close(_pipe[0]);
    close(_pipe[1]);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Es necesario pasar un fichero ...");
        exit(-1);
    }

    int pipe_1[2], pipe_2[2];
    pipe(pipe_2);

    if (fork()) {
        // [pipe_2]-> sort
        redirect_stdin(pipe_2);
        redirect_stdout_to_file(argv[1]);
        execlp("sort", "sort", "-u", NULL);
        printf("Error sort ...\n");
    } else {
        pipe(pipe_1);
        if (fork()) {
            // [pipe_1]-> cut ->[pipe_2]
            redirect_stdin(pipe_1);
            redirect_stdout(pipe_2);
            execlp("cut", "cut", "-c5-12", NULL);
            printf("Error cut ...\n");
        } else {
            // ps -> [pipe_1]
            close_pipe(pipe_2);
            redirect_stdout(pipe_1);
            execlp("ps", "ps", "-efl", NULL);
            printf("Error ps ...\n");
        }
    }

    return 0;
}