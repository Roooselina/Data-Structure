#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
typedef struct Node {
    int val;            // ����� ��
    struct Node* link;  // ���� ��带 ����Ű�� ������
} Node;

// ����Ʈ�� ���� ��带 �����ϴ� �Լ�
Node* insert_last(Node* list, int n) {
    Node* p = (Node*)malloc(sizeof(Node)); // ���ο� ��� �Ҵ�
    p->val = n;                            // ��� �� ����
    p->link = NULL;                        // ���� ��� ������ �ʱ�ȭ

    if (list == NULL)
        list = p; // ����Ʈ�� ��������� ���ο� ��带 ����Ʈ�� ù ���� ����
    else {
        Node* q = list;
        while (q->link != NULL) {
            q = q->link;
        }
        q->link = p; // ������ ����� ��ũ�� ���ο� ���� ����
    }
    return list;
}

// �� ���� ���ĵ� ����Ʈ�� �����ϴ� �Լ�
Node* merge(Node* list1, Node* list2) {
    Node* result = NULL; // ��� ����Ʈ �ʱ�ȭ

    Node* l1 = list1;    // ù ��° ����Ʈ�� �� ��带 ����ų ������
    Node* l2 = list2;    // �� ��° ����Ʈ�� �� ��带 ����ų ������

    // �� ����Ʈ�� ��� ������ �ʾ��� ������ �ݺ�
    while (l1 != NULL && l2 != NULL) {

        //l1 ���� �� ���� ��
        if (l1->val < l2->val) {
            result = insert_last(result, l1->val); // l1�� ���� ��� ����Ʈ�� ����
            l1 = l1->link;                         // l1�� ���� ���� �̵�
        }
        //l1, l2 ���� ���� ��
        else if (l1->val == l2->val) {
            result = insert_last(result, l2->val); // l2�� ���� ��� ����Ʈ�� ����
            // 1���� ���� ����Ʈ�� ������ �Ǳ� ������ l1, l2 �����͸� ���� �̵���Ų��
            l2 = l2->link;                         
            l1 = l1->link;                         
        }
        //l2 ���� �� ���� ��
        else {
            result = insert_last(result, l2->val); // l2�� ���� ��� ����Ʈ�� ����
            l2 = l2->link;                         
        }
    }
    // l1�� ���� ��带 ��� ����Ʈ�� ����
    while (l1 != NULL) {
        result = insert_last(result, l1->val);
        l1 = l1->link;
    }
    // l2�� ���� ��带 ��� ����Ʈ�� ����
    while (l2 != NULL) {
        result = insert_last(result, l2->val);
        l2 = l2->link;
    }
    return result;
}

// Ư�� ������ ������ �־��� ����� ����Ͽ� ����Ʈ�� �����ϴ� �Լ�
Node* cons_list(int start, int end, int evenNum) {
    Node* p = NULL;
    for (int i = start; i <= end; i++) {
        p = insert_last(p, i * evenNum);
    }
    return p;
}

// ����Ʈ�� ��� ��带 ����ϴ� �Լ�
void print_list(Node* list) {
    Node* p = list;
    while (p != NULL) {
        printf("%d ", p->val); 
        p = p->link;
    }
    printf("\n");
}

int main() {
    // 3�� ����� ����Ͽ� ����Ʈ1 ����
    Node* list1 = NULL;
    list1 = cons_list(1, 10, 3); 
    printf("list1 ��: ");
    print_list(list1);

    // 5�� ����� ����Ͽ� ����Ʈ2 ����
    Node* list2 = NULL;
    list2 = cons_list(0, 9, 5); 
    printf("list2 ��: ");
    print_list(list2);

    // ����Ʈ1�� ����Ʈ2 ����
    list1 = merge(list1, list2); 
    printf("���ĵ� ���� ����Ʈ ��: \n");
    print_list(list1);

    return 0;
}
