# Algorithm 공부용 자습페이지

## 메모리
- 2⁸= 1 Byte = 0 ~ 255 = char
- 2¹⁶ = 2 Byte = 65535 = short
- 2³² = 4 Byte = 약 21억 = int
- 2⁶⁴ = 8 Byte = 약 1천경 = long long

```
int a() {
  char str[1024*1024*1]; // 1MB
  char str[1048576]; // 약 100만 선언시 빵!
}
```

### 메모리 제한 사이즈별 한계
- 스택 사이즈 제한: 함수 내에서 선언할 수 있는 메모리 최대크기 = 1M
- 전역 혹은 힙메모리의 경우
  - 512MB = int 1.2억개 정도의 배열
  - 256MB = 약 6천만개 `int a[6000][10000] = {{0,},};`

### 메모리 할당
```
#include <malloc.h>

// int형 10개 필요시
int* p = (int*) malloc(sizeof(int)*10);
free(p)

//아래와 같이 사용시 순수 10byte만 할당. 실사용시 문제생김
int* p = (int*) malloc(10);
```