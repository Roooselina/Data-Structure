#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 트리 노드 구조체 정의
typedef struct TreeNode {
    char name[100];
    char phoneNumber[15];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 새로운 트리 노드 생성 함수
TreeNode* createNode(const char* name, const char* phoneNumber) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newNode->name, name);
    strcpy(newNode->phoneNumber, phoneNumber);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 트리에 노드를 추가하는 함수
TreeNode* insert(TreeNode* root, const char* name, const char* phoneNumber) {
    if (root == NULL) {
        return createNode(name, phoneNumber);
    }

    if (strcmp(name, root->name) < 0) {
        root->left = insert(root->left, name, phoneNumber);
    }
    else if (strcmp(name, root->name) > 0) {
        root->right = insert(root->right, name, phoneNumber);
    }

    return root;
}

// 트리에서 이름을 탐색하고 전화번호를 출력하는 함수
void search(TreeNode* root, const char* name) {
    if (root == NULL) {
        printf("이름을 찾을 수 없습니다.\n");
        return;
    }

    if (strcmp(name, root->name) == 0) {
        printf("%s의 전화번호: %s\n", name ,root->phoneNumber);
    }
    else if (strcmp(name, root->name) < 0) {
        search(root->left, name);
    }
    else {
        search(root->right, name);
    }
}

// 트리에서 최소값을 찾는 함수
TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

// 트리에서 노드를 삭제하는 함수
TreeNode* deleteNode(TreeNode* root, const char* name) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        root->left = deleteNode(root->left, name);
    }
    else if (strcmp(name, root->name) > 0) {
        root->right = deleteNode(root->right, name);
    }
    else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        TreeNode* temp = minValueNode(root->right);
        strcpy(root->name, temp->name);
        strcpy(root->phoneNumber, temp->phoneNumber);
        root->right = deleteNode(root->right, temp->name);
    }
    
    return root;
}

// 메인 함수
int main() {
    TreeNode* root = NULL;
    char command;
    char name[100];
    char phoneNumber[15];

    while (1) {
        printf("(i: 입력, s: 검색, d: 삭제, q: 종료): ");
        scanf(" %c", &command);

        if (command == 'i') {
            printf("이름을 입력하세요: ");
            scanf("%s", name);
            printf("전화번호를 입력하세요: ");
            scanf("%s", phoneNumber);
            root = insert(root, name, phoneNumber);
        }
        else if (command == 's') {
            printf("검색할 이름을 입력하세요: ");
            scanf("%s", name);
            search(root, name);
        }
        else if (command == 'd') {
            printf("삭제할 이름을 입력하세요: ");
            scanf("%s", name);
            root = deleteNode(root, name);
        }
        else if (command == 'q') {
            break;
        }
        else {
            printf("잘못된 명령어입니다.\n");
        }
    }

    return 0;
}