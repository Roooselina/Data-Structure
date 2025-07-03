#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// ���� ����ü ����
typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack;

// ���� �ʱ�ȭ �Լ�
void initialize(Stack* stack) {
    stack->top = -1;
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// ���ÿ� ��Ҹ� �߰��ϴ� �Լ�
void push(Stack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = item;
}

// ���ÿ��� ��Ҹ� �����ϰ� ��ȯ�ϴ� �Լ�
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

// �Էµ� ���ڸ� �������� ����ϴ� �Լ�
void reverseNumber(int num) {
    Stack stack;
    initialize(&stack);

    // ���ڸ� ���ÿ� ����
    while (num != 0) {
        int digit = num % 10;
        push(&stack, digit);
        num /= 10;
    }

    Stack rev;
    initialize(&rev);

    while (!isEmpty(&stack)) {
        push(&rev, pop(&stack));
    }

    // ���ÿ��� ���ڸ� ������ �������� ���
    printf("Reversed Number: ");
    while (!isEmpty(&rev)) {
        printf("%d", pop(&rev));
    }
    printf("\n");
}

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    reverseNumber(num);

    return 0;
}
