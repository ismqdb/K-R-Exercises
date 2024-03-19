#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct key {
    char* word;
    int count;
} keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"do", 0},
    {"double", 0},
    {"else", 0},
    {"enum", 0},
    {"extern", 0},
    {"float", 0},
    {"for", 0},
    {"goto", 0},
    {"if", 0},
    {"inline", 0},
    {"int", 0},
    {"long", 0},
    {"register", 0},
    {"return", 0},
    {"short", 0},
    {"signed", 0},
    {"sizeof", 0},
    {"static", 0},
    {"struct", 0},
    {"switch", 0},
    {"typedef", 0},
    {"union", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

#define NKEYS (sizeof keytab) / (sizeof keytab[0])

enum {MAXTOKEN = 100, BUFSIZE = 100};

int getword(char*, int);
int binsearch(char*, struct key*, int);
int getch(void);
void ungetch(int);
int isValidChar(char c, int first, char del);

char buf[BUFSIZE];
int bufp = 0;

int main(){
    int n;
    char word[MAXWORD];

    int nkeys = (int)NKEYS;

    while(getword(word, MAXWORD) != EOF){
        if(isalpha(word[0]))
            if((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
        printf("%s\n", word);
    }

    for(n = 0; n < nkeys; n++)
        if(keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);

    return 0;
}

int binsearch(char* word, struct key tab[], int n){
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;

    while(low <= high){
        mid = (low+high)/2;
        if((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if(cond > 0)
            low = mid+1;
        else
            return mid;
    }

    return -1;
}

int getword(char* word, int lim){
    int c;
    char* w = word;
    char del = ' ';

    while(isspace(c = getch()))
        ;

    if(c != EOF)
        *w++ = c;

    if(!isValidChar(c, 1, ' ')){
        *w = '\0';
        return c;
    }

    if(c == '\"' || c == '/')
        del = '\n';

    for(; --lim > 0; w++){
        *w = getch();

        if(!isValidChar(*w, 0, del)){
            ungetch(*w);
            break;
        }
    }

    *w = '\0';
    return word[0];
}

int getch(void){                    /* get a character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if(bufp > BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int isValidChar(char c, int first, char del){
    if(c == '_')
        return 1;

    if(c == '#')
        return 1;

    if(c == '\"')
        return 1;

    if(isalpha(c))
        return 1;

    if(isdigit(c))
        return 1 * first;

    if(c == del)
        return 0;

    if(c == EOF)
        return 0;

    if(c == '\n')
        return 0;

    return 1;
}
