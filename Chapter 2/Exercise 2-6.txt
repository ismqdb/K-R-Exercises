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

int main() {
	unsigned x = 0xF6A9;
	int p = 7;
	int n = 3;
	unsigned y = 0xA2;
	printf("%X\n", setbits(x, p, n, y));   // EXPECTS 0XF649
}

