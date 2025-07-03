#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX 5

//원형 큐 정의
typedef struct {
	int data[MAX];
	int front, rear;
}QueueType;

//원형 큐의 front, rear을 0으로 초기화
void init(QueueType* q) {
	q->front = 0;
	q->rear = 0;
}

//front, rear의 값이 같다면 비었다고 간주
int is_empty(QueueType q) {
	return (q.front == q.rear);
}

//rear+1을 max로 나눈 나머지가 q의 front와 같다면 꽉 찼다고 간주
int is_full(QueueType q) {
	return ((q.rear + 1 + MAX) % MAX == q.front);
}

//원형 큐에 값을 저장하는 함수
void enqueue(QueueType* q, int n) {
	if (!is_full(*q)) {	//q의 데이터가 꽉 차지 않았을 때만 실행
		q->rear = (q->rear + 1) % MAX;	// rear을 순환시킴
		q->data[q->rear] = n;			//데이터 저장
	}
}

int dequeue(QueueType* q) {
	if (!is_empty(*q)) {	//q의 데이터가 비지 않았을 때만 실행
		q->front = (q->front + 1) % MAX;	// front를 순환시킴
		return q->data[q->front];
	}
	else
		return -1; // 큐가 비어있는 경우 -1 반환
}

void queue_print(QueueType q) {
	int i = (q.front + 1) % MAX; // 큐의 시작 위치로 초기화

	while (i != (q.rear + 1) % MAX) { // rear 다음 위치에 도달할 때까지 반복
		printf("%d\t", q.data[i]); // 데이터 출력
		i = (i + 1) % MAX; // i를 순환시킴
	}
	printf("\n"); // 줄 바꿈
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