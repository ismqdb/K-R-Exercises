#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    int shift = p-n+1;

    unsigned mask;
    mask = ~0;
    mask <<= n;
    mask = ~mask;
    mask &= y;
    mask <<= shift;

    unsigned bitClear = ~0;
    bitClear <<= n;
    bitClear = ~bitClear;
    bitClear <<= shift;
    bitClear = ~bitClear;

    x &= bitClear;
    x |= mask;

    return x;
}

unsigned wlen(unsigned x){
    return (int)sizeof(x) * 8 / 2;
}

unsigned rightrot(unsigned x, int n){
    unsigned copy = x;
    unsigned len = wlen(x);

    x >>= n;
    return setbits(x, len-1, n, copy);
}

int main() {
	unsigned x = 0xF6A9;
	int n = 3;
    printf("%x\n", rightrot(x, n));
    //printf("%d\n", wlen(0xF));
}

