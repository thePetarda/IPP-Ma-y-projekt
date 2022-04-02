#include <stdio.h>
#include <stdlib.h>
// check realloc in load
// ogarnąć zmienne do użycia

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


int loadhex(int** z, int k){
    *z = realloc(*z, (k)*sizeof(int));
    int elem = getchar();
    int j = 0;//czy na końcu j == k - 1?
    while ((elem != '\n') && (elem != EOF)) {
        if ((elem < 58) && (elem > 47)){
            elem -= 48;
        }
        else if ((elem < 71) && (elem > 64)){
            elem -= 64;
            elem += 9;
        }
        else if ((elem < 103) && (elem > 96)){
            elem -= 96;
            elem += 9;
        }
        else{//ERROR 
        }
        printf("%d,", elem);
        for (int i = 0; i < 4; i++){
            *(*z + j + 3 - i) = elem % 2;
            elem /= 2;
        }
        j += 4;
        elem = getchar();
    }
    return 0;
}


int loadweird(int** z, int p, int k){
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
    return 0;
}


int loadz(int** z, int p, int k){
    int elem1 = getchar();
    *z = realloc(*z, (k)*sizeof(int));
    for (int i = 0; i < k; i++) {*(*z + i) = 0;}
    if (elem1 == 'R'){
        loadweird(z, p, k);
    }
    else {
        int elem2 = getchar();
        if ((elem1 == '0') && (elem2 == 'x')){
            loadhex(z, k);
        }
        else {}
    }
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