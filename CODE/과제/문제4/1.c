#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fun_1(int n) {
    int i, sum = 0;
    long long count = 1;
    for (i = 1; i <= n; i++) {
        sum += 1;
        count += 2;
    }
    printf("%lld\n", count);
    return sum;
}

int main() {
    clock_t start_time, end_time;
    double elapsed_time;

    start_time = clock();
    printf("%lld", fun_1(2500));
    end_time = clock();

    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n실행 시간: %f 초", elapsed_time);

    return 0;
}
