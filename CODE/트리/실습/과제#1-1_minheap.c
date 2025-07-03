#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct {
	int key;
}element;

typedef struct {
	element heap[MAX];
	int heapSize;
}HeapType;

HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
	h->heapSize = 0;
}

void insertMaxHeap(HeapType* h, element item) {
	int i = ++h->heapSize;

	h->heap[i] = item;
	while (i != 1 && item.key <= h->heap[i / 2].key) {
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
}

int printArray(HeapType* h) {
	int size = h->heapSize;
	int level = 1; 
	int index = 1;

	if (size == 0) {
		printf("Heap is empty\n");
		return 0; }

	printf("노드 구조: \n");
	while (index <= size) {
		int limit = pow(2,level - 1);
		int printedNum = 0;
		while (printedNum < limit && index <= size) {
			printf("<%d> ", h->heap[index].key);
			index++;
			printedNum++;
		}

		printf("\n");
		level++;
	}
	printf("\n");
	return 1;
}

void main() {
	HeapType* heap = create();
	init(heap);

	//히프 비어있는지 검사
	printArray(heap);

	char inputArray[MAX];
	fgets(inputArray, sizeof(inputArray), stdin);

	char* ptr = strtok(inputArray, ", ");
	do {
		element num;
		num.key = atoi(ptr);

		insertMaxHeap(heap, num);
		printArray(heap);

		ptr = strtok(NULL, ", ");
	} while (ptr != NULL);

	//최소 히프 출력
	for (int i = 1; i <= heap->heapSize; i++) {
		printf("<%d> ", heap->heap[i].key);
	}

	free(heap);
}