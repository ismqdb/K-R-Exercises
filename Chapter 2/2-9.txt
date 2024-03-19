#include <stdio.h>

int bitcount(unsigned x) {
    int b;
    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}

int bitcount_f(unsigned x) {
    int b;
    for (b = 0; x != 0; x &= (x - 1), b++)
        ;
    return b;
}

int main() {
    unsigned x = 0b11010010;
    printf("%d\n", bitcount(x));
    printf("%d\n", bitcount_f(x));
}

