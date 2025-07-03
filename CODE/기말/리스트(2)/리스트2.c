#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node *next;
	int val;
}Node;

void main() {
    Node* head = NULL;

    Node* p1 = (Node*)malloc(sizeof(Node)); // 첫 번째 노드
    p1->next = NULL;
    p1->val = 10;
    head = p1;

    p1 = (Node*)malloc(sizeof(Node)); // 두 번째 노드
    p1->next = NULL;
    p1->val = 20;
    head->next = p1;

    printf("%d %d\n", head->val, head->next->val);
}