#define _CRT_SECURE_NO_WARNINGS
#define MAX 100

#include <stdio.h>

// 희소 행렬의 데이터 구조체
typedef struct {
    int row;
    int col;
    int val;
} DataInfo;

// 희소 행렬의 요소 구조체
typedef struct {
    DataInfo data[MAX];
    int row;
    int col;
    int num;
} SparseMatrix;

// 벡터를 저장하는 구조체
typedef struct {
    int data[MAX];
    int num;
} vector;

// 희소 행렬과 벡터의 곱셈 함수
vector matrix_vector_multi(SparseMatrix a, vector b) {
    vector c = { 0 }; // 결과 벡터 초기화
    int ir = 0; // 결과 벡터의 현재 인덱스

    for (int i = 0; i < a.row; i++) {
        int num = 0; // 결과 값을 초기화
        for (int j = 0; j < a.num; j++) { // a의 요소 수만큼 반복
            if (a.data[j].row == i) { // 현재 행에 해당하는 요소일 때
                for (int k = 0; k < b.num; k++) { // b의 요소 수만큼 반복
                    if (a.data[j].col == k) { // 현재 열과 b의 인덱스가 일치하는 경우
                        num += a.data[j].val * b.data[k]; // 곱셈을 수행하여 결과에 더함
                    }
                }
            }
        }
        if (num != 0) { // 결과가 0이 아닌 경우에만 결과 벡터에 추가
            c.data[ir] = num;
            ir++;
        }
    }
    c.num = ir; // 결과 벡터의 요소 수 설정
    return c;
}

// 결과 벡터를 출력하는 함수
void display(vector c) {
    int ip = 0; // 결과 벡터의 현재 인덱스
    printf("VECTOR C: \n");
    for (int i = 0; i < c.num; i++) {
        printf("%d\n", c.data[i]);
    }
    printf("c의 열: %d\n", 1); // 결과 벡터는 열이 1로 고정
    printf("c의 행: %d\n", c.num);
    printf("c의 요소: %d\n", c.num);
}

int main() {
    SparseMatrix a = { { {0, 1, 7}, {1, 4, 9}, {1, 5, 3}, {2, 1, 6},
                        {3, 3, 5}, {3, 5, 5} }, 4, 6, 6 };
    vector b = { { 6, 5, 4, 3, 2, 1, 0}, 7 };
    vector c;

    if (a.col == b.num) {
        printf("연산을 수행합니다.\n");
        c = matrix_vector_multi(a, b);
    }
    else {
        printf("벡터 a의 열과 벡터 b의 행 값이 서로 다르므로 연산을 수행할 수 없습니다.");
        return -1;
    }
    display(c);
    return 0;
}