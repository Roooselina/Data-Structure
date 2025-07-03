#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define the structure for the queue
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create a new node
Node* newNode(int k) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = k;
    temp->next = NULL;
    return temp;
}

// Function to create a queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}
int dequeue(Queue* q) {
    // If the queue is empty, return a special value (e.g., -1)
    if (is_Empty(q)) {
        printf("Queue is empty, cannot dequeue.\n");
        return -1; // Assuming negative values are not used in the queue
    }

    // Store the previous front and move the front one node ahead
    Node* temp = q->front;
    q->front = q->front->next;

    // If the front becomes NULL, then change the rear to NULL as well
    if (q->front == NULL) {
        q->rear = NULL;
    }

    int data = temp->data;
    free(temp);
    return data;
}
// Function to add an element to the queue
void enqueue(Queue* q, int n) {
    // Create a new node
    Node* temp = newNode(n);

    // If the queue is empty, then the new node is both the front and rear
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    // Add the new node at the end of the queue and change the rear
    q->rear->next = temp;
    q->rear = temp;
}

// Function to check if the queue is empty
int is_Empty(Queue* q) {
    return (q->front == NULL);
}

// Function to print the queue
void printQueue(Queue* q) {
    if (is_Empty(q)) {
        printf("Queue is empty\n");
        return;
    }
    Node* temp = q->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Queue* q = createQueue();

    enqueue(q, 10);
    dequeue(q);
    if (is_Empty(q)) {
        printf("Queue is empty\n");
    }
    enqueue(q, 20);
    enqueue(q, 30);
    printQueue(q);

    // Check if the queue is empty
    if (is_Empty(q)) {
        printf("Queue is empty\n");
    }
    else {
        printf("Queue is not empty\n");
    }

    return 0;
}
