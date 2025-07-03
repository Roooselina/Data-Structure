#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX 100

// ���� ť ����
typedef struct {
    int data[MAX];
    int front, rear;
} QueueType;

// ���� ť�� front, rear�� 0���� �ʱ�ȭ
void init(QueueType* q) {
    q->front = 0;
    q->rear = 0;
}

// front, rear�� ���� ���ٸ� ���� ����ٰ� ����
int is_empty(QueueType q) {
    return (q.front == q.rear);
}

// rear+1�� max�� ���� �������� q�� front�� ���ٸ� ���� �� á�ٰ� ����
int is_full(QueueType q) {
    return ((q.rear + 1 + MAX) % MAX == q.front);
}

// ���� rear�� ���� �����ϴ� �Լ�
void add_rear(QueueType* q, int n) {
    if (!is_full(*q)) {    // ���� �����Ͱ� �� ���� �ʾ��� ���� ����
        q->rear = (q->rear + 1) % MAX; // rear�� ��ȯ��Ŵ
        q->data[q->rear] = n;          // ������ ����
    }
}

// ���� rear���� ���� �����ϴ� �Լ�
int delete_rear(QueueType* q) {
    if (!is_empty(*q)) {    // ���� �����Ͱ� ���� �ʾ��� ���� ����
        int result = q->data[q->rear];
        q->rear = (q->rear - 1 + MAX) % MAX;    // rear�� ��ȯ��Ŵ

        return result;
    }
    else
        return -1; // ���� ����ִ� ��� -1 ��ȯ
}

// ���� front�� ���� �����ϴ� �Լ�
void add_front(QueueType* q, int n) {
    if (!is_full(*q)) {    // ���� �����Ͱ� �� ���� �ʾ��� ���� ����
        q->data[q->front] = n;          // ������ ����
        q->front = (q->front - 1 + MAX) % MAX;    // rear�� ��ȯ��Ŵ
    }
}

// ���� front ���� �����ϴ� �Լ�
int delete_front(QueueType* q) {
    if (!is_empty(*q)) {    // ���� �����Ͱ� ���� �ʾ��� ���� ����
        q->front = (q->front + 1) % MAX;    // front�� ��ȯ��Ŵ
        return q->data[q->front];
    }
    else
        return -1; // ���� ����ִ� ��� -1 ��ȯ
}

// ȸ�� ���θ� Ȯ���ϴ� �Լ�
int is_palin(char* w) {
    QueueType deque;
    init(&deque);

    int i = 0;
    while (w[i] != '\0') {
        add_rear(&deque, w[i]); // ���ڿ��� ���� �߰�
        i++;
    }
    i = 0;
    while (!is_empty(deque)) {
        if (w[i] != delete_rear(&deque)) { // ���ڿ��� ó���� ���� ���Ͽ� ȸ�� ���� Ȯ��
            return 1; // ȸ���� �ƴ� ���
        }
        i++;
    }
    return 0; // ȸ���� ���
}

void main() {
    printf("�ݺ��� Ƚ��: ");
    int repeat;
    scanf("%d", &repeat);

    for (int i = 0; i < repeat; i++) {
        char w[MAX];

        printf("�Է��� ����: ");
        scanf("%s", w);

        printf("%s is %s", w, (is_palin(w) == 0 ? "Palindrome\n" : "NOT palindrome\n"));
    }
}
