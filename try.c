#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

size_t S_MAX = SIZE_MAX / 2;

int main (){
    printf("size_t = %lu\n", sizeof(SIZE_MAX));
    printf("size_t = %lu\n", sizeof(size_t));
    // printf("uint = %lu\n", sizeof(unsigned int));
    printf("S    MAX = %lu\n", S_MAX * 2);
    printf("SIZE MAX = %lu\n", SIZE_MAX);
    printf("SMAX = %f\n", pow(2, 8));
    int x = 2;
    // for (int i = 0; i < 8*4; i++){
    for (int i = 0; i < 8*8; i++){
        x*=2;
    }
    // unsigned int x = -1;
    // printf("SMAX = %u\n", x);
    if(SIZE_MAX == S_MAX * 2 + 1){
        printf("LOL\n");
    }

    size_t* lol = malloc(sizeof(int));
    // lol = realloc(lol, (SIZE_MAX - 1));
    lol = realloc(lol, (SIZE_MAX) / 2);
    lol = realloc(lol, (S_MAX) * 2);
    lol = realloc(lol, (S_MAX * 2) * sizeof(unsigned int));
    lol = realloc(lol, S_MAX * sizeof(unsigned int) + 1);
}


