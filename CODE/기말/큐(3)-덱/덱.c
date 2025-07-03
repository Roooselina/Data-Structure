#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int rear, front;
    int data[MAX];
} Q;

void init(Q* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Q* q) {
    return q->front == q->rear;
}

int isFull(Q* q) {
    return q->rear == MAX - 1;
}

void insertRear(Q* q, int n) {
    if (!isFull(q))
        q->data[(++q->rear + MAX) % MAX] = n;
    else
        printf("Queue is full\n");
}

void insertFront(Q* q, int n) {
    if (!isFull(q))
        q->data[(q->front-- + MAX) % MAX] = n;
}


int deleteRear(Q* q) {
    if (!isEmpty(q)) {
        return q->data[(q->rear-- + MAX) % MAX];
    }
}


int deleteFront(Q* q) {
    if (!isEmpty(q))
        return q->data[(++q->front + MAX) % MAX];
    else {
        printf("Queue is empty\n");
        return -1; // 혹은 다른 적절한 에러 값
    } 
}

void print(Q* q) {
    if (!isEmpty(q)) {
        for (int i = q->front + 1; i <= q->rear; i++)
            printf("%d ", q->data[(i+MAX)%MAX]);
        printf("\n");
    }
    else {
        printf("Queue is empty\n");
    }
}

void peek(Q* q) {
    int i = (q->front + 1 + MAX) % MAX;
    printf("%d ", q->data[i]);
}

int main() {
    Q* q = (Q*)malloc(sizeof(Q));
    init(q);  // 포인터 전달 시 &q가 아닌 q로 전달

    for (int i = 1; i <= 4; i++) {
        insertFront(q, i);
        print(q);
    }

    deleteFront(q);
    print(q);

    deleteRear(q);
    print(q);

    for (int i = 1; i <= 3; i++) {
        insertRear(q, i);
        print(q);
    }
    peek(q);

    free(q);
    return 0;
}