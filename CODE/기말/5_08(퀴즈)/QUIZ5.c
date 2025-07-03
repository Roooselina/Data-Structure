#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX 100

// 원형 큐 정의
typedef struct {
    int data[MAX];
    int front, rear;
} QueueType;

// 원형 큐의 front, rear을 0으로 초기화
void init(QueueType* q) {
    q->front = 0;
    q->rear = 0;
}

// front, rear의 값이 같다면 덱이 비었다고 간주
int is_empty(QueueType q) {
    return (q.front == q.rear);
}

// rear+1을 max로 나눈 나머지가 q의 front와 같다면 덱이 꽉 찼다고 간주
int is_full(QueueType q) {
    return ((q.rear + 1 + MAX) % MAX == q.front);
}

// 덱의 rear에 값을 저장하는 함수
void add_rear(QueueType* q, int n) {
    if (!is_full(*q)) {    // 덱의 데이터가 꽉 차지 않았을 때만 실행
        q->rear = (q->rear + 1) % MAX; // rear을 순환시킴
        q->data[q->rear] = n;          // 데이터 저장
    }
}

// 덱의 rear에서 값을 제거하는 함수
int delete_rear(QueueType* q) {
    if (!is_empty(*q)) {    // 덱의 데이터가 비지 않았을 때만 실행
        int result = q->data[q->rear];
        q->rear = (q->rear - 1 + MAX) % MAX;    // rear를 순환시킴

        return result;
    }
    else
        return -1; // 덱이 비어있는 경우 -1 반환
}

// 덱의 front에 값을 저장하는 함수
void add_front(QueueType* q, int n) {
    if (!is_full(*q)) {    // 덱의 데이터가 꽉 차지 않았을 때만 실행
        q->data[q->front] = n;          // 데이터 저장
        q->front = (q->front - 1 + MAX) % MAX;    // rear을 순환시킴
    }
}

// 덱의 front 값을 삭제하는 함수
int delete_front(QueueType* q) {
    if (!is_empty(*q)) {    // 덱의 데이터가 비지 않았을 때만 실행
        q->front = (q->front + 1) % MAX;    // front를 순환시킴
        return q->data[q->front];
    }
    else
        return -1; // 덱이 비어있는 경우 -1 반환
}

// 회문 여부를 확인하는 함수
int is_palin(char* w) {
    QueueType deque;
    init(&deque);

    int i = 0;
    while (w[i] != '\0') {
        add_rear(&deque, w[i]); // 문자열을 덱에 추가
        i++;
    }
    i = 0;
    while (!is_empty(deque)) {
        if (w[i] != delete_rear(&deque)) { // 문자열의 처음과 끝을 비교하여 회문 여부 확인
            return 1; // 회문이 아닌 경우
        }
        i++;
    }
    return 0; // 회문인 경우
}

void main() {
    printf("반복할 횟수: ");
    int repeat;
    scanf("%d", &repeat);

    for (int i = 0; i < repeat; i++) {
        char w[MAX];

        printf("입력한 문장: ");
        scanf("%s", w);

        printf("%s is %s", w, (is_palin(w) == 0 ? "Palindrome\n" : "NOT palindrome\n"));
    }
}
