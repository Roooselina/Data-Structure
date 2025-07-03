#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 스택 노드 구조 정의
typedef struct StackNode {
    TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

// 스택 구조 정의
typedef struct Stack {
    StackNode* top;
} Stack;

// 새로운 트리 노드 생성 함수
TreeNode* newTreeNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// 새로운 스택 노드 생성 함수
StackNode* newStackNode(TreeNode* treeNode) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->treeNode = treeNode;
    node->next = NULL;
    return node;
}

// 스택 생성 함수
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

// 스택에 요소 추가 함수
void push(Stack* stack, TreeNode* treeNode) {
    StackNode* node = newStackNode(treeNode);
    node->next = stack->top;
    stack->top = node;
}

// 스택에서 요소 제거 함수
TreeNode* pop(Stack* stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    StackNode* temp = stack->top;
    TreeNode* treeNode = temp->treeNode;
    stack->top = stack->top->next;
    free(temp);
    return treeNode;
}

// 스택이 비어 있는지 확인하는 함수
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// 노드를 방문하는 함수
void visit(TreeNode* node) {
    printf("%d ", node->data);
}

// 중위 순회 비재귀적 구현
void inorder_iter(TreeNode* root) {
    Stack* stack = createStack();
    TreeNode* current = root;

    while (current != NULL || !isEmpty(stack)) {
        // 현재 노드의 왼쪽 하위 트리를 스택에 푸시
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }

        // 스택에서 상위 노드를 팝하여 방문
        current = pop(stack);
        visit(current);

        // 현재 노드의 오른쪽 하위 트리로 이동
        current = current->right;
    }

    // 스택 메모리 해제
    free(stack);
}

// 후위 순회 비재귀적 구현
void postorder_iter(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    Stack* stack1 = createStack();
    Stack* stack2 = createStack();
    push(stack1, root);

    while (!isEmpty(stack1)) {
        TreeNode* node = pop(stack1);
        push(stack2, node);

        if (node->left != NULL) {
            push(stack1, node->left);
        }
        if (node->right != NULL) {
            push(stack1, node->right);
        }
    }

    while (!isEmpty(stack2)) {
        TreeNode* node = pop(stack2);
        visit(node);
    }

    // 스택 메모리 해제
    free(stack1);
    free(stack2);
}

// 전위 순회 비재귀적 구현
void preorder_iter(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    Stack* stack = createStack();
    push(stack, root);

    while (!isEmpty(stack)) {
        TreeNode* node = pop(stack);
        visit(node);

        // 오른쪽 자식을 먼저 스택에 넣고, 왼쪽 자식을 나중에 넣어야 전위 순회가 올바르게 수행됨
        if (node->right != NULL) {
            push(stack, node->right);
        }
        if (node->left != NULL) {
            push(stack, node->left);
        }
    }

    // 스택 메모리 해제
    free(stack);
}

int main() {
    // 주어진 순서에 따라 트리 생성
    TreeNode* root = newTreeNode(1);
    root->left = newTreeNode(2);
    root->right = newTreeNode(5);
    root->left->left = newTreeNode(3);
    root->left->right = newTreeNode(4);
    root->right->left = newTreeNode(6);
    root->left->right->left = newTreeNode(8);

    printf("In-order Traversal: ");
    inorder_iter(root);
    printf("\n");


    printf("Post-order Traversal: ");
    postorder_iter(root);
    printf("\n");

    printf("Pre-order Traversal: ");
    preorder_iter(root);
    printf("\n");

    return 0;
    return 0;
}
