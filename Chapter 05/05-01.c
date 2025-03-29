#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

#define BUFSIZE 100 
char buf[BUFSIZE]; /* buffer for ungetch */ 
int bufp = 0; /* next free position in buf */

int array[BUFSIZE];

/* getint: get next integer from input into *pn */
int getint(int* pn) {
	int c, sign;

	while (isspace(c = getch()));

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		while (c < '0' || c > '9')
			c = getchar();	

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}


int main() {
	for (int n = 0; n < BUFSIZE && getint(&array[n]) != EOF; n++)
		;
}

int getch(void) /* get a (possibly pushed-back) character */ { 
	return (bufp > 0) ? buf[--bufp] : getchar(); 
} 

void ungetch(int c) /* push character back on input */ { 
	if (bufp >= BUFSIZE) 
		printf("ungetch: too many characters\n"); 
	else 
		buf[bufp++] = c; 
}