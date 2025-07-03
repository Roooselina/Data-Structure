#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        return 0;
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

// 연산자 우선순위 반환
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
    // 공백을 건너뛰기
    while (token->infix[token->index] == ' ') {
        token->index++;
    }

    // 끝에 도달하면 종료
    if (token->infix[token->index] == '\0') {
        return '\0';
    }

    // 연산자인 경우
    if (token->infix[token->index] == '+' || token->infix[token->index] == '-' || token->infix[token->index] == '*' || token->infix[token->index] == '/') {
        printf("%c\n", token->infix[token->index]);
        return token->infix[token->index++];
    }

    //괄호인 경우
    if (token->infix[token->index] == '(' || token->infix[token->index] == '{' || token->infix[token->index] == '[' ||
        token->infix[token->index] == ')' || token->infix[token->index] == '}' || token->infix[token->index] == ']') {
        printf("%c\n", token->infix[token->index]);
        return token->infix[token->index++];
    }

    // 숫자인 경우
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

    char* postfix = (char*)malloc((len + 1) * sizeof(char)); // 후위 표기법 문자열
    if (postfix == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        exit(EXIT_FAILURE);
    }
    Stack stack; // 연산자 스택
    initialize(&stack);

    tokenType token;
    init(&token, infix);

    char c;
    int j = 0; // 후위 표기법 문자열 인덱스
    while ((c = get_token(&token)) != '\0') {
        if (c == '+' || c == '-' || c == '*' || c == '/') { // 연산자일 경우
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(c)) {
                postfix[j++] = pop(&stack); // 현재 연산자보다 스택의 top에 있는 연산자의 우선순위가 높거나 같으면 pop하여 출력
            }
            push(&stack, c); // 현재 연산자를 스택에 push
        }
        else if (c == '(' || c == '{' || c == '[') {
            push(&stack, c); // '('는 스택에 push
        }
        else if (c == ')' || c == ']' || c == '}') {
            while (!isEmpty(&stack) && peek(&stack) != '(' && peek(&stack) != '[' && peek(&stack) != '{') {
                postfix[j++] = pop(&stack); // '('를 만날 때까지 스택에서 pop하여 출력
            }
            pop(&stack); // '(' 제거
        }
        else { // 숫자인 경우
            postfix[j++] = c; // 후위 표기법 문자열에 추가
        }
    }

    // 스택에 남아 있는 모든 연산자를 출력
    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0'; // 문자열 끝에 NULL 문자 추가

    return postfix;
}




// 후위 표기법으로 주어진 수식을 계산하여 결과를 반환하는 함수
int evaluatePostfix(char* postfix) {
    Stack stack;
    initialize(&stack);

    int len = strlen(postfix);
    for (int i = 0; i < len; i++) {
        char c = postfix[i];
        if (isdigit(c)) { // 피연산자인 경우
            push(&stack, c - '0'); // 문자를 숫자로 변환하여 스택에 push
        }
        else { // 연산자인 경우
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
                printf("잘못된 연산자입니다.\n");
                exit(EXIT_FAILURE);
            }
            push(&stack, result); // 계산 결과를 스택에 push
        }
    }

    return peek(&stack); // 최종 결과 반환
}

int main() {
    char infix[100];
    printf("식 입력: ");
    scanf("%[^\n]s", infix);
   

    char* postfix = infixToPostfix(infix);
    printf("변환된 수식: %s\n", postfix);

    int num = evaluatePostfix(postfix);

    free(postfix); // 메모리 해제
    printf("결과 값: %d\n", num);
    return 0;
}
