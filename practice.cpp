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

int* getMemo(int i) {
	int j = midx;
	midx += (i + 2); // + 1 은 carry, +1은 flen *2 의 패딩
	return &memo[j];
}

void printRArray2(int len, int* a) {
	for (int i = len - 1; i >= 0; --i) {
		printf("%d", a[i]);
	}
	printf("\n");
}

void nomalize2(int len, int* r) {
	for (int i = 0; i < len; ++i) {
		if (r[i] < 0) {
			int b = (-r[i] + 9) / 10;
			r[i + 1] -= b;
			r[i] += (b * 10);
		}
		else if (r[i] >= 10) {
			r[i + 1] += (r[i] / 10);
			r[i] = (r[i] % 10);
		}
	}
}

void add2(int len, int* a, int* r) {
	for (int i = 0; i < len; ++i) {
		r[i] += a[i];
	}
}

void subtract2(int len, int* a, int* b, int* r) {
	for (int i = 0; i < len; ++i) {
		r[i] = a[i] - b[i];
	}
}

void multi2(int len, int* a, int* b, int* r) {
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			r[i + j] += (a[j] * b[i]);
		}
	}
}


void kara(int len, int* a, int* b, int* r) {

	if (len <= 50) {
		multi2(len, a, b, r);
		return;
	}

	int jari = len / 2;
	int flen = len / 2 + (len % 2); //len 이 아닌   jari 를 더하는 실수.
	// int blen = len / 2;  //blen과 flen을 구분하지 않고 flen으로만 계산해도 가능하다.

	int* a1 = a + jari;
	int* a0 = a;
	int* b1 = b + jari;
	int* b0 = b;

	int* z2 = getMemo(flen * 2);
	//int z2[100] = { 0, };
	kara(flen, a1, b1, z2);

	int* z0 = getMemo(flen * 2);
	kara(flen, a0, b0, z0);
	
	int* z1 = getMemo(flen * 2);
	int* a0a1 = getMemo(flen * 2);
	int* b0b1 = getMemo(flen * 2);
	add2(flen, a1, a0a1);
	add2(flen, a0, a0a1); // 여긴 blan 이여야만 할 것 같다
	add2(flen, b1, b0b1);
	add2(flen, b0, b0b1);

	kara(flen, a0a1, b0b1, z1);

	//len이 틀렸었다.
	subtract2(flen * 2, z1, z0, z1);
	subtract2(flen * 2, z1, z2, z1);

	//복붙을 하다보니 z2, z1, z0 를 변경해주지 않았었다.
	add2(flen * 2, z2, r + (jari * 2));
	add2(flen * 2, z1, r + (jari));
	add2(flen * 2, z0, r);
}

//int main() {
//	clock_t start, end;
//
//	printf("1234 * 5678 = %d\n", 1234 * 5678);
//	printf("12345 * 67891 = %d\n", 12345 * 67891);
//	int size = 15000;
//	//for (int i = 0; i < size; ++i) {
//	//	test100a[i] = 5;
//	//	test100b[i] = 6;
//	//}
//	//test100a[0] = 4;
//	//test100a[1] = 3;
//	//test100a[2] = 2;
//	//test100a[3] = 1;
//	//test100b[0] = 8;
//	//test100b[1] = 7;
//	//test100b[2] = 6;
//	//test100b[3] = 5;
//	//multi2(size, test100a, test100b, test100r);
//	//nomalize2(size * 2, test100r);
//	//printRArray2(size * 2, test100r);
//
//	int test100a[15000] = { 0, };
//	int test100b[15000] = { 0, };
//	int test100r[30000] = { 0, };
//	for (int i = 0; i < size; ++i) {
//		test100a[i] = 5;
//		test100b[i] = 6;
//	}
//	start = clock();
//	kara(size, test100a, test100b, test100r);
//	nomalize2(size*2, test100r);
//	end = clock();
//	printRArray2(size*2, test100r);
//	printf("- %d\n ", midx);
//	printf("start = %d, end = %d, duraion= %d\n", start, end, end - start);
//}
