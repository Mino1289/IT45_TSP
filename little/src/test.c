#include <stdbool.h>
#include <stdio.h>

#define SIZE 4

int next_town[SIZE];

int main() {
    for (int i = 0; i < SIZE; i++) {
        next_town[i] = -1;
    }

    next_town[0] = 1;
    next_town[1] = 3;
    bool subtour = false;
    int izero = 0;
    int jzero = 2;
    next_town[jzero] = izero;
    int start = jzero;
    int tmp = next_town[start];
    int end = izero;
    int i = 0;

    while (tmp != start && tmp != -1 && i < SIZE) {
        i++;
        printf("%d -> %d\n", tmp, next_town[tmp]);
        tmp = next_town[tmp];
    }

    if (tmp == start) {
        subtour = true;
    }


    if (subtour) {
        printf("Sous-tour détecté, arrêt de l'exploration\n");
        next_town[izero] = -1;
        return 0;
    }
    return 0;
}