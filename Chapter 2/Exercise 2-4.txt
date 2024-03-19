#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void squeeze(char s1[], char s2[]) {
	int i;

	for(i = 0; s1[i] != '\0'; i++)
		for(int j = 0; s2[j] != '\0'; j++)
			if(s1[i] == s2[j])
				s1[i] = ' ';

	s1[i+1] = '\0';

	int blanksAlready = 0;

	for (i = 0; s1[i] != '\0'; i++) {
		if(s1[i] == ' ')
			blanksAlready++;
		else
			if (isalpha(s1[i])) 
				if(blanksAlready == 0)
					;
				else {
					s1[i - blanksAlready] = s1[i];
					s1[i] = ' ';
					i -= blanksAlready - 1;
					blanksAlready = 1;
				}
		
	}

	s1[i+1] = '\0';

	for(int i = 0; s1[i] != '\0'; i++)
		if(s1[i] != '\0')
			putchar(s1[i]);
}

int main() {
	char s1[20] = "MSQMSQMSQ\0";
	char s2[20] = "MS\0";

	squeeze(s1, s2);
}