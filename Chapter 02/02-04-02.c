#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int containsChar(char s1, char s2[]) {
	for(int j = 0; s2[j] != '\0'; j++)
		if(s1 == s2[j])
			return 1;

	return 0;
}

void squeeze(char s1[], char s2[]) {
	int i, j;

	for(i = j = 0; s1[i] != '\0'; i++)
		if(!containsChar(s1[i], s2))
			s1[j++] = s1[i];

	s1[j] = '\0';

	printf("%s", s1);
}

int main() {
	char s1[20] = "MSQMMSQMSQ";
	char s2[20] = "MS";

	squeeze(s1, s2);
}