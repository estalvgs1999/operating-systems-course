#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct RGB {
    int r, g, b;
    int last;
};

void rgb_set(struct RGB *rgb, int r, int g, int b) {
    if (
        (r + g + b <= 255*3) && 
        (r >= 0 && g >= 0 && b >= 0)
    ) {
        rgb->r = r;
        rgb->g = g;
        rgb->b = b;
    }
}

void rgb_invert(struct RGB *rgb) {
    rgb_set(rgb, 255 - rgb->r, 255 - rgb->g, 255 - rgb->b);
}

char* rgb_str(struct RGB *rgb) {
    char *str = malloc(sizeof(char) * 64);
    // sprintf -> Permite dar formato al código y guarda el char* en un puntero
    sprintf(
        str,
        "RGB: (%i, %i, %i)\nHEX: 0x%02x%02x%02x\n",
        rgb->r, rgb->g, rgb->b,
        rgb->r, rgb->g, rgb->b
    );
    return str;
}

struct RGB* get_inverted_colors(char *file) {
    int limit = 4;
    struct RGB *inverted = malloc(sizeof(struct RGB) * limit);
    FILE *f = fopen(file, "r");
    int line_size = 16;
    char *line = malloc(sizeof(char) * line_size);
    int i = 0;

    while(fgets(line, line_size, f) > 0) {
        if (i >= limit - 1) {
            limit *= 2; // Una opción es duplicar el tamaño
            inverted = realloc(inverted, sizeof(struct RGB) * limit); // Realocamos la memoria, se cambia su tamaño dinámicamente
        }
        int values[3];
        char *split = strdup(line);
        for (int c = 0; c < 3; c++ ) {
            values[c] = atoi(strsep(&split, " "));
        }
        free(split); // liberar memoria dentro de los bucles es excelente práctica!!!
        rgb_set(&inverted[i], values[0], values[1], values[2]);
        inverted[i].last = 0;
        rgb_invert(&inverted[i++]); // i++ -> lee i, luego incrementa.
        // Nota: ++i -> primero incrementa, luego lee i.
    }
    inverted[i].last = 1; // Marcamos el último color
    free(line);
    fclose(f);
    return inverted;
}

// argc -> argument counter
// argv -> array/vector con argumentos. Se puede hacer de dos maneras:
//          (1) char **argv -> puntero de punteros
//          (2) char *argv[] -> puntero a un array
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Error. Uso: rgb <fichero-colores> ... \n");
        exit(-1);
    }

    /*
    Declaraciones de un struct:
    -------------
    stack: struct RGB rgb = {r, g, b};
    heap: struct RGB *rgb = malloc(sizeof(struct RGB)); 
    */
    struct RGB *inverted = get_inverted_colors(argv[1]);
    
    for (int i = 0; !inverted[i].last; i++) {
        char *s = rgb_str(&inverted[i]);
        printf("%s\n", s);
        free(s);
    }

    free(inverted);
    return 0;
}
