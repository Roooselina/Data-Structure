#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int val;            // 노드의 값
    struct Node* link;  // 다음 노드를 가리키는 포인터
} Node;

// 리스트의 끝에 노드를 삽입하는 함수
Node* insert_last(Node* list, int n) {
    Node* p = (Node*)malloc(sizeof(Node)); // 새로운 노드 할당
    p->val = n;                            // 노드 값 설정
    p->link = NULL;                        // 다음 노드 포인터 초기화

    if (list == NULL)
        list = p; // 리스트가 비어있으면 새로운 노드를 리스트의 첫 노드로 설정
    else {
        Node* q = list;
        while (q->link != NULL) {
            q = q->link;
        }
        q->link = p; // 마지막 노드의 링크를 새로운 노드로 설정
    }
    return list;
}

// 두 개의 정렬된 리스트를 병합하는 함수
Node* merge(Node* list1, Node* list2) {
    Node* result = NULL; // 결과 리스트 초기화

    Node* l1 = list1;    // 첫 번째 리스트의 각 노드를 가리킬 포인터
    Node* l2 = list2;    // 두 번째 리스트의 각 노드를 가리킬 포인터

    // 두 리스트가 모두 끝나지 않았을 때까지 반복
    while (l1 != NULL && l2 != NULL) {

        //l1 값이 더 작을 때
        if (l1->val < l2->val) {
            result = insert_last(result, l1->val); // l1의 값을 결과 리스트에 삽입
            l1 = l1->link;                         // l1을 다음 노드로 이동
        }
        //l1, l2 값이 같을 때
        else if (l1->val == l2->val) {
            result = insert_last(result, l2->val); // l2의 값을 결과 리스트에 삽입
            // 1개의 값만 리스트에 넣으면 되기 때문에 l1, l2 포인터를 전부 이동시킨다
            l2 = l2->link;                         
            l1 = l1->link;                         
        }
        //l2 값이 더 작을 때
        else {
            result = insert_last(result, l2->val); // l2의 값을 결과 리스트에 삽입
            l2 = l2->link;                         
        }
    }
    // l1에 남은 노드를 결과 리스트에 삽입
    while (l1 != NULL) {
        result = insert_last(result, l1->val);
        l1 = l1->link;
    }
    // l2에 남은 노드를 결과 리스트에 삽입
    while (l2 != NULL) {
        result = insert_last(result, l2->val);
        l2 = l2->link;
    }
    return result;
}

// 특정 범위의 정수와 주어진 배수를 사용하여 리스트를 생성하는 함수
Node* cons_list(int start, int end, int evenNum) {
    Node* p = NULL;
    for (int i = start; i <= end; i++) {
        p = insert_last(p, i * evenNum);
    }
    return p;
}

// 리스트의 모든 노드를 출력하는 함수
void print_list(Node* list) {
    Node* p = list;
    while (p != NULL) {
        printf("%d ", p->val); 
        p = p->link;
    }
    printf("\n");
}

int main() {
    // 3의 배수를 사용하여 리스트1 생성
    Node* list1 = NULL;
    list1 = cons_list(1, 10, 3); 
    printf("list1 값: ");
    print_list(list1);

    // 5의 배수를 사용하여 리스트2 생성
    Node* list2 = NULL;
    list2 = cons_list(0, 9, 5); 
    printf("list2 값: ");
    print_list(list2);

    // 리스트1과 리스트2 병합
    list1 = merge(list1, list2); 
    printf("정렬된 병합 리스트 값: \n");
    print_list(list1);

    return 0;
}
