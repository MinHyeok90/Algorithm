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

int* getm(int i) {
	int j = midx;
	midx += i;
	return &memo[j];
}

void printRArrayp(int len, int* a) {
	for (int i = len - 1; i >= 0; --i) {
		printf("%d", a[i]);
	}
	printf("\n");
}

void nomalizep(int len, int* a) {
	for (int i = 0; i < len; ++i) {
		if (a[i] < 0) { //0보다 작을 때, 음수를 확인할때 사용하는거다 10이 아니라.
			int b = (-a[i] + 9) / 10;
			a[i + 1] -= b;
			a[i] += (b * 10);
		}
		else if (a[i] >= 10) {
			a[i + 1] += (a[i] / 10);
			a[i] %= 10;
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

void multip(int len, int* a, int* b, int* r) {
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			r[i + j] += a[j] * b[i];  //r[i + j] 는 계속 더해져야 하는 값이다. = 아니라 += 이다. //같은실수 2번째인데, multi 는 i+j만 +지, a, b는 곱셉이야...
		}
	}
}


void kara(int len, int* a, int* b, int* r) {
	if (len <= 50) {
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

	int* z2 = getm(rlen);
	int* z1 = getm(rlen);
	int* z0 = getm(rlen);
	int* a10 = getm(flen);
	int* b10 = getm(flen);

	kara(flen, a1, b1, z2);
	kara(blen, a0, b0, z0);

	addp(flen, a1, a10);
	addp(blen, a0, a10); //flen 과 blen을 햇갈리는건 너무했다...
	addp(flen, b1, b10);
	addp(blen, b0, b10);

	kara(flen, a10, b10, z1);
	subp(rlen, z1, z0);
	subp(rlen, z1, z2);

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
	printRArrayp(size*2, test100r);
	printf("- %d\n ", midx);
	printf("start = %d, end = %d, duraion= %d\n", start, end, end - start);
}
