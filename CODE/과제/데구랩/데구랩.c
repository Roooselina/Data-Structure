#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

// 스택 구조체 정의
typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

// 스택 초기화
void initialize(Stack* stack) {
    stack->top = -1;
}

// 스택이 비어있는지 확인
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// 스택이 가득 찼는지 확인
int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// 스택에 원소를 추가(push)
void push(Stack* stack, char item) {
    if (isFull(stack)) {
        printf("스택이 가득 찼습니다.\n");
        return;
    }
    stack->items[++stack->top] = item;
}

// 스택에서 원소를 제거(pop)하고 반환
char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("스택이 비어 있습니다.\n");
        return '\0';
    }
    return stack->items[stack->top--];
}

// 스택의 top 원소를 반환(peek)
char peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("스택이 비어 있습니다.\n");
        return '\0';
    }
    return stack->items[stack->top];
}

void run_length(char word[]) {
    Stack s;
    initialize(&s);
    int num = 1;
    int i = 0;
    while (word[i] != '\0') {
        char c = word[i];
        int num = 1;
        c = tolower(c);
        if (!isEmpty(&s) && peek(&s) == c) {
            num++;
        } else {
            if (!isEmpty(&s)) {
                push(&s, num); // 숫자 그대로 스택에 저장
            }
            push(&s, c);
            num = 1;
        }
        i++;
    }
    if (!isEmpty(&s)) {
        push(&s, num); // 마지막 문자의 개수를 스택에 저장
    }

    // 압축된 문자열을 출력
    printf("압축된 문자열: ");
    while (!isEmpty(&s)) {
        printf("%c", pop(&s));
    }
    printf("\n");
}

int main(void)
{
    char str[MAX_SIZE];

    printf("압축할 문자열을 입력하시오: ");
    scanf("%s", str);
    run_length(str);
    
    return 0;
}
