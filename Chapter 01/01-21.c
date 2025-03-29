#include <stdio.h>

#define MAXLINE 1000

void entab(int input[], int length);
int getline(int s[], int lim);

int main() {
	int len;
	int line[MAXLINE];

	while ((len = getline(line, MAXLINE)) > 0)
		entab(line, len);

	return 0;
}

void entab(int input[], int length) {
	int charsAlready = 0;
	int blanksAlready = 0;
	int isLastCharBlank = 0;

	for (int i = 0; i < length; ++i) {
		if (charsAlready == 8) {
			if (blanksAlready > 1)
				putchar('\t');

			charsAlready = 0;
			blanksAlready = 0;
		}

		if (input[i] != ' ') {
			if (isLastCharBlank == 1)
				for (int j = 0; j < blanksAlready; ++j)
					putchar(' ');

			putchar(input[i]);
			charsAlready++;

			if (input[i] == '\t')
				charsAlready = 0;

			isLastCharBlank = 0;
			blanksAlready = 0;
		}
		else {
			if(isLastCharBlank == 0)
				isLastCharBlank = 1;

			blanksAlready++;
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
