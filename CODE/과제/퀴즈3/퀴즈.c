#define _CRT_SECURE_NO_WARNINGS
#define MAX 100

#include <stdio.h>

typedef struct {
    int num[MAX];
    int top;
} stack;

int is_empty(stack data) {
    return (data.top == -1);
}

int is_full(stack data) {
    return (data.top == (MAX - 1));
}

void push(stack* data, int n) {
    if (is_full(*data))
        printf("리스트가 꽉 찼습니다.");
    else
        data->num[++(data->top)] = n;
}

int pop(stack* data) {
    if (is_empty(*data)) {
        printf("리스트가 비었습니다.");
        return -1;
    }
    else {
        return data->num[(data->top)--];
    }
}

int peek(stack data) {
    if (is_empty(data)) {
        printf("리스트가 비었습니다.");
        return -1;
    }
    else {
        return data.num[data.top];
    }
}

int remove(int n) {
    stack data;
    data.top = -1;

    int number[MAX];
    int i = 0;

    //숫자에서 각 자리의 숫자를 분리
    while (n != 0) {
        number[i] = n % 10;
        n /= 10;
        i++;
    }

    // 중복 제거 후 순서대로 스택에 저장
    for (int j = i - 1; j >= 0; j--) {
        if (is_empty(data) || number[j] != data.num[data.top]) {
            push(&data, number[j]);
        }
    }

    // 스택에 저장된 숫자를 거꾸로 꺼내 하나의 숫자로 합치기
    int result = 0;
    int multiplier = 1; // 자릿수를 결정하기 위한 변수
    while (!is_empty(data)) {
        result += pop(&data) * multiplier;
        multiplier *= 10; // 자릿수를 올리기
    }
    return result;
}

int main() {
    // 숫자 저장
    int n;
    scanf("%d", &n);


    // 중복된 숫자 제거 후 결과 출력
    printf("original value: %d \n", n);
    printf("modified value: %d", remove(n));

    return 0;
}

