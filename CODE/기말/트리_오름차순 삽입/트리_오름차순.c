#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 새로운 노드 생성 함수
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// 원형 연결 리스트의 처음에 새로운 노드를 삽입하는 함수
void insert_at_beginning(Node* head, int data) {
    Node* new_node = create_node(data);

    if (*head == NULL) {
        // 리스트가 비어있으면 새로운 노드가 자기 자신을 가리키게 설정
        new_node->next = new_node;
        *head = new_node;
    }
    else {
        // 리스트가 비어있지 않으면
        Node* temp = *head;

        // 마지막 노드를 찾기 위해 리스트를 순회
        while (temp->next != head) {
            temp = temp->next;
        }

        // 새로운 노드의 next가 현재 head를 가리키게 설정
        new_node->next = head;
        // 마지막 노드의 next가 새로운 노드를 가리키게 설정
        temp->next = new_node;
        // head를 새로운 노드로 갱신
        head = new_node;
    }
}

// 리스트를 출력하는 함수
void print_list(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

int main() {
    Node* head = NULL;

    insert_at_beginning(&head, 3);
    insert_at_beginning(&head, 2);
    insert_at_beginning(&head, 1);

    print_list(head);

    return 0;
}
