#include <stdio.h>

int strend(char* s, char* t) {
	int i = 0, j = 0;

	while (*(s + i) != *t)
		if (*(s + i) == '\0')
			return 0;
		else
			i++;

	while (*(t + j) != '\0') {
		if (*(s + i) != *(t + j))
			return 0;
		i++;
		j++;
	}

	return 1;
}

int main() {
	char s[] = "Marko \0";
	char t[] = "ko \0";
	char x[] = "po";

	char a[] = "Markovic\0";
	char b[] = "ic\0";

	printf("%d\n", strend(s, t));
	printf("%d\n", strend(s, x));
	printf("%d\n", strend(a, b));
}