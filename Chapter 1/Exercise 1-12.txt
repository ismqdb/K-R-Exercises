#include <stdio.h> 

void main() { 
	int c;
	int hasBeenNewline = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ')
			if (hasBeenNewline == 0) {
				putchar(10);
				hasBeenNewline = 1;
			}
			else
				getchar();
		else {
			putchar(c);
			hasBeenNewline = 0;
		}
	}
}