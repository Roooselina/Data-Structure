#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


typedef struct nodeType {
    int val;
    struct nodeType* next;
}nodeType;

void main() {
    nodeType* first;
    
    first= (nodeType*)malloc(sizeof(nodeType)); // first를 동적으로 할당
    first->val = 10;
    first->next = (nodeType*)malloc(sizeof(nodeType)); // next를 동적으로 할당


    first->next->val = 20;
    first->next->next = (nodeType*)malloc(sizeof(nodeType)); // next의 next를 동적으로 할당

    first->next->next->val = 30;
    first->next->next->next = NULL; // 마지막 노드의 next는 NULL로 설정 

    nodeType *p = first;
    while (p != NULL) {
        printf("%d\n", p->val);
        p = p->next;
    }

}

