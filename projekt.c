#include <stdio.h>
#include <stdlib.h>

int load(int *n){
    int k = 0;
    int elem = getchar();
    if (elem == '\n') {
        *n = malloc(sizeof(int));
    }
    while (elem != '\n')
    {
        n[k] = elem;
        elem = getchar();
        k ++;
        *n = realloc(n, (k + 1)*sizeof(int));
    }
    return k;
    
}

int main (){
    int k = 0;
    int n[1];
    int x[1];
    int y[1];
    return 0;
}