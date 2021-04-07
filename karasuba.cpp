#include <stdio.h>
#include <time.h>

//long long -> –9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807  -> 사실상 18자리까지만 사용
//unsigned long long -> 0 ~ 18,446,744,073,709,551,615 -> 18자리 20번째자리는 1밖에 못쓰며, 19번째 자리는 2의 배수가 아니므로 사용하기 애매

//log_10(32) / log_10(2) == 5

//스택영역, 지역변수 // 쓰지말자.
//char 배열 최대 크기 : 약 1,000,000 (백만)    : 문제에서 최대 범위가 백만까지 주어질 경우 사용 가능
//int  배열 최대 크기 : 약   250,000 (이십오만): 문제에서 최대 범위가 이십오만까지 주어질 경우 사용 가능

//전역공간에서 256mb 한정시 사용할 수 있는 최대 int배열은?
//int [256] -> 1kb
//int [256 * 1024 = 262,144] 1Mb
//int [256 * 1024 * 256 = 67,108,864] 6천만짜리 배열
//__int32 -> 4byte 

//int m[ n * (log(n) + 1) ]
// n == 8 -> 8 + 4*2 + 2*4 + 1*8 == 8*4 
// n == 15000 -> 15000 * 14 + @ // 계산에 필요한 핵심공간 + 계산에 필요한 부수적 공간
// 15000 * 14 = 210,000

// 카라츠바에서의 계산: 15000 -> (7500 * 3) + (7500 * 2) == 7500 * 5 ...
// n / 2 * 3 + (n) -> 5/2 n 추가필요 -> n이 1 혹은 base line이 될 때까지

// 계산할바에 그냥 크게 잡고 시작하는 게 좋은 방법같다.
// 천만짜리 배열을 잡고 시작하자. 알고리즘 완성 후 줄이는건 천천히 해도 될 듯.

// 연구 기록
/*
	base	duration	memory
	15000	1289		0
	10000	1011		60005
	7500	950			60005
	5000	774			150020
	3000	567			285065
	2000	607			285065
	1000	454			487754
	500		387			792017
	250		277			1249424
	100		195			2978558
*	50		164			4564943 <- 대체적인 최적값으로 보인다. //이 근처로 다른 값들을 시도해 볼 수는 있겠으나, 큰 의미는 없을 것으로 보인다.
	25		183			7006904
	10		303			10907945
*/
int base = 50;
int ma[10] = { 4, 3, 2, 1, 0, }; //123
int mb[10] = { 8 ,7, 6, 5, 0, }; //456
int mr[10] = { 0, };

int memory[10000000] = { 0, };
int mIdx = 0;

int* getMemory(int i) {
	int j = mIdx;
	mIdx += (i + 2); //flen * 2 는 2자리를 먹을 수 있다.
	return &memory[j];
}

void printRArray(int len, int* a) {
	for (int i = len-1; i >= 0; --i) {
		printf("%d", a[i]);
	}
	printf("\n");
}

void mStrcpy(int len, int* s, int* d) {
	for (int i = 0; i < len; ++i) {
		d[i] = s[i];
	}
}

void ntoa(int len, int n, int* r) {
	//100 -> [0],[0],[1]
	//r은 초기화가 되어 있다고 가정.
	for (int i = 0; i < len; ++i) {
		r[i] = n % 10;
		n /= 10;
	}
}

void aton(int len, int *a, int* r) {
	//[0],[0],[1] -> 100
	*r = 0;
	for (int i = len - 1; i >= 0 ; --i) {
		*r *= 10; //1의 자리수는 0 * 10 = 0;
		*r += a[i];
	}
}

void nomalize(int len, int* r) {
	for (int i = 0; i < len; ++i) {
		if (r[i] < 0) {
			int b = (-r[i] + 9) / 10;
			r[i + 1] -= b;
			r[i] += (b * 10);  //r[i] is minus
		}
		else if (r[i] >= 10) {
			r[i + 1] += (r[i] / 10);
			r[i] = (r[i] % 10);
		}
	}
}

//it should be a >= b
void addTwo(int lena, int lenb, int* a, int *b, int* r) { //O(2N) 으로 할 것이냐, O(N)으로 할 것이냐..
	//r에는 이미 더해진 값이 있다고 가정
	for (int i = 0; i < lena; ++i) {
		r[i] += a[i];
		if (i < lenb) {
			r[i] += b[i];
		}
	}
	//nomalize를 안하면 r의 len까지만 계산한다.
	//nomalize((lena > lenb ? lena : lenb) + 1, r); 
}

void add(int len, int* a, int *r) { //O(2N) 으로 할 것이냐, O(N)으로 할 것이냐..
	//r에는 이미 더해진 값이 있다고 가정
	for (int i = 0; i < len; ++i) {
		r[i] += a[i];
	}
	//nomalize를 안하면 r의 len까지만 계산한다.
	//nomalize((lena > lenb ? lena : lenb) + 1, r); 
}

//it should be a >= b
void subtract(int len, int* a, int* b, int* r) {
	for (int i = 0; i < len; ++i) {
		r[i] = a[i] - b[i];
	}
}


void simpleMul(int len, int* a, int* b, int* r) { 
	for (int i = 0; i < len; ++i) { //b
		for (int j = 0; j < len; ++j) { //a
			r[i + j] += (a[j] * b[i]);
		}
	}
	//nomalize(len + 1, r);
}

void karasuba(int len, int* a, int* b, int* r) {
	//input으로 최대길이 len 짜리 a, b를 받으면
	//output으로 len*2짜리 r을 반환하는 함수
	if (len <= base) {
		simpleMul(len, a, b, r);
		return;
	}
	int jari = len / 2; //시작점을 구분하는 상수값. 매우 크다.
	int fLen = len / 2 + (len % 2); //front len -> 3 or 2 //len of 1 (a1, b1)
	int bLen = len / 2; //불필요. //back len //len of 0 (a0, b0)

	//a = (a1 * div) + a0
	int* a1 = a + jari;
	int* a0 = a;
	int* b1 = b + jari;
	int* b0 = b;

	//분할
	//1.앞부분 카라츠바
	//int z2[100] = { 0, }; //테스트 시에는 배열로 해야 디버깅이 편하다.
	int* z2 = getMemory(fLen * 2);
	karasuba(fLen, a1, b1, z2); //z2 는 fLen의 2배 길이일 수 있다.

	//2.뒷부분 카라츠바
 	//int z0[100] = { 0, };
	int* z0 = getMemory(bLen * 2);
	karasuba(bLen, a0, b0, z0); //z0 는 bLen의 2배 길이일 수 있다.
	
	//3.중간값 카라츠바
	int* z1 = getMemory(fLen * 2);
	int* a0a1 = getMemory(fLen);
	int* b0b1 = getMemory(fLen);
	addTwo(fLen, bLen, a1, a0, a0a1);
	addTwo(fLen, bLen, b1, b0, b0b1);
	karasuba(fLen, a0a1, b0b1, z1); //길 수 있는 값 기준. //z1은 fLen의 2배 길이일 수 있다.

	//4.중간값 역산
	subtract(fLen * 2, z1, z0, z1);
	subtract(fLen * 2, z1, z2, z1);

	//5.합산!
	add(fLen * 2, z2, r + (jari * 2));	//z2는 높은 자리수 2개를 곱한거니 2번 올라간다.
	add(fLen * 2, z1, r + (jari));		//z1은 높은 자리수 1개씩 곱한거니 1번 올라간다. //2차다항식의 중간값.
	add(bLen * 2, z0, r);				//z0는 그자리다.
	//nomalize(len, r);
}

int main() {
	clock_t start, end;

	printf("1234 * 5678 = %d\n", 1234 * 5678);
	printf("12345 * 67891 = %d\n", 12345 * 67891);
	karasuba(5, ma, mb, mr);
	nomalize(10, mr);
	printRArray(10, mr);

	int test5a[5] = { 5, 4, 3, 2, 1 };
	int test5b[5] = { 1, 9, 8 ,7, 6 };
	int testr[10] = { 0, };
	karasuba(5, test5a, test5b, testr);
	nomalize(10, testr);
	printRArray(10, testr);

	int test100a[15000] = { 0, };
	int test100b[15000] = { 0, };
	int test100r[30000] = { 0, };
	for (int i = 0; i < 15000; ++i) {
		test100a[i] = 5;
		test100b[i] = 6;
	}
	start = clock();
	karasuba(15000, test100a, test100b, test100r);
	nomalize(30000, test100r);
	end = clock();
	printRArray(30000, test100r);
	printf("- %d\n ", mIdx);
	printf("start = %d, end = %d, duraion= %d\n", start, end, end - start);
}
