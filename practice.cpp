/*
	�� ������ 10�� �ڵ��� �����ϴ� �����Դϴ�.
*/
#include <stdio.h>
#include <time.h>

int test100a[15000] = { 0, };
int test100b[15000] = { 0, };
int test100r[30000] = { 0, };


int main() {
	clock_t start, end;

	for (int i = 0; i < 15000; ++i) {
		test100a[i] = 5;
		test100b[i] = 6;
	}
	start = clock();

	end = clock();
	printf("start = %d, end = %d, duraion= %d\n", start, end, end - start);
}
