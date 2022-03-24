#include <stdio.h>
#include <stdlib.h>


int load(int** n){
    int k = 0;
    int elem = getchar();
    unsigned int num = 0;
    int space = 0;
    while ((elem != '\n') && (elem != EOF))
    {
        // if ((elem != ' ') && (elem != '\t') && (elem != '\v') && (elem != '\f') && (elem != '\r')) {
        //     char let = (char)elem;
        //     *(*n + k) = atoi(&let);
        //     k ++;
        //     *n = realloc(*n, (k + 1)*sizeof(int));
        // }
        // elem = getchar();
        if ((elem != ' ') && (elem != '\t') && (elem != '\v') && (elem != '\f') && (elem != '\r')) {
            char let = (char)elem;
            num = atoi(&let) + (10 * num);
            space = 0;
        }
        else if (space == 0){
            space = 1;
            *(*n + k) = num;
            num = 0;
            k ++;
            *n = realloc(*n, (k)*sizeof(int)); //może wystarczy k
        }
        elem = getchar();
    }
    *(*n + k) = num;
    k++;
    return k;
}


int* loadweird(int** z, int p, int k){
    int *a = malloc(sizeof(int));
    int l = load(&a); //CZY L==5? i czy m ==0?
    int* s = malloc((a[3]) * sizeof(int));
    int* w = malloc((a[3]) * sizeof(int));
    s[0] = (a[0] * a[4] + a[1]) % a[2] + 1; //czy +1?
    for (int i = 1; i < a[3]; i++){
        s[i] = (a[0] * s[i - 1] + a[1]) % a[2] + 1; //czy + 1?
    }
    for (int i = 0; i <a[3]; i++){
        w[i] = s[i] % p;
        int elem = w[i];
        while (elem < k) {
            *z[elem - 1] = 1;
            elem += 4294967296;
        }
    }
    return s;
}


int main () {
    int* x = malloc(sizeof(int));
    // char y = (char) x;
    int k = 3;
    // int* a = loadweird(&x, 125, k);
    int *a = malloc(sizeof(int));
    printf("%ld,", (sizeof(a)/sizeof(int)));
    for (int i = 0; i < (sizeof(a)/sizeof(a[0])); i++){
        // putchar(n[i]);
        printf("%d,", a[i]);
    }
    // return x;
    // putchar(x);
    return 0;
}