#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
typedef struct node {
    int val;
    struct node* left;
    struct node* right;
} Node;

// �� ��带 �����ϴ� �Լ�
Node* create_node(int val) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Ʈ���� �����ϴ� �Լ�
Node* construct_tree() {
    // ��Ʈ ��� ����
    Node* root = create_node(1);

    // 2, 3 ��� ����
    Node *n2 = create_node(2);
    Node* n3 = create_node(3);
    root->left = n2;
    root->right = n3;

    // 4, 5, 6 ��� ����
    Node* n4 = create_node(4);
    Node* n5 = create_node(5);
    Node* n6= create_node(6);

    n2->left = n4;
    n2->right = n5;
    n3->left = n6;

    // 7, 8, 9 ��� ����
    Node* n7 = create_node(7);
    Node* n8 = create_node(8);
    Node* n9 = create_node(9);
    n4->right = n7;
    n5->left = n8;
    n6->right = n9;

    return root;
}

// ���� ��ȸ �Լ�
void preorder(Node* root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

// ���� ��ȸ �Լ�
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

// ���� ��ȸ �Լ�
void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}

int main() {
    // Ʈ�� ����
    Node* root = construct_tree();

    // ���� ��ȸ ���
    printf("Preorder: ");
    preorder(root);
    printf("\n");

    // ���� ��ȸ ���
    printf("Inorder: ");
    inorder(root);
    printf("\n");

    // ���� ��ȸ ���
    printf("Postorder: ");
    postorder(root);
    printf("\n");

    return 0;
}
