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
        printf("����Ʈ�� �� á���ϴ�.");
    else
        data->num[++(data->top)] = n;
}

int pop(stack* data) {
    if (is_empty(*data)) {
        printf("����Ʈ�� ������ϴ�.");
        return -1;
    }
    else {
        return data->num[(data->top)--];
    }
}

int peek(stack data) {
    if (is_empty(data)) {
        printf("����Ʈ�� ������ϴ�.");
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

    //���ڿ��� �� �ڸ��� ���ڸ� �и�
    while (n != 0) {
        number[i] = n % 10;
        n /= 10;
        i++;
    }

    // �ߺ� ���� �� ������� ���ÿ� ����
    for (int j = i - 1; j >= 0; j--) {
        if (is_empty(data) || number[j] != data.num[data.top]) {
            push(&data, number[j]);
        }
    }

    // ���ÿ� ����� ���ڸ� �Ųٷ� ���� �ϳ��� ���ڷ� ��ġ��
    int result = 0;
    int multiplier = 1; // �ڸ����� �����ϱ� ���� ����
    while (!is_empty(data)) {
        result += pop(&data) * multiplier;
        multiplier *= 10; // �ڸ����� �ø���
    }
    return result;
}

int main() {
    // ���� ����
    int n;
    scanf("%d", &n);


    // �ߺ��� ���� ���� �� ��� ���
    printf("original value: %d \n", n);
    printf("modified value: %d", remove(n));

    return 0;
}

