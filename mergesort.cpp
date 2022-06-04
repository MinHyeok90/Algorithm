#include <iostream>

using namespace std;

//병합 알고리즘
// i = 첫째 배열 시작점
// j = 둘째 배열 시작점
// k = 머지소트에서 임시로 생성한 배열의 인덱스
// p는 첫 배열 시작점
// q는 첫 배열 끝점
// r은 지금 정렬하려는 배열 범위의 끝점
// 원본 배열의 index를 사용한다.
void merge(int data[], int p, int q, int r){
    int t[10] = {0,};
    int i = p, j=q+1, k=p;
    while (i<=q && j<=r) {
        if (data[i] <= data[j]) {
            t[k++] = data[i++];
        } else {
            t[k++] = data[j++];
        }
    }
    while(i<=q) {
        t[k++] = data[i++];
    }
    while(j<=r) {
        t[k++] = data[j++];
    }
    for(int a=p;a<=r;a++) data[a]=t[a]; //<= 임을 주의
}

// 분할 알고리즘
// 원본 배열을 그대로 사용하면서, merge 하는 순간에만 메모리를 쓰는 방식.
// ms는 0, 7 을 받으면 0번째부터 7번째 인덱스를 포함한 배열을 정렬한다.
// 인텍스 계산시 0부터 계산하는게 아닌, 원본 배열의 idx를 직접 사용한다.
// p는 첫째 배열 시작점
// q는 첫째 배열 끝점 (이 알고리즘은 끝점을 포함해야 한다)
    // 두번째 배열은 q+1부터 시작한다
// r은 배열의 마지막 인덱스(값을 포함한 끝)
void ms(int data[], int p, int r){ 
    int q;
    // 1개짜리는 p==r 이다. 따라서 p < r 조건덕분에 말단 배열 1개짜리는 넘어간다. 
    if (p < r) {
        q = (p+r)/2; //p는 언제나 r보다 작으며 /2로 나누므로 절대 r을 넘어가지 않는다. (1/2==0)
        ms(data,p ,q);
        ms(data,q+1,r);
        merge(data, p, q, r); //q를 날리는 이유는 p~q까지의 첫번째 배열범위를 알기 위해서이다. 두번째 배열은 q+1부터~r까지임을 알 수 있다
    }
}

int main()
{
    int a[5] = {1,2,7,4,3};
    ms(a, 0, 4);
    for(int i=0; i<5; i++) printf("%d ", a[i]);
    return 0;
}
