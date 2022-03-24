#include <stdio.h>
#include <stdlib.h>


int main () {
    int* x = malloc(3 * sizeof(int));
    // char y = (char) x;
    x[0] = 5;
    printf("You entered: %d", x[0]);
    // return x;
    // putchar(x);
    return 0;
}