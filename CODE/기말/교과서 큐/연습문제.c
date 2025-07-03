#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ʈ�� ��� ����ü ����
typedef struct TreeNode {
    char name[100];
    char phoneNumber[15];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ���ο� Ʈ�� ��� ���� �Լ�
TreeNode* createNode(const char* name, const char* phoneNumber) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newNode->name, name);
    strcpy(newNode->phoneNumber, phoneNumber);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Ʈ���� ��带 �߰��ϴ� �Լ�
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

// Ʈ������ �̸��� Ž���ϰ� ��ȭ��ȣ�� ����ϴ� �Լ�
void search(TreeNode* root, const char* name) {
    if (root == NULL) {
        printf("�̸��� ã�� �� �����ϴ�.\n");
        return;
    }

    if (strcmp(name, root->name) == 0) {
        printf("%s�� ��ȭ��ȣ: %s\n", name ,root->phoneNumber);
    }
    else if (strcmp(name, root->name) < 0) {
        search(root->left, name);
    }
    else {
        search(root->right, name);
    }
}

// Ʈ������ �ּҰ��� ã�� �Լ�
TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

// Ʈ������ ��带 �����ϴ� �Լ�
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

// ���� �Լ�
int main() {
    TreeNode* root = NULL;
    char command;
    char name[100];
    char phoneNumber[15];

    while (1) {
        printf("(i: �Է�, s: �˻�, d: ����, q: ����): ");
        scanf(" %c", &command);

        if (command == 'i') {
            printf("�̸��� �Է��ϼ���: ");
            scanf("%s", name);
            printf("��ȭ��ȣ�� �Է��ϼ���: ");
            scanf("%s", phoneNumber);
            root = insert(root, name, phoneNumber);
        }
        else if (command == 's') {
            printf("�˻��� �̸��� �Է��ϼ���: ");
            scanf("%s", name);
            search(root, name);
        }
        else if (command == 'd') {
            printf("������ �̸��� �Է��ϼ���: ");
            scanf("%s", name);
            root = deleteNode(root, name);
        }
        else if (command == 'q') {
            break;
        }
        else {
            printf("�߸��� ��ɾ��Դϴ�.\n");
        }
    }

    return 0;
}