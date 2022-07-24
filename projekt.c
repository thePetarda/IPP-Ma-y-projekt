#include <stdio.h>
#include <stdlib.h>
// ogarnąć zmienne do użycia
//sprawdzić czy początek i koniec to nie ściany

int load(unsigned int** n, unsigned int* k){
    //dodane start
    //rozkminić lepsze wczytywanie
    int elem = getchar();
    unsigned int num = 0;
    int space = 1;
    int start = 1;
    while ((elem != '\n') && (elem != EOF))
    {
        if ((elem != ' ') && (elem != '\t') && (elem != '\v') && (elem != '\f') && (elem != '\r')) {
            num = (10 * num);
            int dig = elem - 48;
            if ((dig < 0) || (dig > 9)) {return 1;}
            num += dig;
            space = 0;
            start = 0;
        }
        else if (space == 0){
            space = 1;
            if (start != 1){ 
                *(*n + (*k)) = num;
                num = 0;
                (*k) ++;
                if ((*k) > sizeof(size_t) / sizeof(unsigned int)) {return 2;}
                *n = realloc(*n, (*k)*sizeof(unsigned int)); //może wystarczy k
                if (*n == NULL) {return 2;}
            }
        }
        elem = getchar();
    }
    if (num != 0){ 
        *(*n + (*k)) = num;
        (*k)++;
    }
    return 0;
}


int loadhex(unsigned int** z, unsigned int k){
    int elem = getchar();
    unsigned int j = 0;//czy na końcu j == k - 1?
    while ((elem != '\n') && (elem != EOF)) {
        if (j >= k) {return 1;}
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
        else {return 1;}
        for (int i = 3; i >= 0; i--){
            *(*z + j + 3 - i) = elem % 2;
            elem /= 2;
        }
        j += 4;
        elem = getchar();
    }
    return 0;
}


int loadweird(unsigned int** z, unsigned int p, unsigned int k){
    unsigned int *a = malloc(sizeof(unsigned int));
    // if (a == NULL) {return 1;}
    int l = 0;
    int t = load(&a, &l);
    if (t != 0) {return 1;}
    if ((l != 5) || (t != 0)) {return 1;}
    if (a[2] == 0) {return 1;} // m != 0
    if (a[3] > sizeof(size_t) / sizeof(unsigned int)) {return 1;}
    unsigned int* s = malloc((a[3]) * sizeof(unsigned int));
    // if (s == NULL) {return 1;}
    unsigned int* w = malloc((a[3]) * sizeof(unsigned int));
    // if (w == NULL) {return 1;}
    s[0] = (a[0] * a[4] + a[1]) % a[2] + 1;
    for (unsigned int i = 1; i <= a[3]; i++){
        // s[i] = (a[0] * s[i - 1] + a[1]) % a[2] + 1;
        s[i] = (a[0] * s[i - 1] + a[1]) % a[2];
    }
    for (unsigned int i = 0; i < a[3]; i++){
        w[i] = s[i] % p;
        unsigned int elem = w[i];
        // while (elem < k) {
        //     *(*z + (elem - 1)) = 1;
        //     elem += 4294967296;
        // }
        *(*z + (elem - 1)) = 1;
    }
    free(a);
    free(s);
    free(w);
    return 0;
}


int loadz(unsigned int** n, unsigned int** z, unsigned int k, unsigned int* wz){
    unsigned int m = 0;
    unsigned int p = 1;
    for (unsigned int i = 0; i < k; i++){
        unsigned int x = (*(*n + i)) - 1;
        p *= (*(*n + i));
        for (unsigned int j = 0; j < i; j++) {
            x *= (*(*n + j));
        }
        m += x;
    }
    // m++; //nie jestem pewna
    if (m == 0) {m = 4;}
    if ((m % 4) != 0) {m += 4 - (m % 4);}
    // printf(" m = %d ", m); 

    
    int t = 0;
    //jaki ma być rozmiar z?
    if (m >= sizeof(size_t) / sizeof(unsigned int)) {return 2;}
    *wz = m;
    *z = realloc(*z, m*sizeof(unsigned int));
    if (*z == NULL) {return 2;}
    for (unsigned int i = 0; i < m; i++) {*(*z + i) = 0;}
    int elem1 = getchar();
    // putchar(elem1);
    if (elem1 == 'R'){
        // printf("LOL");
        t = loadweird(z, p, m);
    }
    else {
        int elem2 = getchar();
        if ((elem1 == '0') && (elem2 == 'x')){
            t = loadhex(z, m);
        }
        else {return 1;}
    }
    return t;
}

int checkfull(unsigned int** z, unsigned int** n, unsigned int** q, unsigned int wz, unsigned int k){
    int a = 0;
    int p = 1;
    for (int i = 0; i < k; i++){
        int el = *(*q + i);
        if (el > *(*n + i)){return 2;}
        a += (el - 1)*p;
        p *= *(*n + i);
    }
    // if (a > k) {return 2;}
    if (a > wz) {return 2;}
    return *(*z + a);
}


int loadall(unsigned int** n, unsigned int** x, unsigned int** y, unsigned int** z, unsigned int* k) {
    int t;
    t = load(n, k);
    if (t == 2) {return 6;}
    if ((t != 0) || ((*k) == 0)) {return 1;}
    unsigned int a = *k;
    *k = 0;
    t = load(x, k);
    if (t == 2) {return 6;}
    if ((a != *k) || (t != 0)) {return 2;}
    *k = 0;
    t = load(y, k);
    if (t == 2) {return 6;}
    if ((a != *k) || (t != 0)) {return 3;}
    // unsigned int m = 0;
    // unsigned int p = 1;
    // for (unsigned int i = 0; i < (*k); i++){
    //     unsigned int x = (*(*n + i)) - 1;
    //     p *= (*(*n + i));
    //     for (unsigned int j = 0; j < i; j++) {
    //         x *= (*(*n + j));
    //     }
    //     m += x;
    // }
    // if ((m % 4) != 0) {m += 4 - (m % 4);}
    unsigned int wz = 0;
    t = loadz(n, z, *k, &wz);
    if (t == 2) {return 6;}
    if (t != 0) {return 4;}
    if (checkfull(z, n, x, wz, *k) != 0) {return 2;}
    if (checkfull(z, n, y, wz, *k) != 0) {return 3;}
    if (getchar() != EOF) {return 5;}
    return 0;
}


void end(unsigned int** n, unsigned int** x, unsigned int** y, unsigned int** z){
    free(*n);
    free(*x);
    free(*y);
    free(*z);
}


int main (){
    unsigned int k = 0;
    unsigned int *n = malloc(sizeof(unsigned int));
    unsigned int *x = malloc(sizeof(unsigned int));
    unsigned int *y = malloc(sizeof(unsigned int));
    unsigned int *z = malloc(sizeof(unsigned int));
    int t = loadall(&n, &x, &y, &z, &k);
    if (t != 0) {
        printf("ERROR %d\n", (t % 6));
        end(&n, &x, &y, &z);
        return 1;
    }
    end(&n, &x, &y, &z);
    printf("OK");
    return 0;
}


// printf("%d,\n", k);
    // for (unsigned int i = 0; i < k; i++){
    //     // putchar(n[i]);
    //     printf("%d,", n[i]);
    // }
    // printf("\n");
    // for (unsigned int i = 0; i < k; i++){
    //     // putchar(n[i]);
    //     printf("%d,", x[i]);
    // }
    // printf("\n");
    // for (unsigned int i = 0; i < k; i++){
    //     // putchar(n[i]);
    //     printf("%d,", y[i]);
    // }
    // printf("\n");
    // unsigned int m = 0;
    // for (unsigned int i = 0; i < k; i++){
    //     unsigned int x = n[i] - 1;
    //     for (int j = 0; j < i; j++) {
    //         x *= n[j];
    //     }
    //     m += x;
    // }
    
    // if ((m % 4) != 0) {m += 4 - (m % 4);}
    // printf("%d,\n", m);
    // for (unsigned int i = 0; i < m; i++){
    //     printf("%d,", z[i]);
    // }
    // printf("\n");