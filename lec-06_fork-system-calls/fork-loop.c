#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int var = 1;
    for (int i = 0; i < 4; i++) {
        int result = fork();
        if (result != 0) {
            var++;
            break;
        } else {
            var += 2;
        }
    }
    printf("PID: %05i | PPID: %05i | var: %02i\n", getpid(), getppid(), var);
    return 0;
}
