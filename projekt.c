#include <stdio.h>
#include <stdlib.h>
// check realloc in load
// obsluga błędów w load za pomoć aujemnych wartości k

int load(int** n){
    int k = 0;
    int elem = getchar();
    int num = 0;
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


int loadhex(int** z){
    return 0;
}


int loadweird(int** z, int p, int k){
    int *a = malloc(sizeof(int));
    int l = load(a); //CZY L==5? i czy m ==0?
    long* s = malloc((a[3]) * sizeof(long));
    long* w = malloc((a[3]) * sizeof(long));
    s[0] = a[l - 1];
    for (int i = 1; i <l; i++){
        s[i] = (a[0] * s[i - 1] + a[1]) % a[2];
        w[i] = s[i] % p;
        long elem = w[i];
        while (elem < k) {
            *z[elem] = 1;
            elem += 4294967296;
        }
    }
    return 0;
}


int loadz(int** z, int p, int k){
    int elem1 = getchar();
    *z = realloc(*z, (k)*sizeof(int));
    for (int i = 0; i < k; i++) {*z[i] = 0;}
    if (elem1 == 'R'){
        loadweird(z, p, k);
    }
    else {
        int elem2 = getchar();
        if ((elem1 == '0') && (elem2 == 'x')){
            loadhex(z);
        }
        else {}
    }
}


int loadall(int** n, int** x, int** y, int** z, int* k) {
    int a = load(n);
    int b = load(x);
    int c = load(y);
    if ((a == b) && (b == c)) {
        *k = a;
        return 1;
    }
    else return 0; //WYJĄTEK!!!!!!!
    int p = 1;
    for (int i = 0; i < a; i++){p *= *n[i];}
    loadz(z, p, *k);
}


int main (){
    int k = 0;
    int *n = malloc(sizeof(int));
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    int *z = malloc(sizeof(int));
    loadall(&n, &x, &y, &z, &k);
    for (int i = 0; i < k; i++){
        // putchar(n[i]);
        printf("%d,", n[i]);
    }
    // n[0] = getchar();
    // putchar(n[0]);
    return 0;
}