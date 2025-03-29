#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLINE 1000

void detab(int input[], int length);
int getline(int s[], int lim);
int stoi(char[]);

int tabLen = 8;

int main(int argc, char *argv[]) {
	int len;
	int line[MAXLINE];

	if (argc > 2)
		tabLen = stoi(argv[2]);

	while ((len = getline(line, MAXLINE)) > 0)
		detab(line, len);

	return 0;
}

void detab(int input[], int length) {
	int charsAlready = 0;

	for (int i = 0; i < length; ++i) {
		if (charsAlready == tabLen)
			charsAlready = 0;

		if (input[i] != '\t') {
			charsAlready++;
			putchar(input[i]);
		}
		else {
			for (int j = 0; j < tabLen - charsAlready; ++j)
				putchar(' ');
			charsAlready = 0;
		}
	}
}

void entab(int input[], int length) {
	int charsAlready = 0;
	int blanksAlready = 0;
	int isLastCharBlank = 0;

	for (int i = 0; i < length; ++i) {
		if (charsAlready == tabLen) {
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
			if (isLastCharBlank == 0)
				isLastCharBlank = 1;

			blanksAlready++;
		}
	}
}

int stoi(char s[]) {
	int val = 0;
	int len = strlen(s);

	for (int i = 0; i < len; i++)
		val += ((s[i]-'0') * pow(10, len - i - 1));

	return val;
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