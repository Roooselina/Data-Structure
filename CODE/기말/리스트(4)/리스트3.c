#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node* next;
	int val;
}List;

List* insertFirst(List* l, int n) {
	List* p = (List*)malloc(sizeof(List));
	p->val = n;
	p->next = NULL;
	if (l == NULL) {
		l = p;
	}
	else {
		p->next = l;
		return p;
	}
	return l;
}

List* insert(List* head, List* prev, int n) {
	List* p = (List*)malloc(sizeof(List));
	p->val = n;
	p->next = NULL;
	if (head == NULL) {
		head = p;
	}
	else if (prev == NULL) {
		p->next = head;
		head = p;
	}
	else {
		p->next = prev->next;
		prev->next = p;
	}
	return head;
}
List* deleteFirst(List* l) {
	if (l != NULL) {
		List* p = l;
		l = p->next;
		free(p);
		return l;
	}
}

List* delete(List* l, List* prev) {
	if (l == NULL) {
		printf("ERROR");
	}
	else if (prev == NULL) {
		List* p = l;
		l = p->next;
		free(p);
		return l;
	}
	else {
		List* p = prev->next;
		prev->next = p->next;
		free(p);
		return l;
	}
}

List* search_list(List* l, int val) {
	if (l == NULL)
		printf("ERROR");
	List* p = l;
	while (p != NULL) {
		if (p->val == val)
			return p;
		p = p->next;
	}
	return 0;
}


void printList(List* l) {
	List* p = l;
	while (p != NULL) {
		printf("%d ", p->val);
		p = p->next;
	}
	printf("\n");
}


int main() {
    List* l = NULL;

    // insertFirst �׽�Ʈ
    printf("insertFirst�� ����Ͽ� �� �տ� ��� ����:\n");
    for (int i = 1; i <= 5; i++) {
        l = insertFirst(l, i);
        printList(l);
    }

    // insert �׽�Ʈ
    printf("\ninsert (prev = NULL)�� ����Ͽ� �� �տ� ��� ����:\n");
    l = insert(l, NULL, 0);
    printList(l);

    printf("\ninsert�� ����Ͽ� �߰��� ��� ���� (�� ��° ��� �ڿ�):\n");
    List* second = l->next->next;  // �� ��° ��Ҹ� ����Ŵ
    l = insert(l, second, 99);
    printList(l);

	printf("\nƯ�� ��� ã�� 99, 10:\n");
	int q = search_list(l, 99)->val;
	printf("99: %d\n", q);


    // deleteFirst �׽�Ʈ
    printf("\ndeleteFirst�� ����Ͽ� ù ��° ��� ����:\n");
    l = deleteFirst(l);
    printList(l);

    // delete �׽�Ʈ
    printf("\ndelete (prev = head)�� ����Ͽ� �� ��° ��� ����:\n");
    List* first = l;
    l = delete(l, first);
    printList(l);


    return 0;
}

