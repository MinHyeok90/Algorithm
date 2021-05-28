/*
	이 파일은 10분 코딩을 연습하는 공간입니다.
*/
#include <stdio.h>
#include <time.h>

int test100a[15000] = { 0, };
int test100b[15000] = { 0, };
int test100r[30000] = { 0, };

int memo[10000000] = { 0, };
int midx = 0;

int* gm(int i) {
	int j = midx;
	midx += i;
	return &memo[j];
}

void printRA(int len, int* r) {
	for (int i = len - 1; i >= 0; --i) {
		printf("%d", r[i]);
	}
	printf("\n");
}

void nomalizep(int len, int* r) {
	for (int i = 0; i < len; ++i) {
		if (r[i] < 0) {
			int b = (-r[i] + 9) / 10;
			r[i + 1] -= b;
			r[i] += b * 10;
		}
		else if (r[i] >= 10) {
			r[i + 1] += r[i] / 10;
			r[i] %= 10;
		}
	}
}

void addp(int len, int* a, int* r) {
	for (int i = 0; i < len; ++i) {
		r[i] += a[i];
	}
}

void subp(int len, int* a, int* b) {
	for (int i = 0; i < len; ++i) {
		a[i] -= b[i];
	}
}

void multip(int len, int* a, int* b, int *r) {
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			r[i + j] += a[j] * b[i];
		}
	}
}

void kara(int len, int* a, int* b, int* r) {
	if (len < 50) {
		return multip(len, a, b, r);
	}

	int div = len / 2;
	int flen = div + len % 2;
	int blen = div;
	int rlen = flen * 2;

	int* a1 = a + div;
	int* a0 = a;
	int* b1 = b + div;
	int* b0 = b;

	int* a10 = gm(flen);
	int* b10 = gm(flen);
	int* z2 = gm(rlen);
	int* z1 = gm(rlen);
	int* z0 = gm(rlen);

	kara(flen, a1, b1, z2);
	kara(blen, a0, b0, z0);

	addp(flen, a1, a10);
	addp(blen, a0, a10);
	addp(flen, b1, b10);
	addp(blen, b0, b10);
	kara(flen, a10, b10, z1);
	subp(rlen, z1, z2);
	subp(rlen, z1, z0);

	addp(rlen, z2, r + div * 2);
	addp(rlen, z1, r + div);
	addp(blen * 2, z0, r);
}

int main() {
	clock_t start, end;

	printf("1234 * 5678 = %d\n", 1234 * 5678);
	printf("12345 * 67891 = %d\n", 12345 * 67891);
	int size = 15000;

	//for (int i = 0; i < size; ++i) {
	//	test100a[i] = 5;
	//	test100b[i] = 6;
	//}
	//multip(size, test100a, test100b, test100r); 
	//nomalizep(size * 2, test100r);
	//printRArrayp(size * 2, test100r);

	for (int i = 0; i < size; ++i) {
		test100a[i] = 5;
		test100b[i] = 6;
	}
	start = clock();
	kara(size, test100a, test100b, test100r);
	nomalizep(size*2, test100r);
	end = clock();
	printRA(size*2, test100r);
	printf("midx: %d\n ", midx);
	printf("start = %d, end = %d, duraion= %d\n", start, end, end - start);
}
