#include <stdio.h>
#include <stdlib.h>

typedef struct QueueArray QueueArray;

struct QueueArray{
    unsigned int** value;
    unsigned int distance;
    QueueArray* next;
};

QueueArray* deleteFirst(QueueArray* queue){
    if (queue == NULL){
        return NULL;
    }
    if((*queue).next == NULL) {
        return NULL;
    }
    QueueArray* ans = (*queue).next;
    free(queue);
    queue = NULL;
    return ans;
}

void deleteAll(QueueArray * queue){
    if (queue == NULL){
        return;
    }
    while((*queue).next != NULL){
        queue = deleteFirst(queue);
    }
    free(queue);
}

// void putLast(QueueArray* start, unsigned int distance){
void putLast(QueueArray* start, unsigned int** el, unsigned int distance){
    if (start == NULL){
        // QueueArray* start = malloc(sizeof(QueueArray));
        (*start).value = el;
        (*start).distance = distance;
        (*start).next = NULL;
    }
    QueueArray* current = start;
    while((*current).next != NULL){
        current = (*current).next;
    }
    QueueArray* new = malloc(sizeof(QueueArray));
    (*new).value = el;
    (*new).distance = distance;
    (*new).next = NULL;
    (*current).next = new;
}

unsigned int amount(QueueArray* start){
    if (start == NULL) {
        return 0;
    }
    unsigned int ans = 1;
    QueueArray* current = start;
    while((*current).next != NULL){
        ans++;
        current = (*current).next;
    }
    return ans;
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
//     queue -> distance = 69;
//     queue -> next = NULL;
//     // QueueArray * a = malloc(sizeof(QueueArray));
//     // a -> value = 420;
//     // a -> next = NULL;
//     // queue -> next = a;
//     // // put(queue, 420);

//     printf("%d ", amount(queue));
//     putLast(queue, 13);
//     printf("%d ", amount(queue));
//     putLast(queue, 1);
//     printf("%d ", amount(queue));
//     putLast(queue, 2);
//     printf("%d ", amount(queue));
//     putLast(queue, 3);
//     printf("%d ", amount(queue));
//     putLast(queue, 4);
//     printf("%d ", amount(queue));
//     queue = deleteFirst(queue);
//     printf("%d ", amount(queue));
//     queue = deleteFirst(queue);
//     printf("%d ", amount(queue));
//     queue = deleteFirst(queue);
//     printf("%d ", amount(queue));
//     queue = deleteFirst(queue);
//     printf("%d ", amount(queue));
//     queue = deleteFirst(queue);
//     printf("%d ", amount(queue));
//     queue = deleteFirst(queue);
//     printf("%d ", amount(queue));
    
//     deleteAll(queue);
//     printf("%d ", amount(queue));
//     // free(queue);
//     return 0;
// }