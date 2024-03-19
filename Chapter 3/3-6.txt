#include <stdio.h>

void reverse(char s[]) {
	int size = 0;

	for (; s[size] != '\0'; size++)
		;

	for (int i = 0; s[i] != '\0'; i++)
		printf("%c", s[size - i - 1]);

}

void itob(int n, char s[], int b, unsigned width) {
	// 0-9, A=10, B=11, Z = 26
	if (b > 26) {
		printf("Number base can't be higher than 36.\n");
		return;
	}

	int i = 0;
	int digit;

	do {
		int digit = n % b;
		if (digit < 10)
			s[i] = (char)(digit + '0');
		else
			s[i] = (char)(digit + 'A' - 10);
		i++;
	} while ((n /= b) != 0);

	for (int k = i; k < width; k++)
		s[i++] = 32;

	s[i++] = '\0';

	reverse(s);
}

int main() {
	int n = 230;
	int b = 16;
	char s[50];
	unsigned fieldWidth = 8;

	itob(n, s, b, fieldWidth);
}