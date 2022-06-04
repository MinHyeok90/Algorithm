#include <stdlib.h>

// -----------------------------------------Case`) 자체 알고리즘. 빠르나 안전성 보장은 안된다.
int memo[10000000] = { 0, };
int mi = 0;

int* gm(int i) {
  if (mi + i > 10000000){
    mi = 0;
  }
	int j = mi;
	mi += i;
	return &memo[j];
}

// ----------------------------------------Case2) malloc.h  #include <stdlib.h>  안에 있다.
int main()
{
    int *numPtr2;     // int형 포인터 선언
    numPtr2 = (int*) malloc(sizeof(int) * 5);    // int의 크기 4바이트만큼 동적 메모리 할당 //인트포인터 엠얼록 사이즈오브 인트 곱 N
    printf("%p\n", numPtr2);     // 009659F0: 새로 할당된 메모리의 주소 출력
                                // 컴퓨터마다, 실행할 때마다 달라짐
    free(numPtr2);    // 동적으로 할당한 메모리 해제
    return 0;
}

