#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

int main() {
    struct Node *head = malloc(sizeof(struct Node));
    head -> value = 1;
    head -> next = malloc(sizeof(struct Node));
    head -> next -> value = 2; // Profundidad de Punteros

    printf("[head] addrs: %p\n", head);
    printf("[head] value: %i\n", head -> value);
    printf("[head->next] addrs: %p\n", head -> next);
    printf("[head->next] value: %i\n", head -> next -> value);
    printf("[head->next->next] addrs: %p\n", head -> next -> next);
    return 0;
}