#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX 100


//void main() {
//	stack stk1;
//	stack stk2;
//	
//	init(&stk1);
//	init(&stk2);
//
//	stack *stklist[] = { &stk1, &stk2 };
//
//	int n;
//	int result;
//	printf("반복할 횟수: ");
//	scanf("%d", &n);
//
//	if (n == 1) result = 0;
//	else if (n == 2) result = 1;
//	else {
//		int j = 0;
//		push(&stk1, 0);
//		push(&stk1, 1);
//
//		do {
//			int op2 = pop(& *stklist[(j) % 2]);
//			int op1 = pop(& *stklist[(j) % 2]);
//
//			push(&*stklist[(j+1) % 2], op2);
//			push(&*stklist[(j+1) % 2], (op1 + op2));
//			j++;
//		} while (j < n - 2);
//		result = pop(&*stklist[j % 2]);
//	}
//	printf("피보나치 %d번째 값: %d", n, result);
//}


typedef struct {
	int data[MAX];
	int top;
}stack;

void init(stack* q) {
	q->top = -1;
}

int isEmpty(stack* q) {
	return q->top == -1;
}

int isFull(stack* q) {
	return q->top == MAX - 1;
}

int pop(stack* q) {
	if (!isEmpty(&q))
		return q->data[(q->top)--];
}

int peek(stack* q) {
	if (!isEmpty(&q))
		return q->data[(q->top)];
}

void push(stack* q, int n) {
	if (!isFull(&q))
		q->data[++(q->top)] = n;
}

typedef struct {
	stack stk1;
	stack stk2;
}queue;

void enqueue(queue* q, int n) {
	if (!isFull(&q->stk1)) {
		push(&q->stk1, n);
	}
}

int dequeue(queue* q) {
	if (!isEmpty(&q->stk1)) {
		while (!isEmpty(&q->stk1)) {
			push(&q->stk2, pop(&q->stk1));
		}
	}
	return pop(&q->stk2);
}

void initQueue(queue* q) {
	init(&q->stk1);
	init(&q->stk2);
}

void main() {
	queue q;
	initQueue(&q);

	int n;
	printf("출력 범위: ");
	scanf("%d", &n);

	enqueue(&q, 0);
	enqueue(&q, 1);	
	int i = 0;
	while (i < n - 1) {
		int op1 = dequeue(&q);
		int op2 = dequeue(&q);
		printf("%d ", op1);
		enqueue(&q, op2);
		enqueue(&q, (op2 + op1));
		i++;
	}
	printf("%d ", dequeue(&q));
}