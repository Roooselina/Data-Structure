#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct TreeNode {
    char val[10];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* items[MAX_SIZE];
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

void push(Stack* stack, TreeNode* item) {
    if (isFull(stack)) {
        printf("스택이 가득 찼습니다.\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = item;
}

TreeNode* pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("스택이 비어 있습니다.\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

TreeNode* peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("스택이 비어 있습니다.\n");
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

TreeNode* createNode(char* val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    int i = 0;
    while (val[i] != '\0' && i < 9) {
        newNode->val[i] = val[i];
        i++;
    }
    newNode->val[i] = '\0';
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void getToken(char* infix, int* index, char* buffer, int bufferSize) {
    int bufIndex = 0;
    while (infix[*index] != '\0' && infix[*index] != ' ' && bufIndex < bufferSize - 1) {
        buffer[bufIndex++] = infix[*index];
        (*index)++;
    }
    buffer[bufIndex] = '\0';
    if (infix[*index] != '\0') {
        (*index)++;
    }
}


TreeNode* cons_exptree(char* postfix) {
    Stack s;
    initialize(&s);

    int i = 0;
    char token[10];
    while (1) {
        getToken(postfix, &i, token, sizeof(token));
        if (token[0] == '\0') break;

        if (token[0] >= '0' && token[0] <= '9') {
            TreeNode* node = createNode(token);
            push(&s, node);
        }
        else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '^') {
            TreeNode* node = createNode(token);
            node->right = pop(&s);
            node->left = pop(&s);
            push(&s, node);
        }
    }
    return pop(&s);
}


int eval(TreeNode* root) {
    if (root == NULL)
        return 0;

    if (root->val[0] >= '0' && root->val[0] <= '9') {
        return strtol(root->val, NULL, 10);
    }

    int left_val = eval(root->left);
    int right_val = eval(root->right);

    switch (root->val[0]) {
    case '+': return left_val + right_val;
    case '-': return left_val - right_val;
    case '*': return left_val * right_val;
    case '/': return left_val / right_val;
    case '^': {
        int result = 1;
        for (int i = 0; i < right_val; i++)
            result *= left_val;
        return result;
    }
    default: return 0;
    }
}

char* postfix(char* infix) {
    Stack s;
    initialize(&s);

    char* result = (char*)malloc(MAX_SIZE * sizeof(char)); // 후위 표기식 문자열을 저장할 메모리 동적 할당
    if (result == NULL) {
        printf("메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }

    int j = 0;
    int i = 0; // 인덱스 변수 추가
    char token[10];
    while (infix[i] != '\0') {
        if (infix[i] >= '0' && infix[i] <= '9') {
            int k = 0;
            while ((infix[i] >= '0' && infix[i] <= '9') && k < 9) {
                token[k++] = infix[i++];
            }
            token[k] = '\0';
            for (k = 0; token[k] != '\0'; k++) {
                result[j++] = token[k];
            }
            result[j++] = ' ';
        }
        else if (infix[i] == '(' || infix[i] == '{' || infix[i] == '[') {
            push(&s, createNode((char[]) { infix[i++], '\0' }));
        }
        else if (infix[i] == ')' || infix[i] == ']' || infix[i] == '}') {
            while (!isEmpty(&s) && peek(&s)->val[0] != '(' && peek(&s)->val[0] != '[' && peek(&s)->val[0] != '{') {
                TreeNode* node = pop(&s);
                result[j++] = node->val[0];
                result[j++] = ' ';
                free(node);
            }
            free(pop(&s)); // 좌 괄호 제거
            i++;
        }
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') {
            while (!isEmpty(&s) && (precedence(infix[i]) <= precedence(peek(&s)->val[0]))) {
                TreeNode* node = pop(&s);
                result[j++] = node->val[0];
                result[j++] = ' ';
                free(node);
            }
            push(&s, createNode((char[]) { infix[i++], '\0' }));
        }
        else {
            i++;
        }
    }

    while (!isEmpty(&s)) {
        TreeNode* node = pop(&s);
        result[j++] = node->val[0];
        result[j++] = ' ';
        free(node);
    }

    j -= 1;
    result[j] = '\0'; // 후위 표기식 문자열의 끝에 NULL 문자 추가
    return result; // 후위 표기식 반환
}

int main() {
    char infix[MAX_SIZE];
    printf("수식을 입력하세요: ");
    fgets(infix, MAX_SIZE, stdin);
    infix[strcspn(infix, "\n")] = '\0';

    char* midResult = postfix(infix);
    printf("후위 표기식: %s\n", midResult);

    TreeNode* expTree = cons_exptree(midResult);
    int result = eval(expTree);
    printf("결과: %d\n", result);

    free(midResult);
    return 0;
}