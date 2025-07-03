#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


typedef struct nodeType {
    int val;
    struct nodeType* next;
}nodeType;

void main() {
    nodeType* first;
    
    first= (nodeType*)malloc(sizeof(nodeType)); // first�� �������� �Ҵ�
    first->val = 10;
    first->next = (nodeType*)malloc(sizeof(nodeType)); // next�� �������� �Ҵ�


    first->next->val = 20;
    first->next->next = (nodeType*)malloc(sizeof(nodeType)); // next�� next�� �������� �Ҵ�

    first->next->next->val = 30;
    first->next->next->next = NULL; // ������ ����� next�� NULL�� ���� 

    nodeType *p = first;
    while (p != NULL) {
        printf("%d\n", p->val);
        p = p->next;
    }

}

