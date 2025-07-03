#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 4

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
	while (i != 1 && item.key >= h->heap[i / 2].key) {
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
}

element deleteMaxHeap(HeapType* h) {
	int parent, child;
	element item, temp;

		item = h->heap[1];
		temp = h->heap[h->heapSize--];
		parent = 1;
		child = 2;

		while (child <= h->heapSize) {
			if (child < h->heapSize && h->heap[child].key < h->heap[child + 1].key)
				child++;
			if (temp.key >= h->heap[child].key)
				break;
			h->heap[parent] = h->heap[child];
			parent = child;
			child *= 2;
		}
		h->heap[parent] = temp;
		return item;

}


void printArray(HeapType* h) {
	int size = h->heapSize;
	int level = 1;
	int index = 1;

	if (size == 0) {
		printf("Empty\n");
	}
	else if (size == MAX-1) {
		printf("Full\n");
	}

	printf("\n");
}

int main() {
	HeapType* heap = create();
	init(heap);

	char inputArray[100];

	do {
		fgets(inputArray, sizeof(inputArray), stdin);

		if (inputArray[0] == 'I') {
			if (heap->heapSize < MAX - 1) {
				char* ptr = strtok(inputArray, " ");
				ptr = strtok(NULL, " ");

				if (ptr != NULL) {
					element num;
					num.key = atoi(ptr);

					insertMaxHeap(heap, num);
				}
			}
			else 
				printArray(heap);
		}
		else if (inputArray[0] == 'D') {
			if (heap->heapSize != 0) {
				element root = deleteMaxHeap(heap);
				printf("Deleted root: %d\n", root.key);
			}
			else
				printArray(heap);
		}
		else if (inputArray[0] == 'Q') {
			break;
		}
	} while (1);

	free(heap);
	return 0;
}