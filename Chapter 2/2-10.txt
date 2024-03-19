#include <stdio.h>

void tolower(char c[]) {
    for (int i = 0; c[i] != '\0'; i++)
        printf("%c", (c[i] > 64 && c[i] < 91) ? c[i] + 32 : c[i]);
}

int main() {
    char string[] = "MarKo MaRKovic\0";
    tolower(string);
}

