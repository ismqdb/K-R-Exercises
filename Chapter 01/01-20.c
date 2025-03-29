#include <stdio.h>

#define MAXLINE 1000

void detab(int input[], int length);
int getline(int s[], int lim);

int main() {
	int len;
	int line[MAXLINE];

	while ((len = getline(line, MAXLINE)) > 0)
		detab(line, len);

	return 0;
}

void detab(int input[], int length) {
	int charsAlready = 0;

	for (int i = 0; i < length; ++i) {
		if (charsAlready == 8)
			charsAlready = 0;

		if (input[i] != '\t') {
			charsAlready++;
			putchar(input[i]);
		}
		else {
			for (int j = 0; j < 8 - charsAlready; ++j)
				putchar(' ');
			charsAlready = 0;
		}
	}
}

int getline(int s[], int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';
	return i;
}