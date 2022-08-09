#include <stdio.h>
#include <stdlib.h>
#include "QueueArray.c"

unsigned int S_MAX = sizeof(size_t) / sizeof(unsigned int);

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
                if ((*size) > S_MAX) {return 2;}
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


int loadhex(unsigned int** walls, unsigned int size){
    int elem = getchar();
    unsigned int j = 0;
    while ((elem != '\n') && (elem != EOF)) {
        if (j >= size) {return 1;}
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
            *(*walls + j + 3 - i) = elem % 2;
            elem /= 2;
        }
        j += 4;
        elem = getchar();
    }
    return 0;
}


int loadweird(unsigned int** walls, unsigned int p){
    unsigned int *a = malloc(sizeof(unsigned int));
    if (a == NULL) {return 1;}
    int l = 0;
    int t = load(&a, &l);
    if (t != 0) {return 1;}
    if ((l != 5) || (t != 0)) {return 1;}
    if (a[2] == 0) {return 1;} // m != 0
    if (a[3] > S_MAX) {return 1;}
    unsigned int* s = malloc((a[3]) * sizeof(unsigned int));
    if (s == NULL) {return 1;}
    unsigned int* w = malloc((a[3]) * sizeof(unsigned int));
    if (w == NULL) {return 1;}
    s[0] = (a[0] * a[4] + a[1]) % a[2] + 1;
    for (unsigned int i = 1; i <= a[3]; i++){
        s[i] = (a[0] * s[i - 1] + a[1]) % a[2];
    }
    for (unsigned int i = 0; i < a[3]; i++){
        w[i] = s[i] % p;
        unsigned int elem = w[i];
        *(*walls + (elem - 1)) = 1;
    }
    free(a);
    free(s);
    free(w);
    return 0;
}


int loadz(unsigned int** dim, unsigned int** walls, unsigned int size, unsigned int* bits){
    int answer = 0;
    unsigned int m = 0;
    unsigned int p = 1;
    for (unsigned int i = 0; i < size; i++){
        unsigned int x = (*(*dim + i)) - 1;
        p *= (*(*dim + i));
        for (unsigned int j = 0; j < i; j++) {
            x *= (*(*dim + j));
        }
        m += x;
    }
    if (m == 0) {m = 4;}
    if ((m % 4) != 0) {m += 4 - (m % 4);}
    //nie wiem czemu nie przechodzi
    // if (m > S_MAX) {printf("m = %d ", m); return 2;}
    *bits = m;
    *walls = realloc(*walls, m*sizeof(unsigned int));
    if (*walls == NULL) {return 2;}
    for (unsigned int i = 0; i < m; i++) {*(*walls + i) = 0;}
    int elem1 = getchar();
    if (elem1 == 'R'){
        answer = loadweird(walls, p);
    }
    else {
        int elem2 = getchar();
        if ((elem1 == '0') && (elem2 == 'x')){
            answer = loadhex(walls, m);
        }
        else {return 1;}
    }
    return answer;
}

int checkfull(unsigned int** walls, unsigned int** dim, unsigned int** coordinates, unsigned int bits, unsigned int size){
    int bit = 0;
    int p = 1;
    for (int i = 0; i < size; i++){
        int el = *(*coordinates + i);
        if (el > *(*dim + i)){return 2;}
        bit += (el - 1)*p;
        p *= *(*dim + i);
    }
    if (bit > bits) {return 2;}
    return *(*walls + bit);
}


int loadall(unsigned int** dim, unsigned int** start, unsigned int** stop, unsigned int** walls, unsigned int* size, unsigned int* bits) {
    int answer;
    answer = load(dim, size);
    if (answer == 2) {return 6;}
    if ((answer != 0) || ((*size) == 0)) {return 1;}
    unsigned int asize = *size;
    *size = 0;
    answer = load(start, size);
    if (answer == 2) {return 6;}
    if ((asize != *size) || (answer != 0)) {return 2;}
    *size = 0;
    answer = load(stop, size);
    if (answer == 2) {return 6;}
    if ((asize != *size) || (answer != 0)) {return 3;}
    answer = loadz(dim, walls, *size, bits);
    if (answer == 2) {return 6;}
    if (answer != 0) {return 4;}
    if (checkfull(walls, dim, start, *bits, *size) != 0) {return 2;}
    if (checkfull(walls, dim, stop, *bits, *size) != 0) {return 3;}
    if (getchar() != EOF) {return 5;}
    return 0;
}

void visit(unsigned int** walls, unsigned int** dim, unsigned int** coordinates, unsigned int bits, unsigned int size){
    int bit = 0;
    int p = 1;
    for (int i = 0; i < size; i++){
        int el = *(*coordinates + i);
        bit += (el - 1)*p;
        p *= *(*dim + i);
    }
    *(*walls + bit) = 1;
}

int checkstop(unsigned int* coordinates, unsigned int* stop, unsigned int size){
    for (int i = 0; i < size; i++){
        if (*(coordinates + i) != *(stop + i)) {return 0;}
    }
    return 1;
}

unsigned int* copycoordinates(unsigned int* coordinates, unsigned int size){
    unsigned int* ans = (unsigned int*) malloc(size * sizeof(unsigned int));
    for (int i = 0; i < size; i++){
        *(ans + i) = *(coordinates + i);
    }
    return ans;
}

int findway(unsigned int** dim, unsigned int** start, unsigned int** stop, unsigned int** walls, unsigned int size, unsigned int bits){
    QueueArray* queue = malloc(sizeof(QueueArray));
    (*queue).value = start;
    (*queue).distance = 0;
    (*queue).next = NULL;
    while(!checkstop(*((*queue).value), *stop, size)){
        visit(walls, dim, (*queue).value, bits, size);
        for (int i = 0; i < size; i++){
            unsigned int* up = copycoordinates(*((*queue).value), size);
            unsigned int* down = copycoordinates(*((*queue).value), size);
            (*(up + i))++;
            (*(down + i))--;
            if (!checkfull(walls, dim, &up, bits, size)){
                putLast(queue, &up, (*queue).distance + 1);
            }
            if (!checkfull(walls, dim, &down, bits, size)){
                putLast(queue, &down, (*queue).distance + 1);
            }
        }
        deleteFirst(queue);
        if (queue == NULL){
            deleteAll(queue);            
            return -1;
        }
    }
    unsigned int ans = (*queue).distance;
    deleteAll(queue);
    return ans;
}


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
    int distance = findway(&dim, &start, &stop, &walls, size, bits);
    if (distance < 0) {printf("NO WAY");}
    else {printf("%d", distance);}
    end(&dim, &start, &stop, &walls);
    printf("OK");
    return 0;
}
