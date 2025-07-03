#include <stdio.h>
#include <stdlib.h>

// Ʈ�� ��� ���� ����
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ���� ��� ���� ����
typedef struct StackNode {
    TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

// ���� ���� ����
typedef struct Stack {
    StackNode* top;
} Stack;

// ���ο� Ʈ�� ��� ���� �Լ�
TreeNode* newTreeNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// ���ο� ���� ��� ���� �Լ�
StackNode* newStackNode(TreeNode* treeNode) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->treeNode = treeNode;
    node->next = NULL;
    return node;
}

// ���� ���� �Լ�
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

// ���ÿ� ��� �߰� �Լ�
void push(Stack* stack, TreeNode* treeNode) {
    StackNode* node = newStackNode(treeNode);
    node->next = stack->top;
    stack->top = node;
}

// ���ÿ��� ��� ���� �Լ�
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

// ������ ��� �ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// ��带 �湮�ϴ� �Լ�
void visit(TreeNode* node) {
    printf("%d ", node->data);
}

// ���� ��ȸ ������� ����
void inorder_iter(TreeNode* root) {
    Stack* stack = createStack();
    TreeNode* current = root;

    while (current != NULL || !isEmpty(stack)) {
        // ���� ����� ���� ���� Ʈ���� ���ÿ� Ǫ��
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }

        // ���ÿ��� ���� ��带 ���Ͽ� �湮
        current = pop(stack);
        visit(current);

        // ���� ����� ������ ���� Ʈ���� �̵�
        current = current->right;
    }

    // ���� �޸� ����
    free(stack);
}

// ���� ��ȸ ������� ����
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

    // ���� �޸� ����
    free(stack1);
    free(stack2);
}

// ���� ��ȸ ������� ����
void preorder_iter(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    Stack* stack = createStack();
    push(stack, root);

    while (!isEmpty(stack)) {
        TreeNode* node = pop(stack);
        visit(node);

        // ������ �ڽ��� ���� ���ÿ� �ְ�, ���� �ڽ��� ���߿� �־�� ���� ��ȸ�� �ùٸ��� �����
        if (node->right != NULL) {
            push(stack, node->right);
        }
        if (node->left != NULL) {
            push(stack, node->left);
        }
    }

    // ���� �޸� ����
    free(stack);
}

int main() {
    // �־��� ������ ���� Ʈ�� ����
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
