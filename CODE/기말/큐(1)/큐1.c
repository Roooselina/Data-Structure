#include <stdio.h>
#include <stdlib.h>

#define MAX 5

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

void enqueue(Q* q, int n) {
    if (!isFull(q))
        q->data[++q->rear] = n;
    else
        printf("Queue is full\n");
}

int dequeue(Q* q) {
    if (!isEmpty(q))
        return q->data[++q->front];
    else {
        printf("Queue is empty\n");
        return -1; // 혹은 다른 적절한 에러 값
    }
}

void print(Q* q) {
    if (!isEmpty(q)) {
        for (int i = q->front + 1; i <= q->rear; i++)
            printf("%d ", q->data[i]);
        printf("\n");
    }
    else {
        printf("Queue is empty\n");
    }
}

int main() {
    Q* q = (Q*)malloc(sizeof(Q));
    init(q);  // 포인터 전달 시 &q가 아닌 q로 전달

    for (int i = 1; i <= 4; i++) {
        enqueue(q, i);
        print(q);
    }

    dequeue(q);
    print(q);

    dequeue(q);
    print(q);

    free(q);
    return 0;
}
