#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX 5

//���� ť ����
typedef struct {
	int data[MAX];
	int front, rear;
}QueueType;

//���� ť�� front, rear�� 0���� �ʱ�ȭ
void init(QueueType* q) {
	q->front = 0;
	q->rear = 0;
}

//front, rear�� ���� ���ٸ� ����ٰ� ����
int is_empty(QueueType q) {
	return (q.front == q.rear);
}

//rear+1�� max�� ���� �������� q�� front�� ���ٸ� �� á�ٰ� ����
int is_full(QueueType q) {
	return ((q.rear + 1 + MAX) % MAX == q.front);
}

//���� ť�� ���� �����ϴ� �Լ�
void enqueue(QueueType* q, int n) {
	if (!is_full(*q)) {	//q�� �����Ͱ� �� ���� �ʾ��� ���� ����
		q->rear = (q->rear + 1) % MAX;	// rear�� ��ȯ��Ŵ
		q->data[q->rear] = n;			//������ ����
	}
}

int dequeue(QueueType* q) {
	if (!is_empty(*q)) {	//q�� �����Ͱ� ���� �ʾ��� ���� ����
		q->front = (q->front + 1) % MAX;	// front�� ��ȯ��Ŵ
		return q->data[q->front];
	}
	else
		return -1; // ť�� ����ִ� ��� -1 ��ȯ
}

void queue_print(QueueType q) {
	int i = (q.front + 1) % MAX; // ť�� ���� ��ġ�� �ʱ�ȭ

	while (i != (q.rear + 1) % MAX) { // rear ���� ��ġ�� ������ ������ �ݺ�
		printf("%d\t", q.data[i]); // ������ ���
		i = (i + 1) % MAX; // i�� ��ȯ��Ŵ
	}
	printf("\n"); // �� �ٲ�
}


void main() {
	QueueType q;
	init(&q);
	for (int i = 1; i <= 2; i++) {
		enqueue(&q, i);
		queue_print(q);
	}

	dequeue(&q);
	queue_print(q);

	for (int i = 3; i <= 4; i++) {
		enqueue(&q, i);
		queue_print(q);
	}

	dequeue(&q);
	queue_print(q);

	for (int i = 5; i <= 6; i++) {
		enqueue(&q, i);
		queue_print(q);
	}

}