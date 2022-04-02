#include <stdio.h>
#include <stdlib.h>

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

int main () {
    int k = 4;
    int *z = malloc(sizeof(int));
    loadhex(&z, k);
    for (int i = 0; i < k; i++){
        // putchar(n[i]);
        printf("%d,", z[i]);
    }
    return 0;
}