#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NUMBER '0'
#define MAX 100

void reverse_p(char* s);
void reverse(char s[]);

// getline 1, 4
// atoi, itoa 2, 3, 4
// reverse 3
// strindex, getop 4

/* getline: read a line into s, return length */ // c1
int getline(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c; ++i;
	}

	s[i] = '\0';

	return i;
}

int getline_p(char* s, int lim) {
	int c, i;
	char arr[MAX];

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		arr[i] = c;

	if (c == '\n') {
		arr[i] = c;
		++i;
	}

	arr[i] = '\0';
	strcpy(s, arr);

	return i;
}

/* getline: get line into s, return length */ // c4
int getline2(char s[], int lim) {
	int c, i;
	i = 0;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}

int getline2_p(char* s, int lim) {
	int c, i;
	i = 0;

	char arr[MAX];

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		arr[i++] = c;

	if (c == '\n')
		arr[i++] = c;

	arr[i] = '\0';
	strcpy(s, arr);

	return i;
}

/* atoi: convert s to integer */
int atoi1(char s[]) {
	int i, n;
	n = 0;

	for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = 10 * n + (s[i] - '0');

	return n;
}

/* atoi: convert s to integer */
int atoi1_p(char* s) {
	int i, n;
	n = 0;

	for (i = 0; *(s + i) >= '0' && *(s + i) <= '9'; ++i)
		n = 10 * n + (*(s + i) - '0');

	return n;
}

/* atoi: convert s to integer; version 2 */ //c3
int atoi2(char s[]) {
	int i, n, sign;

	for (i = 0; isspace(s[i]); i++) /* skip white space */;
	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '+' || s[i] == '-') /* skip sign */
		i++;

	for (n = 0; isdigit(s[i]); i++)
		n = 10 * n + (s[i] - '0');

	return sign * n;
}

/* atoi: convert s to integer; version 2 */ //c3
int atoi2_p(char* s) {
	int i, n, sign;

	for (i = 0; isspace(*(s + i)); i++) /* skip white space */;
	sign = (*(s + i) == '-') ? -1 : 1;

	if (*(s + i) == '+' || *(s + i) == '-') /* skip sign */
		i++;

	for (n = 0; isdigit(*(s + i)); i++)
		n = 10 * n + (*(s + i) - '0');

	return sign * n;
}

/* itoa: convert n to characters in s */ //c3
void itoa(int n, char s[]) {
	int i, sign;

	if ((sign = n) < 0) /* record sign */
		n = -n; /* make n positive */
	i = 0;

	do { /* generate digits in reverse order */
		s[i++] = n % 10 + '0'; /* get next digit */
	} while ((n /= 10) > 0); /* delete it */

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';

	reverse(s);
}

void itoa_p(int n, char* s) {
	int i, sign;
	char arr[MAX];

	if ((sign = n) < 0) /* record sign */
		n = -n; /* make n positive */
	i = 0;

	do { /* generate digits in reverse order */
		arr[i++] = n % 10 + '0'; /* get next digit */
	} while ((n /= 10) > 0); /* delete it */

	if (sign < 0)
		arr[i++] = '-';

	arr[i] = '\0';
	strcpy(s, arr);

	reverse_p(s);
}

/* reverse: reverse string s in place */
void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}

}

void reverse_p(char* s) {
	int c, i, j;
	char arr[MAX];

	for (i = 0, j = strlen(s) - 1; j >= 0; i++, j--) {
		arr[i] = *(s + j);
	}
	arr[i] = '\0';
	strcpy(s, arr);
}

/* strindex: return index of t in s, -1 if none */
int strindex(char s[], char t[]) {
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++);
		if (k > 0 && t[k] == '\0')
			return i;
	}

	return -1;
}

int strindex_p(char* s, char* t) {
	int i, j, k;

	for (i = 0; *(s + i) != '\0'; i++) {
		for (j = i, k = 0; *(t + k) != '\0' && *(s + j) == *(t + k); j++, k++);
		if (k > 0 && *(t + k) == '\0')
			return i;
	}

	return -1;
}

/* getop: get next character or numeric operand */
int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;

	s[1] = '\0';

	if (!isdigit(c) && c != '.')
		return c; /* not a number */

	i = 0;

	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;

	if (c == '.') /* collect fraction part */

		while (isdigit(s[++i] = c = getch()))
			;

	s[i] = '\0';

	if (c != EOF)
		ungetch(c);

	return NUMBER;
}

int getop_p(char* s) {
	int i, c;
	char buffer[MAX];

	while ((buffer[0] = c = getchar()) == ' ' || c == '\t')
		;

	buffer[1] = '\0';

	if (!isdigit(c) && c != '.')
		return c; /* not a number */

	i = 1;

	if (isdigit(c)) /* collect integer part */
		while (isdigit(buffer[i] = c = getchar()))
			;

	if (c == '.') /* collect fraction part */

		while (isdigit(buffer[i++] = c = getchar()))
			;

	buffer[i] = '\0';

	if (c != EOF);
		//ungetch(c);

	strcpy(s, buffer);

	return NUMBER;
}

int main() {
	char s[MAX];
	getop_p(s);
	getop_p(s);
	printf("%s", s);
}