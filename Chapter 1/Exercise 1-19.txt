#include <stdio.h>
#define MAXLINE 1000

int getline(int line[], int maxline);
void reverse(int input[], int lineLength);

main() {
	int len;
	int line[MAXLINE];

	while ((len = getline(line, MAXLINE)) > 0)
		reverse(line, len);

	return 0;
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

void reverse(int input[], int lineLength) {
	int i;

	for (i = lineLength - 1; i >= 0; i--)
		putchar(input[i]);
}
