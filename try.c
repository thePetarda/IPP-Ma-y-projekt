#include <stdio.h>
#include <stdlib.h>

int load(int** n, int* k){
    int elem = getchar();
    int num = 0;
    int space = 1;
    while ((elem != '\n') && (elem != EOF))
    {
        if ((elem != ' ') && (elem != '\t') && (elem != '\v') && (elem != '\f') && (elem != '\r')) {
            num = (10 * num);
            int dig = elem - 48;
            if ((dig < 0) || (dig > 9)) {return 1;}
            num += dig;
            space = 0;
        }
        else if (space == 0){
            space = 1;
            if (num != 0){ 
                *(*n + (*k)) = num;
                num = 0;
                (*k) ++;
                *n = realloc(*n, (*k)*sizeof(int)); //może wystarczy k
            }
            if (*n == NULL) {return 2;}
        }
        elem = getchar();
    }
    if (num != 0){ 
        *(*n + (*k)) = num;
        (*k)++;
    }
    return 0;
}

int loadall(int** n, int** x, int** y, int** z, int* k) {
    int t;
    t = load(n, k);
    if (t != 0) {return 1;}
    int a = *k;
    *k = 0;
    t = load(x, k);
    if ((a != *k) || (t != 0)) {return 2;}
    *k = 0;
    t = load(y, k);
    if ((a != *k) || (t != 0)) {return 3;}
    // int p = 1;
    // for (int i = 0; i < a; i++){p *= *n[i];}
    // loadz(z, p, *k);
    return 0;
}

int main () {
    int k = 0;
    int *n = malloc(sizeof(int));
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    int *z = malloc(sizeof(int));
    int a = loadall(&n, &x, &y, &z, &k);
    printf("%d,", a);
    printf("%d,\n", k);
    for (int i = 0; i < k; i++){
        // putchar(n[i]);
        printf("%d,", n[i]);
    }

    return 0;
}