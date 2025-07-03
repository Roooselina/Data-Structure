#include <stdio.h>
#include <stdlib.h>

// element ���Ͽ� ����
typedef union {
    int operand;
    char operator;
} element;

// TreeNode ����ü ����
typedef struct TreeNode {
    element data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ���ο� Ʈ�� ��� ���� �Լ� (�ǿ�����)
TreeNode* newOperandNode(int operand) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data.operand = operand;
    node->left = node->right = NULL;
    return node;
}

// ���ο� Ʈ�� ��� ���� �Լ� (������)
TreeNode* newOperatorNode(char operator) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data.operator = operator;
    node->left = node->right = NULL;
    return node;
}


// Ʈ���� ���̸� ����ϴ� �Լ�
int get_height(TreeNode* T) {
    if (T == NULL)
        return 0;
    else {

        return 1 + max(get_height(T->left), get_height(T->right));
    }
        
}

// Ʈ���� �� ��带 ����ϴ� �Լ�
int get_leaf(TreeNode* T) {
    if (T == NULL)
        return 0;
    if (T->left == NULL && T->right == NULL)
        return 1;
    return get_leaf(T->left) + get_leaf(T->right);
}

// ���� Ʈ���� ���� ��ȸ�ϸ� ����ϴ� �Լ�
int eval(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return root->data.operand;
    }

    int left_val = eval(root->left);
    int right_val = eval(root->right);

    switch (root->data.operator) {
    case '+':
        return left_val + right_val;
    case '-':
        return left_val - right_val;
    case '*':
        return left_val * right_val;
    case '/':
        return left_val / right_val;
    default:
        return 0;
    }
}

TreeNode* insert_node(TreeNode* root, int key) {
         if (root == NULL)
             return new_node(key);
         if (key < root->data.operand)
             root->left = insert_node(root->left, key);
         else if (key > root->data.operand)
             root->right = insert_node(root->right, key);
         return root;
     }

int main() {
    // ���� Ʈ�� ����: ((3 + 2) * (5 - 1))
    TreeNode* root = newOperatorNode('*');
    root->left = newOperatorNode('+');
    root->right = newOperatorNode('-');
    root->left->left = newOperandNode(3);
    root->left->right = newOperandNode(2);
    root->right->left = newOperandNode(5);
    root->right->right = newOperandNode(1);
    root->right->right->left = newOperandNode(1);

    // ���� Ʈ�� ��� �� ���� ���
    printf("Result of expression tree: %d\n", eval(root));
    printf("Height of the tree: %d\n", get_height(root));
    printf("Number of leaf nodes: %d\n", get_leaf(root));
    return 0;
}

