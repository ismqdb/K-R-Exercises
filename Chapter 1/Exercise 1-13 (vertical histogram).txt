#include <stdio.h>

#define MAXLINE 15

int main() {
	int c;
	int wlen[MAXLINE];				// array that stores word lenght;
	int i;
	int wordln = 0;					// lenght of the current word
	char pointer = 'n';				// if pointer == 'y', we are in the word

	for (i = 0; i < MAXLINE; ++i)
		wlen[i] = 0;

	while ((c = getchar()) != EOF) {
		if (c != ' ' && c != '\t' && c != '\n' && pointer == 'n') {
			++wordln;
			pointer = 'y';
		}
		else if ((c == ' ' || c == '\t' || c == '\n') && pointer == 'y') {
			pointer = 'n';
			++wlen[wordln];
			wordln = 0;
		}

		else if ((c == ' ' || c == '\t' || c == '\n') && pointer == 'n');

		else if (c != ' ' && c != '\t' && c != '\n' && pointer == 'y')
			++wordln;
	}

	// baskets[0]: words with 0-3 lenght
	// baskets[1]: words with 4-6 lenght
	int baskets[6] = { 0, 0, 0, 0, 0, 0 };

	for (i = 0; i < MAXLINE; ++i) {
		if (i < 3)
			baskets[0] += wlen[i];
		else if (i < 6)
			baskets[1] += wlen[i];
		else if (i < 9)
			baskets[2] += wlen[i];
		else if (i < 12)
			baskets[3] += wlen[i];
		else if (i < 15)
			baskets[4] += wlen[i];
		else if (i >= 15)
			baskets[5] += wlen[i];
	}
	// define and get the biggest value
	int rows = 0;

	for (i = 0; i < 6; ++i)
		if (baskets[i] > rows)
			rows = baskets[i];

	putchar(10);

	for (i = rows; i >= 0; --i) {
		putchar('*');
		if (i == 0) {
			for (int k = 0; k < 6; ++k)
				putchar('*');
		}
		else {
			int k;
			for (k = 0; k < 6; ++k)
				if (i == baskets[k])
					putchar('+');
				else
					putchar(' ');
		}
		putchar(10);
	}

}

















