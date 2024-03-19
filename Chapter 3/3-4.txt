#include <stdio.h>
#include <math.h>

void reverse(char s[]) {
	int size = 0;

	for (; s[size] != '\0'; size++)
		;

	for (int i = 0; s[i] != '\0'; i++)
		printf("%c", s[size - i - 1]);

}

void itoa(int n, char s[]) {
	int i, sign;

	signed int maxNeg = (-pow(2, sizeof(n) * 8 - 1));

	if ((sign = n) < 0)
		if (n == maxNeg)
			n = -(n + 1);
		else
			n = -n;
	i = 0;

	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	if (sign == maxNeg) {
		int f = abs(maxNeg % 10);
		s[0] = (char)f + '0';
	}

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';

	reverse(s);
}

int main() {
	signed int x = -pow(2, sizeof(signed int) * 8 - 1);

	char s[50];
	itoa(x, s);
}