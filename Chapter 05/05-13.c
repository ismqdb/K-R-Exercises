#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */

char* lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char* lineptr[], int nlines);
void writelines(char* lineptr[], int nlines);
int stoi(char s[]);

int linesToWrite = 0;

/* sort input lines */
int main(int argc, char* argv[]) {
    int nlines; /* number of input lines read */

    if (argc > 2) {
        linesToWrite = stoi(argv[2]);
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        linesToWrite = nlines - linesToWrite;
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int stoi(char s[]) {
    int val = 0;
    int len = strlen(s);

    for (int i = 1; i < len; i++)
        val += ((s[i] - '0') * pow(10, len - i - 1));

    return val;
}

#define MAXLEN 1000 /* max length of any input line */
int getline(char*, int);
char* alloc(int);

/* readlines: read input lines */
int readlines(char* lineptr[], int maxlines) {
    int len, nlines;
    char* p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char* lineptr[], int nlines) {
    int i;

    for (i = linesToWrite; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* getline: read a line into s, return length */
int getline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char* allocp = allocbuf; /* next free position */

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

/* swap: interchange v[i] and v[j] */
void swap(char* v[], int i, int j) {
    char* temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}