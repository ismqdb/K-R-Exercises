#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLINE 1000

void detab(int input[], int length);
void entab(int input[], int length);
int getline(int s[], int lim);
int stoi(char[]);

int tabLen = 8;
int n = 0;
int m = 8;

int main(int argc, char* argv[]) {
	int len;
	int line[MAXLINE];

;	if (argc > 2) {
		m = stoi(argv[2]);
		n = stoi(argv[3]);
	}

	while ((len = getline(line, MAXLINE)) > 0)
		entab(line, len);

	return 0;
}

void detab(int input[], int length) {
	int charsAlready = 0;

	for (int i = 0; i < length; ++i) {

		if (i > 1 && ((i%n) == 1)) {
			for (int k = 0; k < tabLen; k++)
				putchar(' ');
			putchar(input[i]);
		}
		else
			putchar(input[i]);
	}
}

void entab(int input[], int length) {
	int charsAlready = 0;
	int blanksAlready = 0;
	int isLastCharBlank = 0;

	for (int i = 0; i < length; ++i) {
		if (charsAlready > 1 && ((i % n) == 1)) {
			for(int k = 0; k < tabLen; k++)
				putchar(' ');
			putchar(input[i]);

			charsAlready = 0;
			blanksAlready = 0;
		}
		else {

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
}

int stoi(char s[]) {
	int val = 0;
	int len = strlen(s);

	for (int i = 1; i < len; i++)
		val += ((s[i] - '0') * pow(10, len - i - 1));

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