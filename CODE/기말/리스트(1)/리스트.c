#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
	int data[MAX];
	int size;
}List;

void init(List* l) {
	l->size = 0;
}

int is_Full(List* l) {
	return l->size == MAX;
}

int is_Empty(List* l) {
	return l->size == 0;
}

void insertLast(List* l, int n) {
	if (!is_Full(l)) {
		l->data[l->size++] = n;
	}
}

void insert(List* l, int pos, int n) {
	if (!is_Full(l)) {
		for (int i = l->size - 1; i >= pos; i--) {
			l->data[i + 1] = l->data[i];
		}
		l->data[pos] = n;
		l->size++;
	}
}

void delete(List* l, int pos) {
	if (!is_Empty(l) && pos<l->size) {
		int val = l->data[pos];
		for (int i = pos; i <= l->size-1; i++) 
			l->data[i] = l->data[i+1];		
		l->size--;
		printf("삭제된 값: %d\n", val);
	}
	
}

void print(List* l) {
	for (int i = 0; i < l->size; i++) {
		if (l->data[i] == NULL)
			printf("0 ");
		else {
			printf("%d ", l->data[i]);
		}
	}
	printf("\n");
}


void main() {
	List* l = (List*)malloc(sizeof(List));

	init(l);
	for (int i = 1; i <= 5; i++) {
		insertLast(l, i);
		print(l);
	}
	
	delete(l, 2);
	print(l);

	delete(l, 1);
	print(l);

	for (int i = 1; i <= 3; i++) {
		insert(l,1, i);
		print(l);
	}

}