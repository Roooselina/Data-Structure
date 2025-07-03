#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int sum_iter(int n) {
	int sum = 0;

	do {
		int num;
		num = n % 10;
		sum += num;

		n /= 10;

	} while (n != 0);

	return sum;
}


int sum_rec(int n) {

	if (n < 10) {
		return n;
	}

	int last_digit = n % 10;

	return last_digit + sum_rec(n/10);
}

void main() {
	int num;
	for (int i = 0; i < 3; i++) {
		printf("���� �Է��� �ֽʽÿ�: ");
		scanf("%d", &num);
		printf("���: %d\n", sum_rec(num));
		printf("��ȯ: %d\n", sum_iter(num));
	}

}
