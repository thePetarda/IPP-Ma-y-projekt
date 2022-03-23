#include <stdio.h>
#include <stdlib.h>

int load(int** n){
    int k = 0;
    int elem = getchar();
    while ((elem != '\n') && (elem != EOF))
    {
        if ((elem != ' ') && (elem != '\t') && (elem != '\v') && (elem != '\f') && (elem != '\r')) {
            *(*n + k) = elem;
            k ++;
            *n = realloc(*n, (k + 1)*sizeof(int));
        }
        elem = getchar();
    }
    return k;
}

int loadall(int** n, int** x, int** y) {
    int a = load(n);
    int b = load(x);
    int c = load(y);
    if ((a == b) && (b == c)) return a;
    else return 0; //WYJĄTEK!!!!!!!
}


int main (){
    int k = 0;
    int *n = malloc(sizeof(int));
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    k = loadall(&n, &x, &y);
    for (int i = 0; i < k; i++){
        putchar(n[i]);
    }
    // n[0] = getchar();
    // putchar(n[0]);
    return 0;
}