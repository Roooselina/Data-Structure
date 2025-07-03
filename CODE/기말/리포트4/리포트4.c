#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// ����ü ����: ���׽� ��(term)�� ��Ÿ���� ����ü
typedef struct {
    float coef; // ���(coefficient)
    int expo;  // ����(exponent)
} term_type;

// ����ü ����: ���׽�(polynomial)�� ��Ÿ���� ����ü
typedef struct {
    term_type terms[MAX]; // ���׽��� �׵��� �����ϴ� �迭
    int nums;             // ���׽� ���� ����
} poly;

// ���� ����Ʈ ��� ����ü ����: ���׽� ���� ���� ������ ���� ����Ʈ
typedef struct nodeType {
    float coef; // ���
    int expo;   // ����
    struct nodeType* next; // ���� ��带 ����Ű�� ������
} nodeType;

// �Լ� ����: ���� ����Ʈ�� �������� ��� �߰�
nodeType* insert_last(nodeType* list, float coef, int expo) {
    // ���ο� ��带 ���� �Ҵ��ϰ� �ʱ�ȭ
    nodeType* p = (nodeType*)malloc(sizeof(nodeType));
    p->coef = coef;
    p->expo = expo;
    p->next = NULL;

    // ����Ʈ�� ��������� �� ��带 ����Ʈ�� ù ���� ����
    if (list == NULL) {
        list = p;
    }
    // ����Ʈ�� ������� ������ ����Ʈ�� ���� �� ��带 �߰�
    else {
        nodeType* q = list;
        while (q->next != NULL) {
            q = q->next;
        }
        q->next = p;
    }
    return list;
}

// �Լ� ����: ���׽��� �迭���� ���� ����Ʈ�� ��ȯ
nodeType* ploy_array2list(poly p) {
    nodeType* list = NULL; // ����Ʈ �ʱ�ȭ

    // ���׽��� �� ���� ���� ����Ʈ�� �߰�
    for (int i = 0; i < p.nums; i++) {
        list = insert_last(list, p.terms[i].coef, p.terms[i].expo);
    }
    return list;
}

// �Լ� ����: �� ���׽��� ���� ����Ʈ ���·� ���ϱ�
nodeType* add_poly_list(nodeType* list1, nodeType* list2) {
    nodeType* result = NULL; // ��� ����Ʈ �ʱ�ȭ
    nodeType* currentList1 = list1; // ù ��° ���׽��� ���� ���
    nodeType* currentList2 = list2; // �� ��° ���׽��� ���� ���

    // �� ����Ʈ�� ��� ��ȸ�ϸ� �׵��� ����
    while (currentList1 != NULL && currentList2 != NULL) {
        if (currentList1->expo == currentList2->expo) {
            // ������ ������ ����� ���ϰ� ��� ����Ʈ�� �߰�
            float sum = currentList1->coef + currentList2->coef;
            if (sum != 0)
                result = insert_last(result, sum, currentList1->expo);
            currentList1 = currentList1->next;
            currentList2 = currentList2->next;
        }
        else if (currentList1->expo > currentList2->expo) {
            // ù ��° ����Ʈ�� ���� ������ ũ�� ��� ����Ʈ�� �߰�
            result = insert_last(result, currentList1->coef, currentList1->expo);
            currentList1 = currentList1->next;
        }
        else {
            // �� ��° ����Ʈ�� ���� ������ ũ�� ��� ����Ʈ�� �߰�
            result = insert_last(result, currentList2->coef, currentList2->expo);
            currentList2 = currentList2->next;
        }
    }

    // �����ִ� �׵��� ��� ����Ʈ�� �߰�
    while (currentList1 != NULL) {
        result = insert_last(result, currentList1->coef, currentList1->expo);
        currentList1 = currentList1->next;
    }

    while (currentList2 != NULL) {
        result = insert_last(result, currentList2->coef, currentList2->expo);
        currentList2 = currentList2->next;
    }

    return result;
}

// �Լ� ����: ���׽��� ���
void print_poly(nodeType* list) {
    nodeType* p = list;
    while (p != NULL) {
        // ��� ���
        printf("%.0f", p->coef);
        if (p->expo != 0) {
            // ������ 0�� �ƴϸ� x ���
            printf("x");
            if (p->expo != 1)
                // ������ 1�� �ƴϸ� ���� ���
                printf("^%d", p->expo);
            if (p->next != NULL) {
                // ���� ���� ������ + ���
                printf(" + ");
            }
        }
        p = p->next;
    }
    printf("\n");
}


void main() {
	poly poly1 = { {{10,5}, {5,2}, {6,1}, {1,0}}, 4 }; // 10x^5 + 5x^2 + 6^x + 1
	poly poly2 = { {{7,3}, {3,2}, {-6,1}}, 3 }; //7x^3 + 3x^2 - 6^x

	// ����Ʈ�� ǥ���� ���׽��� ����
	nodeType* list1 = ploy_array2list(poly1);
	nodeType* list2 = ploy_array2list(poly2);

	// ���׽� ����
	nodeType* list3 = add_poly_list(list1, list2);

	// ���׽� ���
	printf("list1: ");	// 10x^5 + 5x^2 + 6^x + 1
	print_poly(list1);

	printf("list2: ");	//7x^3 + 3x^2 - 6^x
	print_poly(list2);

	printf("�� ����Ʈ�� ��: ");	//10x^5 + 7x^3 + 8x^2 + 1
	print_poly(list3);

	// ���׽� ����
	free(list1);
	free(list2);
	free(list3);
}