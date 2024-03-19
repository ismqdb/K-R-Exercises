#include <stdio.h>

int main() {

	int c;
	int alreadyBlank = 0;

	while ((c = getchar()) != EOF) {
		if (c != ' ') {
			putchar(c);
			alreadyBlank = 0;
		}
		else
			if (alreadyBlank == 0) {
				putchar(c);
				alreadyBlank = 1;
			}
			else
				getchar();
	}
}