#include <stdio.h> 
#include <stdlib.h> /* for atof() */ 
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100	/* max size of operand or operator */ 
#define NUMBER '0'	/* signal that a number was found */ 
#define MAXVAL 100	/* maximum depth of val stack */
#define BUFSIZE 100

#define POW '1'
#define SIN '2'
#define EXP '3'

int sp = 0;			/* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

double dupl[MAXVAL];	/* duplicate stack */
int duplCounter = 0;

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void printTop(void);
void swapTopTwo(void);
void duplicateStack(void);
void clearStack(void);

/* reverse Polish calculator */
int main() {
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case POW:
			push(pow(pop(), pop()));
			break;
		case SIN:
			push(sin(pop()));
			break;
		case EXP:
			push(exp(pop()));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			push(fmod(pop(), op2));
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

/* push: push f onto value stack */
void push(double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

void printTop(void) {
	int n = sp;

	printf("%g %g\n", val[sp--], val[sp]);
}

void duplicateStack(void) {
	for (duplCounter = 0; duplCounter < sp; duplCounter++)
		dupl[duplCounter] = val[duplCounter];
}

void swapTopTwo(void) {
	double temp;
	int n = sp;

	temp = val[n - 2];
	val[n - 2] = val[n - 1];
	val[n - 1] = temp;
}

void clearStack(void) {
	for (int i = 0; i < sp; i++)
		val[i] = 0;
}

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
		ungetch(c);

	if (!strcmp(s, "pow"))
		return POW;

	if (!strcmp(s, "sin"))
		return SIN;

	if (!strcmp(s, "exp"))
		return EXP;

	return NUMBER;
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
