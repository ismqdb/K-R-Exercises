#include <stdio.h>
#include <string.h>

#define N 10
#define MAX 100

//strncpy, strncat, and strncmp
//char* strncpy(s, ct, n); //copy at most n characters of string ct to s; return s.Pad with '\0''s if ct has fewer than n characters.
//char* strncat(s, ct, n); //concatenate at most n characters of string ct to string s, terminate s with '\0'; return s.
//int strncmp(cs, ct, n); //compare at most n characters of string cs to string ct; return <0 if cs < ct, 0 if cs == ct, or >0 if cs>ct.

char* strncpy_p(char* s, char* ct, int n) {
	int i = 0, j = 0;
	int ctlen = strlen(ct);
	int charsToAdd = ctlen - n+1;

	char buffer[MAX];

	while (n--) {
		if (charsToAdd-- > 0)
			buffer[i] = *(ct + j++);
		else
			buffer[i] = '\0';
		i++;
	}
	buffer[i] = '\0';

	s = buffer;
	return s;
}

char* strncat_p(char* s, char* ct, int n) {
	int i = 0, j = 0;
	int ctlen = strlen(ct);
	int charsToAdd = ctlen - n + 1;

	char buffer[MAX];

	while (*(s + i) != '\0') {
		buffer[i] = *(s + i);
		i++;
	}

	while (n--) {
		if (charsToAdd-- > 0)
			buffer[i] = *(ct + j++);
		else
			buffer[i] = '\0';
		i++;
	}
	buffer[i] = '\0';

	s = buffer;
	return s;
}

int strncmp_p(char* cs, char* ct, int n) {
	int i = 0;

	while (*(cs + i) == *(ct + i) && n-- > 0)
		if (*(cs + i) > *(ct + i))
			return 1;
		else if (*(cs + i) < *(ct + i))
			return -1;

	return 0;
}


int main() {
	char s[MAX] = "Marko\0";
	char t[MAX] = " Markovic\0";

	//printf("%s\n", strncpy_p(s, t, 3));
	//printf("%s\n", strncat_p(s, t, 3));
	//printf("%s", strncmp_p(s, t, N));
}