#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

// ���� ����ü ����
typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

// ���� �ʱ�ȭ
void initialize(Stack* stack) {
    stack->top = -1;
}

// ������ ����ִ��� Ȯ��
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// ������ ���� á���� Ȯ��
int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// ���ÿ� ���Ҹ� �߰�(push)
void push(Stack* stack, char item) {
    if (isFull(stack)) {
        printf("������ ���� á���ϴ�.\n");
        return;
    }
    stack->items[++stack->top] = item;
}

// ���ÿ��� ���Ҹ� ����(pop)�ϰ� ��ȯ
char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("������ ��� �ֽ��ϴ�.\n");
        return '\0';
    }
    return stack->items[stack->top--];
}

// ������ top ���Ҹ� ��ȯ(peek)
char peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("������ ��� �ֽ��ϴ�.\n");
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
                push(&s, num); // ���� �״�� ���ÿ� ����
            }
            push(&s, c);
            num = 1;
        }
        i++;
    }
    if (!isEmpty(&s)) {
        push(&s, num); // ������ ������ ������ ���ÿ� ����
    }

    // ����� ���ڿ��� ���
    printf("����� ���ڿ�: ");
    while (!isEmpty(&s)) {
        printf("%c", pop(&s));
    }
    printf("\n");
}

int main(void)
{
    char str[MAX_SIZE];

    printf("������ ���ڿ��� �Է��Ͻÿ�: ");
    scanf("%s", str);
    run_length(str);
    
    return 0;
}
