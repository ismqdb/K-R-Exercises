#include <stdio.h>
#include <ctype.h>
#include <math.h>

int getch(void);
void ungetch(int);

#define BUFSIZE 100 
char buf[BUFSIZE]; /* buffer for ungetch */ 
int bufp = 0; /* next free position in buf */

int array[BUFSIZE];
float farr[BUFSIZE];

float getfloat(float* pn) {
	int c, sign;
	int dc = -1;

	while (isspace(c = getch()));

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		while (c < '0' || c > '9')
			c = getchar();

	for (*pn = 0; isdigit(c) && c != '.'; c = getch())
		*pn = 10 * *pn + (c - '0');

	if(c == '.')
		while (isdigit(c = getch())) {
			*pn += ((float)pow(10, dc) * (c - '0'));
			dc--;
		}

	*pn *= sign;
	if (c != EOF)
		ungetch(c);

	return c;
}


int main() {
	for (int n = 0; n < BUFSIZE && getfloat(&farr[n]) != EOF; n++)
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