#include <stdio.h>

void strcat(char s[], char t[]) {
	int i, j;

	i = j = 0;

	while (s[i] != '\0')
		i++;

	while ((s[i++] = t[j++]) != '\0')
		;
}

void strcat_p(char* s, char* t) {
	int i = 0, j = 0;

	while (*(s + i) != '\0')
		i++;

	while ((*(s + i++) = *(t + j++)) != '\0')
		;
}

int main() {
	char s[] = "Marko ";
	char t[] = "Markovic";

	strcat_p(s, t);
	printf("%s", s);

	//strcat_p(s, t);
}