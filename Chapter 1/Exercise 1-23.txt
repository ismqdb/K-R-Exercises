// KOMENTAR
/* KOMENTAR */

#include <stdio.h> 

#define MAXLINE 100000

int getSourceCode(char line[], int maxline);
void removeComments(char line[], int lineLength);

int main() { // KOMENTAR
    int len = 0;
    char line[MAXLINE];

    len = getSourceCode(line, MAXLINE);
    removeComments(line, len);

    return 0;
}

void removeComments(char input[], int lineLength) {
    int dashAlready = 0;

    int singleRowComment = 0;
    int multipleRowsComment = 0;
    int isQuoteString = 0;

    /* MULTILINE
       KOMENTAR
    */

    for (int i = 0; i < lineLength; ++i) {
        if (input[i] == '\'')
            if (isQuoteString)
                isQuoteString = 0;
            else
                isQuoteString = 1;

        if (input[i] == '\/')
            if (!isQuoteString) {
                dashAlready = 1;
                i++;
            }

        if (dashAlready && !isQuoteString)
            if (input[i] == '*') {
                multipleRowsComment = 1;
                dashAlready = 2;
            }
            else if (input[i] == '\/') {
                singleRowComment = 1;
                dashAlready = 2;
            }

        if (dashAlready != 2)
            putchar(input[i]);
        else
            if (singleRowComment) {
                while (input[i] != '\n')
                    ++i;

                putchar('\n');

                singleRowComment = 0;
                dashAlready = 0;
            }

            else if (multipleRowsComment)
                while (dashAlready != 0) {
                    if (input[i] == '\/' || input[i] == '*') 
                        dashAlready--;                        

                    i++;
                }
    }
}

int getSourceCode(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF; ++i)
        s[i] = c;

    s[i] = '\0';

    return i;
}


