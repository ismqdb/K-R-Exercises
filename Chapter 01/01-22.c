#include <stdio.h> 

#define MAXLINE 1000 
#define MAX_LINE_LENGTH 20

int getline(char line[], int maxline);
void foldInputLine(char line[], int lineLength);

main() {
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > 20) {
            foldInputLine(line, len);
        }
    }
}

void foldInputLine(char line[], int lineLength) {
    int charCount = 0;

    for (int i = 0; i < lineLength; ++i)
        if (charCount == MAX_LINE_LENGTH - 1) {
            charCount = 0;
            putchar(line[i]);
            putchar('\n');
        }
        else {
            putchar(line[i]);
            charCount++;
        }
}

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