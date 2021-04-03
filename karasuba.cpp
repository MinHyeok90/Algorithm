#include <stdio.h>

//long long -> –9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807  -> 사실상 18자리까지만 사용
//unsigned long long -> 0 ~ 18,446,744,073,709,551,615 -> 18자리 20번째자리는 1밖에 못쓰며, 19번째 자리는 2의 배수가 아니므로 사용하기 애매

int ma[10] = { 4, 3, 2, 1, 0, }; //123
int mb[10] = { 8 ,7, 6, 5, 0, }; //456
int mr[10] = { 0, };

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
		*r *= 10;
		*r += a[i];
	}
}

void nomalize(int len, int* r) {
	for (int i = 0; i < len; ++i) {
		if (r[i] < 0) {
			int b = ((r[i] < 0 ? -r[i] : r[i]) + 9) / 10;
			r[i + 1] -= b;
			r[i] += (b * 10);  //r[i] is minus
		}
		else if (r[i] >= 10) {
			r[i + 1] += (r[i] / 10);
			r[i] = (r[i] % 10);
		}
	}
}

void add(int lena, int lenb, int* a, int* b, int *r) {
	//r에는 이미 더해진 값이 있다고 가정
	for (int i = 0; i < lena; ++i) {
		r[i] += a[i];
	}
	for (int i = 0; i < lenb; ++i) {
		r[i] += b[i];
	}
	//add 는 nomalize를 포함하는 경우, n+1의 결과를 return할 수 있다.
	//nomalize((lena > lenb ? lena : lenb) + 1, r);
}

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
	if (len <= 4) {
		simpleMul(len, a, b, r);
		return;
	}
	int div = len / 2; //div가 자릿수다
	int d = sizeof(int*); //delta
	int flen = len / 2 + (len % 2); //front len -> 3 or 2 //len of 1 (a1, b1)
	int blen = len / 2; //back len //len of 0 (a0, b0)

	//add 는 n+1의 결과를 return할 수 있다.
	int* a1 = div + a;
	int* b1 = div + b;
	int* a0 = a;
	int* b0 = b;

	//분할
	//1.앞부분 카라츠바
	int z2[100] = { 0, };
	karasuba(flen, a1, b1, z2); //z2 는 flen의 2배 길이일 수 있다.

	//2.뒷부분 카라츠바
 	int z0[100] = { 0, };
	karasuba(blen, a0, b0, z0); //z0 는 blen의 2배 길이일 수 있다.
	
	//3.중간값 카라츠바
	int z1[100] = { 0, };
	int a0a1[100] = { 0, };
	int b0b1[100] = { 0, };
	add(blen, flen, a0, a1, a0a1);
	add(blen, flen, b0, b1, b0b1);
	karasuba(flen, a0a1, b0b1, z1); //길 수 있는 값 기준. //z1은 flen의 2배 길이일 수 있다.

	//4.중간값 역산
	subtract(len, z1, z0, z1);
	subtract(len, z1, z2, z1);
	//nomalize(flen * 2, z1);

	//5.합산!
	add(flen * 2, 0, z2, r + (div * 2), r + (div * 2)); //z2는 높은 자리수 2개를 곱한거니 2번 올라간다.
	add(flen * 2, 0, z1, r + (div), r + (div));			//z1은 높은 자리수 1개씩 곱한거니 1번 올라간다. //2차다항식의 중간값.
	add(blen * 2, 0, z0, r, r);							//z0는 그자리다.
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
