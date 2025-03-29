#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* expand: expand shorthand notation a-z in s1 to list abc...xyz in s2*/
void expand(char s1[], char s2[]) {
	char x1, x2, x3;
	x1 = x2 = x3 = ' ';

	unsigned s2Counter = 0;
	unsigned prevDash = 0;

	int i;

	for (i = 0; isdigit(s1[i]) || isalpha(s1[i]) || s1[i] == '-'; i++) {
		if(s1[i] == '-'){
			if (prevDash)
				continue;

			if (x1 == ' ')
				s2[s2Counter++] = '-';
			else if (x2 == ' ') {
				x2 = '-';
				prevDash = 0;
			}
			else if (x3 == ' ') 
				s2[s2Counter++] = '-';			
			
			prevDash = 1;
		}
		else if(isalpha(s1[i]) || isdigit(s1[i])) {
			if (x1 == ' ')
				x1 = s1[i];
			else {
				x3 = s1[i];
				if (x3 < x1) {
					printf("Invalid input. Please try again.\n");
					// terminate
					exit(EXIT_FAILURE);
				}

				for (int k = x1; k <= x3; k++) {
					s2[s2Counter++] = k;
				}

				x1 = x2 = x3 = ' ';
				prevDash = 0;
			}
		}
		else
			// invalid character
			exit(EXIT_FAILURE);
	}

	s2[s2Counter] = '\0';

	for (int i = 0; s2[i] != '\0'; i++)
		printf("%c", s2[i]);

	putchar(10);
}

int main() {
	char s2[1000];

	expand("a-z", s2);
	expand("a-b-c", s2);
	expand("a-z0-9", s2);
	expand("-a-z", s2);
	expand("--a-z0-5--", s2);
}