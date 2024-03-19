#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[]) {
	int i;
	i = strlen(s) - 1;

	if (i >= 0) {
		printf("%c", s[i]);
		s[i--] = '\0';
		reverse(s);
	}
}

void itoa_r(int n, char s[]) {
	static int i = 0, sign;

	if ((sign = n) < 0)
		n = -n;

	if (n > 0) {
		s[i++] = n % 10 + '0';
		n /= 10;
		itoa_r(n, s);
	}

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';
}

int main() {
	int x = 253;
	char s[10];

	itoa_r(x, s);	
	reverse(s);
}