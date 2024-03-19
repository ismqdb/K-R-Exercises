#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void swap(void* v[], int, int);

#define MAXLINES 5000
#define MAXLEN 1000 				/* max length of any input line */
#define ALLOCSIZE 10000 			/* size of available space */

static char allocbuf[ALLOCSIZE]; 	/* storage for alloc */
static char* allocp = allocbuf; 	/* next free position */

char* alloc(int);
void afree(char* p);
int getln(char*, int);
int readlines(char* lineptr[], int nlines);
int numcmp(const char*, const char*);
int numcmp_(const char*, const char*, int);
int strcmp_(const char*, const char*, int);
void quicksort(void* v[], int left, int right, int);
bool isDirChar(char c);
bool isDir(const char* c, int flags);
void writelines(char* lineptr[], int nlines);
char checkUpper(char c, bool flag);

// numcmp ---> numerically, string length
// strcmp ---> alphabetic

// lexicographically -> alphabetic order
// -n numerically -> 
// -r reverse
// -f fold
// -d directory order

// program -n -r
// program -nr

int main(int argc, char* argv[]) {
	int nlines;
	char* lineptr[MAXLINES];

	int flags = 0;

	if(argc == 1){
		if((nlines=readlines(lineptr, MAXLINES)) >= 0){
			quicksort((void**)lineptr, 0, nlines-1, 0);
			writelines(lineptr, nlines);
			return 0;
		} else {
			printf("Input too big to sort.\n");
			return 1;
		}
	}

	if(argc == 2){
		for(size_t i = 0; i < strlen(argv[1]); i++){
			if((*(argv[1]+i)) == 'n')
				flags |= 1;
			if((*(argv[1]+i)) == 'r')
				if(flags & 1)
					flags |= 2;
			if((*(argv[1]+i)) == 'f')
				flags |= 4;
			if((*(argv[1]+i)) == 'd')
				flags |= 8;
		}
	}

	if(argc > 2){
		for(int i = 1; i < argc; i++){
			if(strcmp(argv[i], "-n") == 0)
				flags |= 1;
			if(strcmp(argv[i], "-r") == 0)
				if(flags&1)
					flags |= 2;
			if(strcmp(argv[i], "-f") == 0)
				flags |= 4;
			if(strcmp(argv[i], "-d") == 0)
				flags |= 8;
		}
	}

	if((nlines=readlines(lineptr, MAXLINES)) >= 0){
		quicksort((void**)lineptr, 0, nlines-1, flags);
		writelines(lineptr, nlines);
		return 0;

	} else {
		printf("Input too big to sort.\n");
		return 1;
	}
	
}

void quicksort(void* v[], int left, int right, int flags) {
	int (*comp)(const char*, const char*, int);

	if(!flags || (flags&4))
		comp = strcmp_;

	if(flags&1)
		comp = numcmp_;

	int i, last;

	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;

	if(flags&8){
		for (i = left + 1; i <= right; i++)
			if(isDir(v[i], flags) && isDir(v[left], flags)){
				if (strcmp_(v[i], v[left], flags) < 0)
					swap(v, ++last, i);
			} else return;

	} else {
		for (i = left + 1; i <= right; i++)
			if ((*comp)(v[i], v[left], flags) < 0)
				swap(v, ++last, i);
	}

	swap(v, left, last);
	quicksort(v, left, last - 1, flags);
	quicksort(v, last + 1, right, flags);
}

bool isDirChar(char c){
	if(!isdigit(c) || !isalpha(c) || !isblank(c))
		return false;

	return true;
}

bool isDir(const char* c, int flags){
	for(size_t i = 0; *(c+i) != '\0'; i++)
		if(!isDirChar(flags&4 ? checkUpper(*(c+i), 1) : *(c+i)))
			return false;

	return true;
}

int numcmp(const char* s1, const char* s2) {
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int strcmp_(const char* s1, const char* s2, int flags) { // alphabetically
	char c1, c2;

	for(size_t i = 0; s1[i] != '\n' && s2[i] != '\n'; i++){
		c1 = checkUpper(s1[i], flags&4);
		c2 = checkUpper(s2[i], flags&4);

		if(c1 != c2){
			if(c1 > c2)
				return 1;
			if(c1 < c2)
				return -1;
			return 0;
		}
	}

	return 0;
}

char checkUpper(char c, bool flag){
	if(flag)
		if(isupper(c))
			return tolower(c);

	return c;
}

int numcmp_(const char* s1, const char* s2, int flags){ // numerically
	size_t v1 = strlen(s1);
	size_t v2 = strlen(s2);

	int reverse = 1;
	if(flags & 2)
		reverse = -1;

	if(v1 > v2)
		return 1*reverse;
	else if(v1 < v2)
		return -1*reverse;
	else 
		return 0;
}

void swap(void* v[], int i, int j) {
	void* temp;

	if (i == j) return;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* readlines: read input lines */
int readlines(char* lineptr[], int maxlines) {
	int len, nlines;
	char* p, line[MAXLEN];

	nlines = 0;
	while ((len = getln(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0'; /* delete newline */
			strcpy(p,  line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char* lineptr[], int nlines) {
	int i;

	putchar(10);
	putchar(10);

	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);

	putchar(10);
	putchar(10);
}

/* getln: read a line into s, return length */
int getln(char* s, int lim) {
	int i;
	int c = ' ';

	for (i = 0; i < lim - 1 && 
			(c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';
	return i;
}

char* alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	}
	else /* not enough room */
		return 0;
}

void afree(char* p) /* free storage pointed to by p */
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

