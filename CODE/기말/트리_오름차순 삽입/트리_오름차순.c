#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// ���ο� ��� ���� �Լ�
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// ���� ���� ����Ʈ�� ó���� ���ο� ��带 �����ϴ� �Լ�
void insert_at_beginning(Node* head, int data) {
    Node* new_node = create_node(data);

    if (*head == NULL) {
        // ����Ʈ�� ��������� ���ο� ��尡 �ڱ� �ڽ��� ����Ű�� ����
        new_node->next = new_node;
        *head = new_node;
    }
    else {
        // ����Ʈ�� ������� ������
        Node* temp = *head;

        // ������ ��带 ã�� ���� ����Ʈ�� ��ȸ
        while (temp->next != head) {
            temp = temp->next;
        }

        // ���ο� ����� next�� ���� head�� ����Ű�� ����
        new_node->next = head;
        // ������ ����� next�� ���ο� ��带 ����Ű�� ����
        temp->next = new_node;
        // head�� ���ο� ���� ����
        head = new_node;
    }
}

// ����Ʈ�� ����ϴ� �Լ�
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
