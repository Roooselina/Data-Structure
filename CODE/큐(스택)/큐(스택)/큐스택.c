#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct node {
    int val;
    struct node* left;
    struct node* right;
} Node;

// 새 노드를 생성하는 함수
Node* create_node(int val) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// 트리를 구성하는 함수
Node* construct_tree() {
    // 루트 노드 생성
    Node* root = create_node(1);

    // 2, 3 노드 생성
    Node *n2 = create_node(2);
    Node* n3 = create_node(3);
    root->left = n2;
    root->right = n3;

    // 4, 5, 6 노드 생성
    Node* n4 = create_node(4);
    Node* n5 = create_node(5);
    Node* n6= create_node(6);

    n2->left = n4;
    n2->right = n5;
    n3->left = n6;

    // 7, 8, 9 노드 생성
    Node* n7 = create_node(7);
    Node* n8 = create_node(8);
    Node* n9 = create_node(9);
    n4->right = n7;
    n5->left = n8;
    n6->right = n9;

    return root;
}

// 전위 순회 함수
void preorder(Node* root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

// 중위 순회 함수
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

// 후위 순회 함수
void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}

int main() {
    // 트리 구성
    Node* root = construct_tree();

    // 전위 순회 출력
    printf("Preorder: ");
    preorder(root);
    printf("\n");

    // 중위 순회 출력
    printf("Inorder: ");
    inorder(root);
    printf("\n");

    // 후위 순회 출력
    printf("Postorder: ");
    postorder(root);
    printf("\n");

    return 0;
}
