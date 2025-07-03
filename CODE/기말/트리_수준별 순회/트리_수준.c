#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 큐 노드 구조 정의
typedef struct QueueNode {
    TreeNode* treeNode;
    struct QueueNode* next;
} QueueNode;

// 큐 구조 정의
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// 새로운 트리 노드 생성 함수
TreeNode* newTreeNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// 새로운 큐 노드 생성 함수
QueueNode* newQueueNode(TreeNode* treeNode) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->treeNode = treeNode;
    node->next = NULL;
    return node;
}

// 큐 생성 함수
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// 큐에 요소 추가 함수
void enqueue(Queue* q, TreeNode* treeNode) {
    QueueNode* temp = newQueueNode(treeNode);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// 큐에서 요소 제거 함수
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

// 큐가 비어 있는지 확인하는 함수
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// 트리 수준별 순회 함수
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

    // 큐 메모리 해제
    free(q);
}

int main() {
    // 트리 생성
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

