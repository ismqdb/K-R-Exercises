#include <stdio.h>

int main() {
	int i;
	int lim = 1000;

	char c;
	char s[100];

	for (i = 0; i < lim - 1, (c = getchar()) != '\n', c != EOF; ++i) 
		s[i] = c;
}