#include <stdio.h>
#include <stdlib.h>
// check realloc in load

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
        // putchar(n[i]);
        printf("%d,", n[i]);
    }
    // n[0] = getchar();
    // putchar(n[0]);
    return 0;
}