#include<stdio.h>

int p = 127, mod = 1610612741;
int hash(char c[]) {
    long long ans = 0;
    for (int i = 0; c[i]; i++) ans = (p * ans + c[i]) % mod;
    return ans;
}
