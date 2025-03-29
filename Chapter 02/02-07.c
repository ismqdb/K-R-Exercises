// Online C compiler to run C program online
#include <stdio.h>

unsigned invert(unsigned x, int p, int n){
    unsigned y;
    y = ~0;
    y <<= n;
    y = ~y;
    y <<= (p-n+1);
    y ^= x;
    return y;
}

int main() {
    unsigned x = 0x1FA9;
    int p = 7;
    int n = 2;
    
    printf("%d\n", invert(x, p, n));
    
    return 0;
}