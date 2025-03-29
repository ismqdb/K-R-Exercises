#include <stdio.h>
#include <string.h>

int strindex(char source[], char searchfor[]);

/* find all lines matching pattern */
int main() {
	char line[MAXLINE];
	int found = 0;

	printf("%d\n", strindex("could could not not could", "could"));

	return 0;
}

/* strindex: return index of t in s, -1 if none */ 
int strindex(char s[], char t[]) { 
	int i, j, k; 

	int index = -1;

	for (i = 0; s[i] != '\0'; i++) { 
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			; 

		if (k > 0 && t[k] == '\0')
			index = i;
	} 

	return index;
}