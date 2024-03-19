#include <stdio.h>
#include <ctype.h>
#include "calc.h"

#define BUFSIZE 100

static char buf[BUFSIZE];	/* buffer for ungetch */
static int bufp = 0;		/* next free position in buf */

/* getop: get next character or numeric operand */
int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;

	s[1] = '\0';
	if (!isdigit(c) && !isalpha(c) && c != '.')
		return c; 	/* not a number */

	i = 0;

	// check is it pow, exp or sin
	if (isalpha(c))
		while (isalpha(s[++i] = c = getch()))
			;

	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;

	if (c == '.') /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;

	s[i] = '\0';

	if (c != EOF)
		if (bufp >= BUFSIZE)
			printf("ungetch: too many characters\n");
		else
			buf[bufp++] = c;

	return NUMBER;
}