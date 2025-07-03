#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        return 0;
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

// ������ �켱���� ��ȯ
int precedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

typedef struct {
    char *infix;
    int index;
}tokenType;


void init(tokenType* token, char* infix) {
    token->index = 0;
    token->infix = infix;
}

int get_token(tokenType* token) {
    // ������ �ǳʶٱ�
    while (token->infix[token->index] == ' ') {
        token->index++;
    }

    // ���� �����ϸ� ����
    if (token->infix[token->index] == '\0') {
        return '\0';
    }

    // �������� ���
    if (token->infix[token->index] == '+' || token->infix[token->index] == '-' || token->infix[token->index] == '*' || token->infix[token->index] == '/') {
        printf("%c\n", token->infix[token->index]);
        return token->infix[token->index++];
    }

    //��ȣ�� ���
    if (token->infix[token->index] == '(' || token->infix[token->index] == '{' || token->infix[token->index] == '[' ||
        token->infix[token->index] == ')' || token->infix[token->index] == '}' || token->infix[token->index] == ']') {
        printf("%c\n", token->infix[token->index]);
        return token->infix[token->index++];
    }

    // ������ ���
    int number = 0;
    while (token->infix[token->index] >= '0' && token->infix[token->index] <= '9') {
        number = number * 10 + (token->infix[token->index++] - '0');
    }
    printf("%d\n", number);
    return number;
}


char* infixToPostfix(char* infix) {
    int len = 0;
    while (infix[len] != '\0') {
        len++;
    }

    char* postfix = (char*)malloc((len + 1) * sizeof(char)); // ���� ǥ��� ���ڿ�
    if (postfix == NULL) {
        printf("�޸� �Ҵ翡 �����߽��ϴ�.\n");
        exit(EXIT_FAILURE);
    }
    Stack stack; // ������ ����
    initialize(&stack);

    tokenType token;
    init(&token, infix);

    char c;
    int j = 0; // ���� ǥ��� ���ڿ� �ε���
    while ((c = get_token(&token)) != '\0') {
        if (c == '+' || c == '-' || c == '*' || c == '/') { // �������� ���
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(c)) {
                postfix[j++] = pop(&stack); // ���� �����ں��� ������ top�� �ִ� �������� �켱������ ���ų� ������ pop�Ͽ� ���
            }
            push(&stack, c); // ���� �����ڸ� ���ÿ� push
        }
        else if (c == '(' || c == '{' || c == '[') {
            push(&stack, c); // '('�� ���ÿ� push
        }
        else if (c == ')' || c == ']' || c == '}') {
            while (!isEmpty(&stack) && peek(&stack) != '(' && peek(&stack) != '[' && peek(&stack) != '{') {
                postfix[j++] = pop(&stack); // '('�� ���� ������ ���ÿ��� pop�Ͽ� ���
            }
            pop(&stack); // '(' ����
        }
        else { // ������ ���
            postfix[j++] = c; // ���� ǥ��� ���ڿ��� �߰�
        }
    }

    // ���ÿ� ���� �ִ� ��� �����ڸ� ���
    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0'; // ���ڿ� ���� NULL ���� �߰�

    return postfix;
}




// ���� ǥ������� �־��� ������ ����Ͽ� ����� ��ȯ�ϴ� �Լ�
int evaluatePostfix(char* postfix) {
    Stack stack;
    initialize(&stack);

    int len = strlen(postfix);
    for (int i = 0; i < len; i++) {
        char c = postfix[i];
        if (isdigit(c)) { // �ǿ������� ���
            push(&stack, c - '0'); // ���ڸ� ���ڷ� ��ȯ�Ͽ� ���ÿ� push
        }
        else { // �������� ���
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            int result;
            switch (c) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            default:
                printf("�߸��� �������Դϴ�.\n");
                exit(EXIT_FAILURE);
            }
            push(&stack, result); // ��� ����� ���ÿ� push
        }
    }

    return peek(&stack); // ���� ��� ��ȯ
}

int main() {
    char infix[100];
    printf("�� �Է�: ");
    scanf("%[^\n]s", infix);
   

    char* postfix = infixToPostfix(infix);
    printf("��ȯ�� ����: %s\n", postfix);

    int num = evaluatePostfix(postfix);

    free(postfix); // �޸� ����
    printf("��� ��: %d\n", num);
    return 0;
}
