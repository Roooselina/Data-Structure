#include <stdio.h>
#include <stdlib.h>

// Ʈ�� ��� ���� ����
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ť ��� ���� ����
typedef struct QueueNode {
    TreeNode* treeNode;
    struct QueueNode* next;
} QueueNode;

// ť ���� ����
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// ���ο� Ʈ�� ��� ���� �Լ�
TreeNode* newTreeNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// ���ο� ť ��� ���� �Լ�
QueueNode* newQueueNode(TreeNode* treeNode) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->treeNode = treeNode;
    node->next = NULL;
    return node;
}

// ť ���� �Լ�
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// ť�� ��� �߰� �Լ�
void enqueue(Queue* q, TreeNode* treeNode) {
    QueueNode* temp = newQueueNode(treeNode);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// ť���� ��� ���� �Լ�
TreeNode* dequeue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    QueueNode* temp = q->front;
    TreeNode* treeNode = temp->treeNode;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return treeNode;
}

// ť�� ��� �ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Ʈ�� ���غ� ��ȸ �Լ�
void levelOrderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    Queue* q = createQueue();
    enqueue(q, root);

    while (!isEmpty(q)) {
        TreeNode* current = dequeue(q);
        printf("%d ", current->data);

        if (current->left != NULL) {
            enqueue(q, current->left);
        }
        if (current->right != NULL) {
            enqueue(q, current->right);
        }
    }

    // ť �޸� ����
    free(q);
}

int main() {
    // Ʈ�� ����
    TreeNode* root = newTreeNode(1);
    root->left = newTreeNode(2);
    root->right = newTreeNode(3);
    root->left->left = newTreeNode(4);
    root->left->right = newTreeNode(5);
    root->right->left = newTreeNode(6);
    root->right->right = newTreeNode(7);

    printf("Level Order Traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    return 0;
}

