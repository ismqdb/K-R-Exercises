#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int getline(char[], int, FILE*);

/* find: print lines that match pattern from 1st arg */
main(int argc, char *argv[])
{
	char line[MAXLINE];
	long lineno = 0;

	int c, except = 0, number = 0, found = 0;

	const char *filepath = "./1.txt";
	FILE *file = fopen(filepath, "r");

	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
				case 'x':
					except = 1;
					break;
				case 'n':
					number = 1;
					break;
				default:
					printf("find: illegal option %c\n", c);
					argc = 0;
					found = -1;
					break;
			}

	if (argc != 1)
		printf("Usage: find -x -n pattern\n");
	else
		while (getline(line, MAXLINE, file) > 0) {
			lineno++;
			if ((strstr(line, *argv) != NULL) == except) {
				if (number)
					printf("In file \"%s\" match found on line %ld.\n", filepath, lineno);
				//printf("%s", line);
				found++;
			}
		}

	return found;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim, FILE *file) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = ((file == NULL) ? getchar() : getc(file))) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}
