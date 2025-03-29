#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

enum {MAXTOKEN = 100, BUFSIZE = 100};

char buf[BUFSIZE];
int bufp = 0;

enum { NAME, PARENS, BRACKETS };

int dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;              /* Type of the last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* Identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];

int getch(void);
void ungetch(int);
int validType(char* name);
void popch();
int peek();

int convert();
void undcl();

/* dcl: parse a declarator */
int dcl(void){
    int ns;
    int n;

    n = gettoken();

    if(n != '*' && !isalnum(n) && n != '(')
        return 0;

    ungetch(n);

    for(ns = 0; gettoken() == '*'; ) /* count */
        ns++;

    dirdcl();
    while(ns-- >0)
        strcat(out, " pointer to");

    return 1;
}

/* dirdcl: parse a direct declarator */
void dirdcl(void){
    int type;

    if(tokentype == '('){       /* (dcl) */
        dcl();
        if(tokentype != ')')
            printf("error: missing )\n");

    } else if(tokentype == NAME)
        strcpy(name, token);
    else {
        printf("error: expected name or (dcl)\n");
        exit(1);
    }

    while((type=gettoken()) == PARENS || type == BRACKETS)
        if(type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

int gettoken(void) /* return next token */
{
    int c;
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else if(isalpha(c)){
            memset(token, '\0', sizeof(token));
            *p++ = '(';
            *p++ = c;
            while((c = getch()) != ')')
                *p++ = c;
            *p = ')';

            if(validType(token)){
                memset(token, '\0', sizeof token);
                strcpy(token, "()");
            }
            return tokentype = PARENS;
        }
        else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
        ;
        *p = '\0';
        return tokentype = BRACKETS;

    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;

    } else
    return tokentype = c;
}

int peek(){
    int retValue = gettoken();

    popch();

    int inputSize = 0;

    while(token[inputSize++] != '\0')
        ;

    for(int i = inputSize - 1; i >= 0; i--)
        buf[bufp++] = token[i];

    //buf[bufp] = '\0';

    memset(token, '\0', sizeof(token));


    return retValue;
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

void popch(){
    buf[--bufp] = '\0';
}

int validType(char* typeName){
    if(!strcmp(typeName, "char"))
        return 1;

    if(!strcmp(typeName, "int"))
        return 1;

    if(!strcmp(typeName, "void"))
        return 1;

    if(!strcmp(typeName, "float"))
        return 1;

    if(!strcmp(typeName, "double"))
        return 1;

    return 0;
}

int convert(){
    while(gettoken() != EOF){       // 1st token on line
        if(validType(token))
            strcpy(datatype, token);    // is the datatype
        else {
            printf("Invalid type name: %s.\n\n", token);
            while(gettoken() != '\n')
                ;
            bufp = 0;
            buf[0] = '\0';
            continue;
        }

        out[0] = '\0';
        if(!dcl())                      // parse rest of the line
            continue;

        if(tokentype != '\n'){
            printf("Syntax error\n");
            continue;
        }
        printf("%s: %s %s\n\n", name, out, datatype);
    }

    return 0;
}

/* undcl: convert word description to declarations */
void undcl(){
    int type;
    char temp[1100];

    while(gettoken() != EOF){
        if(token[0] == '(' || token[0] == '[')
           continue;
        strcpy(out, token);
        while((type=gettoken()) != '\n'){
            if(type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if(type == '*'){
                if(peek() == NAME)
                    sprintf(temp, "*%s", out);
                else
                    sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            } else if(type == NAME){
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else  {
                printf("Invalid input at %s.\n\n", token);
                exit(1);
            }
        }

        printf("%s\n\n", out);
        break;
    }
}

int main(void){
    undcl();

    return 0;
}

/*

C operator precedence:

()  -> function call
[]  -> Array declarator
*   -> Dereference operator

dcl:
    optional *'s direct-dcl
direct-dcl
    name
    (dcl)
    direct-dcl()
    direct-dcl[optional size]

char (*(*x[3])())[5]

*/
