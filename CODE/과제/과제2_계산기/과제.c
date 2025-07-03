#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE 100

typedef struct {
    char* infix;
    int index;
} TokenInfo;

typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, char item) {
    if (isFull(stack)) {
        printf("������ ���� á���ϴ�.\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = item;
}

char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("������ ��� �ֽ��ϴ�.\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

char peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("������ ��� �ֽ��ϴ�.\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top];
}

int precedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

char getToken(char* infix, int* index) {
    char token = infix[*index];
    if (token != '\0') {
        (*index)++;
        return token;
    }
    return '\0';
}

char* postfix(char* infix) {
    Stack s;
    initialize(&s);

    char* result = (char*)malloc(MAX_SIZE * sizeof(char)); // ���� ǥ��� ���ڿ��� ������ �޸� ���� �Ҵ�


    int j = 0;
    int i = 0; // �ε��� ���� �߰�
    char token;
    while ((token = getToken(infix, &i)) != '\0') {
        if (token == '(' || token == '{' || token == '[') {
            push(&s, token);
        }

        else if (token == ')' || token == ']' || token == '}') {
            while (!isEmpty(&s) && peek(&s) != '(' && peek(&s) != '[' && peek(&s) != '{') {

                result[j++] = pop(&s); // '�� ��ȣ'�� ���� ������ ���ÿ��� pop�Ͽ� ���
                result[j++] = ' ';
            }

            pop(&s); // �� ��ȣ ����  
        }

        else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '^') {
            while (!isEmpty(&s) && (precedence(token) <= precedence(peek(&s)))) {
                result[j++] = pop(&s);
                result[j++] = ' ';
            }
            push(&s, token);
        }
        else if (token >= '0' && token <= '9') {
            do {
                result[j++] = token;
                token = getToken(infix, &i); // getToken �Լ� ȣ�� �� �ε����� ������Ʈ
            } while (token >= '0' && token <= '9');
            result[j++] = ' ';
            if (token != '\0')
                i--; // �ε����� �ϳ� ���ҽ��Ѽ� getToken ȣ�� ���� ��ġ�� �ǵ���
        }
    }

    while (!isEmpty(&s)) {
        result[j++] = pop(&s);
        result[j++] = ' ';
    }

    j -= 1;
    result[j] = '\0'; // ���� ǥ��� ���ڿ��� ���� NULL ���� �߰�
    return result; // ���� ǥ��� ��ȯ
}

int eval(char* postfix) {
    Stack s;
    initialize(&s);

    int i = 0;
    char token;
    int result = 1;
    while ((token = getToken(postfix, &i)) != '\0') {
        if (isdigit(token)) {
            int operand = 0;
            while (token <= '9' && token >= '0') {
                operand = operand * 10 + (token - '0');
                token = postfix[i++];
            }
            i--; // Move back one position since we've read one extra character
            push(&s, operand);
        }
        else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '^') {
            int operand2 = pop(&s);
            int operand1 = pop(&s);

            switch (token) {
            case '+':
                push(&s, operand1 + operand2);
                break;
            case '-':
                push(&s, operand1 - operand2);
                break;
            case '*':
                push(&s, operand1 * operand2);
                break;
            case '/':
                if (operand2 == 0) {
                    printf("0���� ���� �� �����ϴ�.\n");
                    exit(EXIT_FAILURE);
                }
                push(&s, operand1 / operand2);
                break;
            case '^':
                result = 1;
                for (int j = 0; j < operand2; j++) {
                    result *= operand1;
                }
                push(&s, result);
                break;

            }
        }
    }
    return pop(&s);
}


int main() {
    char infix[MAX_SIZE];
    printf("������ �Է��ϼ���: ");
    fgets(infix, MAX_SIZE, stdin);

    char* midResult = postfix(&infix);
    printf("���� ǥ���: %s\n", midResult);

    int result = eval(midResult);
    printf("���: %d\n", result);


    free(midResult);
    return 0;
}