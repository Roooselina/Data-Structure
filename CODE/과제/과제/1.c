#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 스택 구조체 정의
typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack;

// 스택 초기화 함수
void initialize(Stack* stack) {
    stack->top = -1;
}

// 스택이 비어있는지 확인하는 함수
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// 스택이 가득 찼는지 확인하는 함수
int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// 스택에 요소를 추가하는 함수
void push(Stack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = item;
}

// 스택에서 요소를 제거하고 반환하는 함수
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

// 입력된 숫자를 역순으로 출력하는 함수
void reverseNumber(int num) {
    Stack stack;
    initialize(&stack);

    // 숫자를 스택에 넣음
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

    // 스택에서 숫자를 꺼내며 역순으로 출력
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
