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
        printf("리스트가 꽉 찼습니다.");
        return -1;
    }
    else
        data->num[++(data->top)] = n;
}

int pop(stack* data) {
    char c;
    if (is_empty(&data)) {
        printf("리스트가 비었습니다.");
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
        printf("리스트가 비었습니다.");
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
                return 0; // 괄호가 일치하지 않으면 즉시 false 반환
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
    // 식 저장
    char ch[MAX_SIZE];
    scanf("%s", ch);

    // 결과 출력
    printf("%s is %s\n", ch, (paren_test(ch)==1)?"Balance":"NOT Balance");
    return 0;
}
