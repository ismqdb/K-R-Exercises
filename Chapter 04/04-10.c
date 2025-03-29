#include <stdio.h> 
#include <stdlib.h> /* for atof() */ 
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100	/* max size of operand or operator */ 
#define MAXVAL 100	/* maximum depth of val stack */
#define BUFSIZE 100

#define NUMBER '0'	/* signal that a number was found */ 
#define POW '1'
#define SIN '2'
#define EXP '3'
#define VARDEF '4'	/* signal that the variable is found */
#define VARPRINT '5'

int sp = 0;			/* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */
unsigned varTableIndex = 0;		// current varTablePos
char varTable[MAXVAL][MAXVAL];	// array to store variable
double varValues[MAXVAL];			// variable values

double dupl[MAXVAL];	/* duplicate stack */
int duplCounter = 0;

int getop(char[]);
void push(double);
double pop(void);
void ungets(char[]);
void printTop(void);
void swapTopTwo(void);
void duplicateStack(void);
void clearStack(void);
void varDecl(char[]);
int isVarDeclared(char var[]);
void clearCharBuffer(void);
void getline();

/* reverse Polish calculator */
int main() {
	int type;
	double op2;
	char s[MAXOP];

	getline();

 	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case VARDEF:
			
			break;
		case VARPRINT:
			push(varValues[varTableIndex - 1]);
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
			clearCharBuffer();
			getline();
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

void clearCharBuffer(void) {
	for (int i = 0; i < bufp; i++)
		buf[i] = 0;
	bufp = 0;
}

/* getop: get next character or numeric operand */
int getop(char s[]) {
	int i = 0, c;

	while ((s[0] = c = buf[bufp++]) == ' ' || c == '\t')
		;

	s[1] = '\0';
	if (s[0] == '\0')
		return '\n';

	if (!isdigit(c) && !isalpha(c) && c != '.')
		return c; 	/* not a number */

	// check is it pow, exp or sin
	if (isalpha(c))
		while (isalpha(s[++i] = c = buf[bufp++]))	;

	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = buf[bufp++]))
			;

	if (c == '.') /* collect fraction part */
		while (isdigit(s[++i] = c = buf[bufp++]))
			;

	s[i] = '\0';

	if (!strcmp(s, "pow"))
		return POW;

	if (!strcmp(s, "sin"))
		return SIN;

	if (!strcmp(s, "exp"))
		return EXP;

	// check is it a number
	if (atof(s) != 0)
		return NUMBER;
	else
		if (strlen(s) == 1)
			return 0;

	if (isVarDeclared(s))
		return VARPRINT;
	else {
		varDecl(s);
		return VARDEF;
	}
}

void getline() {
	while ((buf[bufp++] = getchar()) != '\n')
		;

	buf[--bufp] = '\0';
	bufp = 0;
}

void ungets(char s[]) {
	for (unsigned i = 0; s[i] != '\0'; i++)
		buf[bufp++] = s[i];
}

int isVarDeclared(char var[]) {
	for (unsigned i = 0; i < varTableIndex; i++)
		if (!strcmp(varTable[i], var))
			return 1;

	return 0;
}

void varDecl(char arg[]) {
	// throws an error if var name is longer than 7
	strcpy_s(varTable[varTableIndex], sizeof arg, arg);
	varValues[varTableIndex++] = val[sp-1];
}