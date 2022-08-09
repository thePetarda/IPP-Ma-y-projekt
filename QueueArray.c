#include <stdio.h>
#include <stdlib.h>

typedef struct QueueArray QueueArray;

struct QueueArray{
    unsigned int** value;
    unsigned int distance;
    QueueArray* next;
};

QueueArray* deleteFirst(QueueArray* queue){
    if((*queue).next == NULL) {
        return NULL;
    }
    QueueArray* ans = (*queue).next;
    free(queue);
    queue = NULL;
    return ans;
}

void deleteAll(QueueArray * queue){
    while((*queue).next != NULL){
        queue = deleteFirst(queue);
    }
    free(queue);
}

void putLast(QueueArray* start, unsigned int** el, unsigned int distance){
    QueueArray* current = start;
    while((*current).next != NULL){
        current = (*current).next;
    }
    QueueArray* new = malloc(sizeof(QueueArray));
    (*new).value = el;
    (*new).distance = distance;
    (*new).next = NULL;
    (*current).next = new;
    // free(new);
}

// void print(QueueArray* start){
//     if (start == NULL) {return;}
//     QueueArray* current = start;
//     while((*current).next != NULL){
//         printf("%d ", (*current).value);
//         current = (*current).next;
//     }
//     printf("%d ", (*current).value);
// }

// int main(){
//     QueueArray *queue = malloc(sizeof(QueueArray));
//     queue -> value = 69;
//     queue -> next = NULL;
//     // QueueArray * a = malloc(sizeof(QueueArray));
//     // a -> value = 420;
//     // a -> next = NULL;
//     // queue -> next = a;
//     // // put(queue, 420);
//     putLast(queue, 13);
//     putLast(queue, 1);
//     putLast(queue, 2);
//     putLast(queue, 3);
//     putLast(queue, 4);
    
//     deleteAll(queue);
//     // free(queue);
//     return 0;
// }