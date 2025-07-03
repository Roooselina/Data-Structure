#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

typedef struct {
	int row;
	int col;
	int val;
}elt_ty;

typedef struct {
	elt_ty data[50];
    int row;
    int col;
	int num;
}sparse_matrix;


sparse_matrix add_sparseMatrix(sparse_matrix p, sparse_matrix q) {
    sparse_matrix r;
    int num = 0;
    int p_dx = 0, q_dx = 0, r_dx = 0;

    while (p_dx < p.num && q_dx < q.num) {
        if (p.data[p_dx].row < q.data[q_dx].row || (p.data[p_dx].row == q.data[q_dx].row && p.data[p_dx].col < q.data[q_dx].col)) {
            r.data[r_dx].row = p.data[p_dx].row;
            r.data[r_dx].col = p.data[p_dx].col;
            r.data[r_dx++].val = p.data[p_dx].val;
            num++;
            p_dx++;
        }
        else if (p.data[p_dx].row > q.data[q_dx].row || (p.data[p_dx].row == q.data[q_dx].row && p.data[p_dx].col > q.data[q_dx].col)) {
            r.data[r_dx].row = q.data[q_dx].row;
            r.data[r_dx].col = q.data[q_dx].col;
            r.data[r_dx++].val = q.data[q_dx].val;
            num++;
            q_dx++;
        }
        else {
            r.data[r_dx].row = p.data[p_dx].row;
            r.data[r_dx].col = p.data[p_dx].col;
            r.data[r_dx++].val = p.data[p_dx].val + q.data[q_dx].val;
            num++;
            p_dx++;
            q_dx++;
        }
    }

    while (p_dx < p.num) {
        r.data[r_dx++] = p.data[p_dx++];
        num++;
    }
    while (q_dx < q.num) {
        r.data[r_dx++] = q.data[q_dx++];
        num++;
    }

    r.num = num;
    r.col = q.col;
    r.row = q.row;
    return r;
}



void print(sparse_matrix p, sparse_matrix q, sparse_matrix r) {
    printf("Matrix p:\n");
    for (int i = 0; i < p.row; i++) {
        for (int j = 0; j < p.col; j++) {
            int val = 0;
            for (int k = 0; k < p.num; k++) {
                if (p.data[k].row == i && p.data[k].col == j) {
                    val = p.data[k].val;
                    break;
                }
            }
            printf("%d ", val);
        }
        printf("\n");
    }
    printf("\np�� ���� ����: %d", p.row);
    printf("\np�� ���� ����: %d", p.col);
    printf("\np�� ����� ����: %d\n\n", p.num);

    printf("Matrix q:\n");
    for (int i = 0; i < q.row; i++) {
        for (int j = 0; j < q.col; j++) {
            int val = 0;
            for (int k = 0; k < q.num; k++) {
                if (q.data[k].row == i && q.data[k].col == j) {
                    val = q.data[k].val;
                    break;
                }
            }
            printf("%d ", val);
        }
        printf("\n");
    }
    printf("\nq�� ���� ����: %d", q.row);
    printf("\nq�� ���� ����: %d", q.col);
    printf("\nq�� ����� ����: %d\n\n", q.num);

    printf("Matrix r:\n");
    for (int i = 0; i < r.row; i++) {
        for (int j = 0; j < r.col; j++) {
            int val = 0;
            for (int k = 0; k < r.num; k++) {
                if (r.data[k].row == i && r.data[k].col == j) {
                    val = r.data[k].val;
                    break;
                }
            }
            printf("%d ", val);
        }
        printf("\n");
    }
    printf("\nr�� ���� ����: %d", r.row);
    printf("\nr�� ���� ����: %d", r.col);
    printf("\np�� ����� ����: %d\n\n", r.num);
}

sparse_matrix changep(sparse_matrix p) {
    for (int i = 0; i < p.num; i++) {
        p.data[i].val = 1;
    }
    return p;
}


sparse_matrix changeq(sparse_matrix q) {
    for (int i = 0; i < q.num; i++) {
        q.data[i].val = 49;
    }
    return q;
}


void main() {
    sparse_matrix r;
    sparse_matrix p = {
        {
            {0, 2, 1}, {1, 5, 2}, {3, 1, 3},
            {3, 9, 4}, {4, 0, 5}, {4, 4, 6}, {4, 9, 7}
        },
           5, 11, 7
    };

    sparse_matrix q = {
        {
            {0, 0, 5}, {0, 4, 6}, {0, 9, 7}, {1, 1, 3}, {1, 5, 1},
            {1, 9, 4}, {2, 2, 1}, {3, 5, 2}, {4, 4, 1}, {4, 9, 1}
        },
        5, 10, 10
    };

    p = changep(p);
    q = changeq(q);
    if (q.row == p.row && q.col == p.col) {
        r = add_sparseMatrix(p, q);
        print(p, q, r);
    }
    else printf("�� ���� ������ ���� �ʾ� ������ ������ �� �����ϴ�.");
   

    return 0;
}