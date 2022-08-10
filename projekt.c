#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "QueueArray.c"

// unsigned int S_MAX = sizeof(size_t) / sizeof(unsigned int);
// size_t S_MAX = (SIZE_MAX - 2) / 2 / sizeof(unsigned int);

int load(unsigned int** dim, unsigned int* size){
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
                *(*dim + (*size)) = num;
                num = 0;
                (*size) ++;
                // if ((*size) >= S_MAX) {return 2;}
                // if ((*size)*sizeof(unsigned int) > (SIZE_MAX / 2 - 1)) {return 2;}
                if ((*size) > 6) {return 2;} 
                // if ((*size)*sizeof(unsigned int) >  (27 + 1)) {return 2;} 
                // if ((*size)*sizeof(unsigned int) >  (23)) {return 2;} 
                *dim = realloc(*dim, (*size)*sizeof(unsigned int));
                if (*dim == NULL) {return 2;}
            }
        }
        elem = getchar();
    }
    if (num != 0){ 
        *(*dim + (*size)) = num;
        (*size)++;
    }
    return 0;
}


// int loadhex(unsigned int** walls, unsigned int size){
//     int elem = getchar();
//     unsigned int j = 0;
//     while ((elem != '\n') && (elem != EOF)) {
//         if (j >= size) {return 1;}
//         if ((elem < 58) && (elem > 47)){
//             elem -= 48;
//         }
//         else if ((elem < 71) && (elem > 64)){
//             elem -= 64;
//             elem += 9;
//         }
//         else if ((elem < 103) && (elem > 96)){
//             elem -= 96;
//             elem += 9;
//         }
//         else {return 1;}
//         for (int i = 0; i < 4; i++){
//             *(*walls + j + 3 - i) = elem % 2;
//             elem /= 2;
//         }
//         j += 4;
//         elem = getchar();
//     }
//     return 0;
// }


// int loadweird(unsigned int** walls, unsigned int p){
//     unsigned int *a = malloc(sizeof(unsigned int));
//     if (a == NULL) {return 1;}
//     int l = 0;
//     int t = load(&a, &l);
//     if (t != 0) {return 1;}
//     if ((l != 5) || (t != 0)) {return 1;}
//     if (a[2] == 0) {return 1;} // m != 0
//     if (a[3] > S_MAX) {return 1;}
//     unsigned int* s = malloc((a[3]) * sizeof(unsigned int));
//     if (s == NULL) {return 1;}
//     unsigned int* w = malloc((a[3]) * sizeof(unsigned int));
//     if (w == NULL) {return 1;}
//     s[0] = (a[0] * a[4] + a[1]) % a[2] + 1;
//     for (unsigned int i = 1; i <= a[3]; i++){
//         s[i] = (a[0] * s[i - 1] + a[1]) % a[2];
//     }
//     for (unsigned int i = 0; i < a[3]; i++){
//         w[i] = s[i] % p;
//         unsigned int elem = w[i];
//         *(*walls + (elem - 1)) = 1;
//     }
//     free(a);
//     free(s);
//     free(w);
//     return 0;
// }


// int loadz(unsigned int** dim, unsigned int** walls, unsigned int size, unsigned int* bits){
//     int answer = 0;
//     unsigned int msize = 0;
//     unsigned int p = 1;
//     for (unsigned int i = 0; i < size; i++){
//         unsigned int x = (*(*dim + i)) - 1;
//         p *= (*(*dim + i));
//         for (unsigned int j = 0; j < i; j++) {
//             x *= (*(*dim + j));
//         }
//         // na tym poległ example5
//         msize += x;
//     }
//     if (msize == 0) {msize = 4;}
//     if ((msize % 4) != 0) {msize += 4 - (msize % 4);}
//     //nie wiem czemu nie przechodzi
//     if (msize > S_MAX) {return 2;}
//     *bits = msize;
//     *walls = realloc(*walls, msize*sizeof(unsigned int));
//     if (*walls == NULL) {return 2;}
//     for (unsigned int i = 0; i < msize; i++) {*(*walls + i) = 0;}
//     int elem1 = getchar();
//     if (elem1 == 'R'){
//         answer = loadweird(walls, p);
//     }
//     else {
//         int elem2 = getchar();
//         if ((elem1 == '0') && (elem2 == 'x')){
//             answer = loadhex(walls, msize);
//         }
//         else {return 1;}
//     }
//     return answer;
// }

// int checkfull(unsigned int** walls, unsigned int** dim, unsigned int** coordinates, unsigned int bits, unsigned int size){
//     int bit = 0;
//     int p = 1;
//     for (int i = 0; i < size; i++){
//         int el = *(*coordinates + i);
//         if (el > *(*dim + i)){return 2;}
//         bit += (el - 1)*p;
//         p *= *(*dim + i);
//     }
//     if (bit > bits) {return 2;}
//     return *(*walls + bits - bit - 1);
// }


int loadall(unsigned int** dim, unsigned int** start, unsigned int** stop, unsigned int** walls, unsigned int* size, unsigned int* bits) {
    int answer;
    answer = load(dim, size);
    if (answer == 2) {return 6;}
    if ((answer != 0) || ((*size) == 0)) {return 1;}
    // unsigned int asize = *size;
    // *size = 0;
    // answer = load(start, size);
    // if (answer == 2) {return 6;}
    // if ((asize != *size) || (answer != 0)) {return 2;}
    // *size = 0;
    // answer = load(stop, size);
    // if (answer == 2) {return 6;}
    // if ((asize != *size) || (answer != 0)) {return 3;}
    // answer = loadz(dim, walls, *size, bits);
    // if (answer == 2) {return 6;}
    // if (answer != 0) {return 4;}
    // if (checkfull(walls, dim, start, *bits, *size) != 0) {return 2;}
    // if (checkfull(walls, dim, stop, *bits, *size) != 0) {return 3;}
    // if (getchar() != EOF) {return 5;}
    // return 0;
}

// void visit(unsigned int** walls, unsigned int** dim, unsigned int** coordinates, unsigned int bits, unsigned int size){
//     int bit = 0;
//     int p = 1;
//     for (int i = 0; i < size; i++){
//         int el = *(*coordinates + i);
//         bit += (el - 1)*p;
//         p *= *(*dim + i);
//     }
//     *(*walls + bits - bit - 1) = 1;
// }

// int checkstop(unsigned int* coordinates, unsigned int* stop, unsigned int size){
//     for (int i = 0; i < size; i++){
//         if (*(coordinates + i) != *(stop + i)) {return 0;}
//     }
//     return 1;
// }

// unsigned int* copycoordinates(unsigned int* coordinates, unsigned int size){
//     unsigned int* ans = (unsigned int*) malloc(size * sizeof(unsigned int));
//     for (int i = 0; i < size; i++){
//         *(ans + i) = *(coordinates + i);
//     }
//     return ans;
// }

// int findway(unsigned int** dim, unsigned int** start, unsigned int** stop, unsigned int** walls, unsigned int size, unsigned int bits){
//     QueueArray* queue = malloc(sizeof(QueueArray));
//     (*queue).value = start;
//     (*queue).distance = 0;
//     (*queue).next = NULL;
//     // while(!checkstop(*((*queue).value), *stop, size)){
//     //     visit(walls, dim, (*queue).value, bits, size);
//     //     for (int i = 0; i < size; i++){
//     //         unsigned int* up = copycoordinates(*((*queue).value), size);
//     //         unsigned int* down = copycoordinates(*((*queue).value), size);
//     //         (*(up + i))++;
//     //         (*(down + i))--;
//     //         if (checkfull(walls, dim, &up, bits, size) == 0){
//     //             // printf("UP");
//     //             putLast(queue, &up, (*queue).distance + 1);
//     //         }
//     //         if (checkfull(walls, dim, &down, bits, size) == 0){
//     //             // printf("DOWN");
//     //             putLast(queue, &down, (*queue).distance + 1);
//     //         }
//     //     }
//     //     queue = deleteFirst(queue);
//     //     if (amount(queue) == 0){
//     //         deleteAll(queue);
//     //         printf("LOL");
//     //         return -1;
//     //     }
//     // }
//     unsigned int ans = (*queue).distance;
//     deleteAll(queue);
//     return ans;
// }


void end(unsigned int** dim, unsigned int** start, unsigned int** stop, unsigned int** walls){
    free(*dim);
    free(*start);
    free(*stop);
    free(*walls);
}


int main (){
    unsigned int size = 0;
    unsigned int bits = 0;
    unsigned int *dim = malloc(sizeof(unsigned int));
    unsigned int *start = malloc(sizeof(unsigned int));
    unsigned int *stop = malloc(sizeof(unsigned int));
    unsigned int *walls = malloc(sizeof(unsigned int));
    int t = loadall(&dim, &start, &stop, &walls, &size, &bits);
    if (t != 0) {
        printf("ERROR %d\n", (t % 6));
        end(&dim, &start, &stop, &walls);
        return 1;
    }
    // int distance = findway(&dim, &start, &stop, &walls, size, bits);
    // if (distance < 0) {printf("NO WAY\n");}
    // else {printf("%d\n", distance);}
    end(&dim, &start, &stop, &walls);

    // for (int i = 0; i < bits; i++){
    //     printf("%d ", *(walls + i));
    // }
    // printf("\n");

    // for (int i = -1; i < 5; i++){
    //     unsigned int* coor = copycoordinates(start, size);
    //     (*(coor)) += i;
    //     printf("%d ", *(coor));
    //     if (checkfull(&walls, &dim, &coor, bits, size) != 0){
    //         printf("WALL ");
    //     }
    // }
    return 0;
}
