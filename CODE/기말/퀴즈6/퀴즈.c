#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
	int key;
	struct node* link;
}nodeType;


nodeType* cons_list(nodeType* first) {
    printf("랜덤 값  : ");
    int ran;
    for (int i = 0; i < 20; i++) {
        ran = (rand() % 10) + 1;
        printf("%d    ", ran);

        nodeType* p = (nodeType*)malloc(sizeof(nodeType));
        p->key = ran;
        p->link = NULL;
        if (first == NULL) {
            first = p;
        }
        else {
            nodeType* q = first;
            while (q->link != NULL) {
                q = q->link;
            }
            q->link = p;
        }
    }
    return first;
}

void print_list(nodeType* first) {
    printf("\n저장된 값: ");
    nodeType* p = first;
    while (p != NULL) {
        printf("%d    ", p->key);
        p = p->link;
    }
    printf("\n");
}

int count(nodeType* first, int n) {
    nodeType* p = first;
    int num = 0;
    while (p != NULL) {
        if (p->key == n) {
            num++;
        }
        p = p->link;
    }
    return num;
}

int main() {
    srand(time(NULL));
    nodeType* head = NULL;

    head = cons_list(head);
    print_list(head);

    printf("\n");
    //예시로 모든 숫자의 개수 출력
    for (int i = 1; i <= 10; i++) {
        int num = count(head, i);
        printf("%d의 개수: %d\n", i, num);
    }

    return 0;
}