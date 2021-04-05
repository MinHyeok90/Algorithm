#include <stdio.h>

//long long -> –9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807  -> 사실상 18자리까지만 사용
//unsigned long long -> 0 ~ 18,446,744,073,709,551,615 -> 18자리 20번째자리는 1밖에 못쓰며, 19번째 자리는 2의 배수가 아니므로 사용하기 애매

//log_10(32) / log_10(2) == 5

//스택영역, 지역변수에서 
//char 배열 최대 크기 : 약 1,000,000 (백만)    : 문제에서 최대 범위가 백만까지 주어질 경우 사용 가능
//int  배열 최대 크기 : 약   250,000 (이십오만): 문제에서 최대 범위가 이십오만까지 주어질 경우 사용 가능

//전역공간에서 256mb 한정시 사용할 수 있는 최대 int배열은?
//int [256] -> 1kb
//int [256 * 1024 = 262,144] 1Mb
//int [256 * 1024 * 256 = 67,108,864] 6천만짜리 배열

int memory[1000000000] = { 0, };

//int m[ n * (log(n) + 1) ]
// n == 8 -> 8 + 4*2 + 2*4 + 1*8 == 8*4 
// n == 15000 -> 15000 * 14 + @ // 계산에 필요한 핵심공간 + 계산에 필요한 부수적 공간
// 15000 * 14 = 210,000

// 카라츠바에서의 계산: 15000 -> (7500 * 3) + (7500 * 2) == 7500 * 5 ...
// n / 2 * 3 + (n) -> 5/2 n 추가필요 -> n이 1 혹은 base line이 될 때까지

//계산할바에 그냥 크게 잡고 시작하는것도 방법일듯.. 이분탐색을 손으로 해도 14번정도면 될껀데 ㅋㅋㅋㅋ

int ma[10] = { 4, 3, 2, 1, 0, }; //123
int mb[10] = { 8 ,7, 6, 5, 0, }; //456
int mr[10] = { 0, };
// 15000 + 7500*5 + 3750 * 5 + 1875 * 5 + 938 * 5


//int memory[10000000] = { 0, };
//
//int mIdx = 0;
//int* getMemory(int i) {
//	return &memory[mIdx];
//}

//__int32 -> 4byte 

struct MyArray
{
	int* a;
	int size;
};

void printArray(int len, int* a) {
	for (int i = 0; i < len; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

void printRArray(int len, int* a) {
	for (int i = len-1; i >= 0; --i) {
		printf("%d", a[i]);
	}
	printf("\n");
}

void printMyArray(MyArray m) {
	for (int i = 0; i < m.size; ++i) {
		printf("%d", m.a[i]);
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
void addON(int lena, int lenb, int* a, int *b, int* r) { //O(2N) 으로 할 것이냐, O(N)으로 할 것이냐..
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
	//input으로 최대길이 len 짜리 a, b를 받고
	//output으로 len*2짜리 r을 반환하는 함수
	if (len <= 4) {
		simpleMul(len, a, b, r);
		return;
	}
	int div = len / 2; //div가 자릿수다
	int fLen = len / 2 + (len % 2); //front len -> 3 or 2 //len of 1 (a1, b1)
	int bLen = len / 2; //back len //len of 0 (a0, b0)

	//add 는 n+1의 결과를 return할 수 있다.
	int* a1 = div + a;
	int* b1 = div + b;
	int* a0 = a;
	int* b0 = b;

	//분할
	//1.앞부분 카라츠바
	int z2[100] = { 0, }; //테스트 시에는 배열로 해야 디버깅이 편하다.
	//int* z2 = getMemory(fLen * 2);
	karasuba(fLen, a1, b1, z2); //z2 는 fLen의 2배 길이일 수 있다.

	//2.뒷부분 카라츠바
 	int z0[100] = { 0, };
	//int* z0 = getMemory(bLen * 2);
	karasuba(bLen, a0, b0, z0); //z0 는 bLen의 2배 길이일 수 있다.
	
	//3.중간값 카라츠바
	int z1[100] = { 0, };
	int a0a1[100] = { 0, };
	int b0b1[100] = { 0, };
	//int* z1 = getMemory(fLen * 2);
	//int* a0a1 = getMemory(fLen);
	//int* b0b1 = getMemory(fLen);
	add(bLen, a0, a0a1);
	add(fLen, a1, a0a1);
	add(bLen, b0, b0b1);
	add(fLen, b1, b0b1);
	karasuba(fLen, a0a1, b0b1, z1); //길 수 있는 값 기준. //z1은 fLen의 2배 길이일 수 있다.

	//4.중간값 역산
	subtract(len, z1, z0, z1);
	subtract(len, z1, z2, z1);

	//5.합산!
	add(fLen * 2, z2, r + (div * 2));	//z2는 높은 자리수 2개를 곱한거니 2번 올라간다.
	add(fLen * 2, z1, r + (div));		//z1은 높은 자리수 1개씩 곱한거니 1번 올라간다. //2차다항식의 중간값.
	add(bLen * 2, z0, r);				//z0는 그자리다.
	nomalize(len, r);
}

int main() {
	printf("1234 * 5678 = %d\n", 1234 * 5678);
	printf("12345 * 67891 = %d\n", 12345 * 67891);
	karasuba(5, ma, mb, mr);
	nomalize(10, mr);
	printRArray(10, mr);

	int test5a[5] = { 5, 4, 3, 2, 1 }; //123
	int test5b[5] = { 1, 9, 8 ,7, 6 }; //456
	int testr[10] = { 0, };
	karasuba(5, test5a, test5b, testr);
	nomalize(10, testr);
	printRArray(10, testr);
}
