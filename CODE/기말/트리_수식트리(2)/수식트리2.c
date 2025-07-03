#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ʈ�� ���
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    int isThread;
} TreeNode;

// ���ο� ��� ����
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThread = 0;
    return newNode;
}

// ������ ��ȸ
TreeNode* cons_thread_tree_prev(TreeNode* root, TreeNode* prev) {
    if (root == NULL) return prev;

    if (root->left != NULL) {
        prev = cons_thread_tree_prev(root->left, prev);
    }

    if (prev != NULL && prev->right == NULL) {
        prev->right = root;
        prev->isThread = 1;
    }

    prev = root;

    if (root->right != NULL) {
        prev = cons_thread_tree_prev(root->right, prev);
    }

    return prev;
}

// ������ ���� Ʈ�� ����
TreeNode* cons_thread_tree(TreeNode* root) {
    TreeNode* prev = NULL;
    cons_thread_tree_prev(root, prev);
    return root;
}

// Ʈ�� ���� ���
void thread_inorder(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* current = root;
    while (current->left != NULL) {
        current = current->left;
    }

    while (current != NULL) {
        printf("%d ", current->data);

        if (current->isThread==1) {
            current = current->right;
        }
        else {
            current = current->right;
            while (current != NULL && current->left != NULL) {
                current = current->left;
            }
        }
    }
}

int main() {
    TreeNode* T = createNode(1);

    T->left = createNode(2);
    T->right = createNode(3);

    T->left->left = createNode(4);
    T->left->right = createNode(5);
    T->right->left = createNode(6);

    T->left->left->right = createNode(7);
    T->left->right->left = createNode(8);
    T->right->left->right = createNode(9);

    TreeNode* root = cons_thread_tree(T);

    // Ʈ�� ���� ��ȸ ���
    printf("Ʈ�� ���� ��ȸ: ");
    thread_inorder(root);

    return 0;
}
