#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>

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

void close_pipe(int _pipe[]) {
    close(_pipe[0]);
    close(_pipe[1]);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("[Error] Argumentos incompletos, falta un directorio ...\n");
        exit(-1);
    }

    struct stat data;
    DIR *dir;
    struct dirent *dp;
    char *file;

    int p1[2], p2[2];

    if (stat(argv[1], &data) != 0) {
        printf("[Error] Ha fallado la llamada a stat ...\n");
    }

    if (!S_ISDIR(data.st_mode)) {
        printf("[Error] No es un directorio ...\n");
        exit(-1);
    }

    dir = opendir(argv[1]);

    while ((dp = readdir(dir)) != NULL) {

        if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
            file = malloc(strlen(argv[1]) + strlen(dp->d_name) + 2); // path + / + fichero
            sprintf(file, "%s/%s", argv[1], dp->d_name);
            stat(file, &data);
            if (S_ISDIR(data.st_mode)) {
                if (fork()) {
                    wait(NULL);
                } else {
                    pipe(p2);
                    // wc
                    if (fork()) {
                        redirect_stdin(p2);
                        printf("Numero de ficheros en %s: ", file);
                        fflush(stdout);
                        execlp("wc", "wc", "-l", NULL);
                        printf("[Error] wc ...\n");
                        exit(-1);
                    } else {
                        pipe(p1);
                        // grep
                        if (fork()) {
                            redirect_stdin(p1);
                            redirect_stdout(p2);
                            execlp("grep", "grep", "^-", NULL);
                            printf("[Error] grep ...\n");
                            exit(-1);
                        } else {
                            // ls
                            close_pipe(p2);
                            redirect_stdout(p1);
                            execlp("ls", "ls", "-l", file, NULL);
                            printf("[Error] ls ...\n");
                            exit(-1);
                        }
                    }

                }
            }
            free(file);
        }
    }

    closedir(dir);

    return 0;
}
