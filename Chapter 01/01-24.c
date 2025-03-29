#include <stdio.h>

#define MAXLINE 1000

int getInput(char s[], int lim);

int checkParenthesis(char s[], char openingPar, char closingPar);
void printResult(char openingPar, char closingPar);

int checkQuotes(char s[], char quote);
void printQuotes(int value, char s[], char quote);

int checkSingleComments(char s[]);
void printResultForSingleComments(int value);

int checkMultiComments(char s[]);
void printResultForMultiComments(int value);

int checkEscapeSequences(char s[]);
void printResultForEscapeSequences(int value);


int main() {
    char line[MAXLINE];
    getInput(line, MAXLINE);

    printResult(checkParenthesis(line, '(', ')'), '(', ')');
    printResult(checkParenthesis(line, '{', '}'), '{', '}');
    printResult(checkParenthesis(line, '[', ']'), '[', ']');

    printQuotes(checkQuotes(line, '\''), line, '\'');
    printQuotes(checkQuotes(line, '\"'), line, '\"');

    printResultForSingleComments(checkSingleComments(line));
    printResultForMultiComments(checkMultiComments(line));
    
    printResultForEscapeSequences(checkEscapeSequences(line));
}

int getInput(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF; ++i)
        s[i] = c;

    s[i] = '\0';

    return i;
}

int checkParenthesis(char s[], char x, char y){
    int parenthesisOpened = 0;
    int i;

    for(i = 0; s[i] != '\0'; i++)
        if(s[i] == x)
            parenthesisOpened++;
        else if(s[i] == y)
            parenthesisOpened--;

    if(parenthesisOpened == 0)
        return 0;
    else
        return 1;
}

void printResult(int value, char openingPar, char closingPar) {
    putchar(10);

    putchar(openingPar);
    putchar(closingPar);
    putchar(':');
    putchar('\t');

    if (value == 0) 
        putchar('y');
    else if (value == 1)
        putchar('n');
}

int checkQuotes(char s[], char quote) {
    int quotes = 0;

    for (int i = 0; s[i] != '\0'; i++)
        if(s[i] == quote)
            quotes++;

    if (quotes == 0 || quotes % 2 == 0)
        return 0;
    else
        return 1;
}

void printQuotes(int value, char s[], char quote) {
    putchar(10);

    putchar(quote);
    putchar(':');
    putchar('\t');

    if (value == 0)
        putchar('y');
    else if (value == 1)
        putchar('n');
}

int checkSingleComments(char s[]) {
    int counter = 0;

    for(int i = 0; s[i] != '\0'; i+=2)
        if(s[i] == '\/' && s[i+1] == ' ')
            counter++;

    if(counter == 0 || counter % 2 == 0)
        return 0;
    else
        return 1;
}

void printResultForSingleComments(int value) {
    putchar(10);

    putchar('\/');
    putchar('\/');
    putchar(':');
    putchar('\t');

    if (value == 0)
        putchar('y');
    else if (value == 1)
        putchar('n');
}

int checkMultiComments(char s[]) {
    int counter = 0; 

    for(int i = 0; s[i] != '\0'; i+=2)
        if(s[i] == '\/' && s[i+1] == '*')
            counter++;
        else if(s[i] == '*' && s[i+1] == '\/')
            counter--;

    if(counter == 0)
        return 0;
    else
        return 1;
}

void printResultForMultiComments(int value) {
    putchar(10);

    putchar('\/');
    putchar('*');
    putchar('*');
    putchar('\/');
    putchar(':');
    putchar('\t');

    if (value == 0)
        putchar('y');
    else if (value == 1)
        putchar('n');
}

int checkIsEscapeSequence(char x, char y) {
    int counter = 0;
    if(x == '\\')
        if(!(y == 0x07 || y == 0x08 || y == 0x1B || y == 0x0C
            || y == 0x0A || y == 0x0D || y == 0x09 || y == 0x0B ||
            y == 0x5C || y == 0x27 || y == 0x22 || y == 0x3F || 
            y == '\0'))
        counter++;
        else
            counter--;

    if(counter != 0)
        return 1;
    else
        return 0;
}

int checkEscapeSequences(char s[]) {
    int counter = 0;

    for(int i = 0; s[i] != '\0' && s[i+1] != '\0'; i += 2)
        if (checkIsEscapeSequence(s[i], s[i+1]))
            ;

    if(counter > 0)
        return 1;
    else
        return 0;
}

void printResultForEscapeSequences(int value) {
    putchar(10);

    putchar('e');
    putchar('s');
    putchar(':');
    putchar('\t');

    if (value == 0)
        putchar('y');
    else if (value == 1)
        putchar('n');
}