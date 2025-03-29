#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int htoi(char str[]) {
	int sum = 0;
	int num = 0;
	int strLen = strlen(str);

	for (int i = 2; str[i] != '\0'; i++) {
		if (isdigit(str[i]))
			num = str[i] - '0';
		else
			switch (str[i]) {
				case 'a':
				case 'A':
					num = 10;
					break;
				case 'b':
				case 'B':
					num = 11;
					break;
				case 'c':
				case 'C':
					num = 12;
					break;
				case 'd':
				case 'D':
					num = 13;
					break;
				case 'e':
				case 'E':
					num = 14;
					break;
				case 'f':
				case 'F':
					num = 15;
					break;
			}

		sum += pow(16, strLen - 1 - i) * num;
	}

	return sum;
}

int main() {
	char s[20] = "0x000F\0";
	printf("%s = %d", s, htoi(s));
}