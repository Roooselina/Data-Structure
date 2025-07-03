#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


#define MAX_SIZE 100

typedef struct {
    char num[MAX_SIZE];
    int top;
} stack;

void init(stack* data) {
    data->top = -1;
}

int is_empty(stack* data) {
    return (data->top == -1);
}

int is_full(stack* data) {
    return (data->top == (MAX_SIZE - 1));
}

void push(stack* data, int n) {
    if (is_full(&data)) {
        printf("����Ʈ�� �� á���ϴ�.");
        return -1;
    }
    else
        data->num[++(data->top)] = n;
}

int pop(stack* data) {
    char c;
    if (is_empty(&data)) {
        printf("����Ʈ�� ������ϴ�.");
        return -1;
    }
    else {
        c = data->num[data->top];
        data->num[data->top] = NULL;
        return data->num[(data->top)--];
    }
}

int peek(stack* data) {
    if (is_empty(&data)) {
        printf("����Ʈ�� ������ϴ�.");
        return -1;
    }
    else {
        return data->num[data->top];
    }
}

int paren_test(char ch[MAX_SIZE]) {
    stack data;
    init(&data);

    int i = 0;
    while (ch[i] != '\0') {
        if (ch[i] == '(' || ch[i] == '{' || ch[i] == '[')
            push(&data, ch[i]);

        else if (ch[i] == ')' || ch[i] == '}' || ch[i] == ']') {
            if (!is_empty(&data) &&
                ((ch[i] == ')' && peek(&data) == '(') ||
                    (ch[i] == '}' && peek(&data) == '{') ||
                    (ch[i] == ']' && peek(&data) == '['))) {
                pop(&data);
            }
            else {
                return 0; // ��ȣ�� ��ġ���� ������ ��� false ��ȯ
            }
        }
        i++;
    }
    if (is_empty(&data))
        return 1;
    else
        return 0;
}

int main() {
    // �� ����
    char ch[MAX_SIZE];
    scanf("%s", ch);

    // ��� ���
    printf("%s is %s\n", ch, (paren_test(ch)==1)?"Balance":"NOT Balance");
    return 0;
}
