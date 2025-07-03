#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

int iter(int n) {
	if (n == 0) return 0;
	else return n%10 + iter(n / 10);
}

void main() {
	printf("%d",iter(12345));
}