//arr가 일차원 정렬된 배열일 경우
int BSearchRecursive(int arr[], int target, int low, int high) {
    if (low > high)
        return -1;

    int mid = (low + high) / 2;
    if (arr[mid] == target)
        return mid;
    else if (arr[mid] > target)
        return BSearchRecursive(arr, target, low, mid-1);
    else
        return BSearchRecursive(arr, target, mid+1, high);
}

// arr가 BST로 구성된 경우
// 우선 BST를 구성하기 위해 add 함수를 만들든가 해야 함.
// BST는 1부터 시작해야 함
// 실제로 만들어보니, 빈 공간이 너무 많다... 최악의 경우 16번의 입력으로 65535의 배열이 터질수도 있다..
// 밸런스를 맞춘다면 쓸만할 지 모르겠으나, 그건 성능이 안나올 것 같음. 그냥 정렬 후 위 알고리즘 쓰는게..

int tree[100000];

void add(int i, int n) {
    if (i < 1) {
        printf("시작값은 1 보다 커야 함\n");
        return;
    }
    if (tree[i] == n) {
        printf("중복\n");
        return;
    }
    if (tree[i] == 0) {
        tree[i] = n;
        printf("값이 추가됨: tree[%d]:%d\n", i,n);
        return;
    }
    if (i * 2 > 100000) {
        printf("더 이상 추가할 수 없음: %d", i*2);
        return;
    }
    if (n < tree[i]) {
        add(i*2, n);
        return;
    }
    add(i*2 + 1, n);
}


int main()
{
    int a[8] = {1,2,7,4,3,4,9,0};
    for (int i=1; i<=8; i++) {
        add(1, a[i-1]);
    }
    for (int i=1; i<=20; i++) {
        printf("tree[%d]:%d\n", i, tree[i]);
    }
    return 0;
}
