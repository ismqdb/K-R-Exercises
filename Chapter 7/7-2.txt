 
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000

enum {MAXTOKEN = 100, BUFSIZE = 100};

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);

int main(int argc, char* argv[]){
    char input[MAXN];
    int lineBreak = 0;
    int i;

    for(i = 0; (input[i] = getch()) != EOF; i++){
        if(lineBreak == 50){
            input[i+1] = input[i];
            input[i] = '\n';
            lineBreak = 0;
        }

        lineBreak++;
    }

    input[i] = '\0';
    putchar(10);

    for(int k = 0; input[k] != '\0'; k++)
        if(isalpha(input[k]) || input[k] == '\n')
            putchar(input[k]);
        else
            printf("%X", input[k]);

    printf("\n\n");
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
