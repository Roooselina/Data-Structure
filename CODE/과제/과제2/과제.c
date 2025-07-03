#define _CRT_SECURE_NO_WARNINGS
#define MAX 100

#include <stdio.h>

// ��� ����� ������ ����ü
typedef struct {
    int row;
    int col;
    int val;
} DataInfo;

// ��� ����� ��� ����ü
typedef struct {
    DataInfo data[MAX];
    int row;
    int col;
    int num;
} SparseMatrix;

// ���͸� �����ϴ� ����ü
typedef struct {
    int data[MAX];
    int num;
} vector;

// ��� ��İ� ������ ���� �Լ�
vector matrix_vector_multi(SparseMatrix a, vector b) {
    vector c = { 0 }; // ��� ���� �ʱ�ȭ
    int ir = 0; // ��� ������ ���� �ε���

    for (int i = 0; i < a.row; i++) {
        int num = 0; // ��� ���� �ʱ�ȭ
        for (int j = 0; j < a.num; j++) { // a�� ��� ����ŭ �ݺ�
            if (a.data[j].row == i) { // ���� �࿡ �ش��ϴ� ����� ��
                for (int k = 0; k < b.num; k++) { // b�� ��� ����ŭ �ݺ�
                    if (a.data[j].col == k) { // ���� ���� b�� �ε����� ��ġ�ϴ� ���
                        num += a.data[j].val * b.data[k]; // ������ �����Ͽ� ����� ����
                    }
                }
            }
        }
        if (num != 0) { // ����� 0�� �ƴ� ��쿡�� ��� ���Ϳ� �߰�
            c.data[ir] = num;
            ir++;
        }
    }
    c.num = ir; // ��� ������ ��� �� ����
    return c;
}

// ��� ���͸� ����ϴ� �Լ�
void display(vector c) {
    int ip = 0; // ��� ������ ���� �ε���
    printf("VECTOR C: \n");
    for (int i = 0; i < c.num; i++) {
        printf("%d\n", c.data[i]);
    }
    printf("c�� ��: %d\n", 1); // ��� ���ʹ� ���� 1�� ����
    printf("c�� ��: %d\n", c.num);
    printf("c�� ���: %d\n", c.num);
}

int main() {
    SparseMatrix a = { { {0, 1, 7}, {1, 4, 9}, {1, 5, 3}, {2, 1, 6},
                        {3, 3, 5}, {3, 5, 5} }, 4, 6, 6 };
    vector b = { { 6, 5, 4, 3, 2, 1, 0}, 7 };
    vector c;

    if (a.col == b.num) {
        printf("������ �����մϴ�.\n");
        c = matrix_vector_multi(a, b);
    }
    else {
        printf("���� a�� ���� ���� b�� �� ���� ���� �ٸ��Ƿ� ������ ������ �� �����ϴ�.");
        return -1;
    }
    display(c);
    return 0;
}