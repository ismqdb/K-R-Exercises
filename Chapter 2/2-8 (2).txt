#include <stdio.h>

unsigned wlen(unsigned x) {
    return (int)sizeof(x) * 8 / 2;
}

unsigned rightrot(unsigned x, int n) {
    unsigned len = wlen(x);
    unsigned lsb;
        
    for (int i = 0; i < n; i++) {
        lsb = x & 1;
        x >>= 1;
        lsb <<= len - 1;
        x |= lsb;
    }

    return x;
}

int main() {
    unsigned x = 0xF6A9;
    int n = 3;
    printf("%x\n", rightrot(x, n));
}

