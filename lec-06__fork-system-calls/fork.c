// Un proceso es un programa en ejecución ...
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int var = 5;

    // fork -> es la función que se utiliza para clonar el proceso actual
    // si el proceso es padre, retorna el PID del proceso hijo, si es hijo, retorna 0...
    int result = 1; //fork();
    if (result != 0) {
        printf("Este es el proceso padre. [result = %i]\n", result);
        var = 40;
    } else {
        printf("Este es el proceso hijo. [result = %i]\n", result);
    }

    // Explicación
    // ------------------
    // [1] En la primer llamada, se invoca a fork(), que retorna el PID del proceso hijo creado.
    //     Por lo tanto, entra a la primer condición del if.
    // [2] Como fork() clona el proceso, se ejecuta nuevamente el código (en el proceso hijo).
    //     De modo que, como es una proceso hijo, se retorna 0 y entra en el else.

    printf("Esto quién lo ejecuta?\n"); // se ejecuta siempre, no está condicionada

    // Los procesos son independientes en memoria, solo clona el estado que tenía el programa antes de clonarse...
    printf("var = %i\n", var);

    int x = 0;
    // ¿Qué sucede si creamos procesos en un bucle?
    for (int i = 0; i < 4; i++) {
        int pid = fork(); // El proceso continúa desde donde se hace el fork!
        if (pid != 0) {
            break; // Se debe terminar el proceso, para que no se encicle y haya infinidad de procesos
        }
        x++;
    }

    printf("PID: %05i, PPID: %05i, x: %i\n", getpid(), getppid(), x);

    /*

    ... Cuando el proceso se convierte en padre, se termina
    ---+-----o A: x = 0
       \----+-----o B: x =1
            \---+------o C: x = 2
                \---+-------o D: x = 3
                        \-----------------> E: x = 4 <--- Este es el resultado del último proceso dentro del bucle
                        
                        [!] Este no entra al for, porque no cumple la condición, así que no hace fork() sino
                            que únicamente termina el proceso.

    ----------------------------------------------------------------

    <pstree>
    code─┬─sh───cpuUsage.sh───sleep
        ├─zsh───pstree
    */

    return 0;
}
