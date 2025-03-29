 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASHSIZE 101

enum {MAXTOKEN = 100, BUFSIZE = 100};
#define MAXWORD 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);

struct nlist {
    struct nlist* next;
    char* name;
    char* defn;
};

static struct nlist* hashtab[HASHSIZE];
struct nlist* lookup(char*);
char* _strdup(char*);
void undef(char*);
void freeptr(struct nlist*);

int isValidChar(char c, int first);
int getword(char* word, int lim);

unsigned hash(char* s){
    unsigned hashval;

    for(hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

struct nlist* lookup(char* s){
    struct nlist* np;

    for(np = hashtab[hash(s)]; np != NULL; np = np->next)
        if(!strcmp(s, np->name))
            return np;
    return NULL;
}

struct nlist* install(char* name, char* defn){
    struct nlist* np;
    unsigned hashval;

    if((np = lookup(name)) == NULL){
        np = (struct nlist*)malloc(sizeof(*np));
        if(np == NULL || (np->name = _strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void*)np->defn);

    if((np->defn = _strdup(defn)) == NULL)
        return NULL;

    return np;
}

char* _strdup(char* s){
    char* p = (char*)malloc(strlen(s)+1);

    if(p != NULL)
        strcpy(p, s);

    return p;
}

void undef(char* name){
    struct nlist* np;
    unsigned hashval;

    if((np = lookup(name)) == NULL)
        return;

    hashval = hash(name);

    for(np = hashtab[hashval]; np != NULL; np = np->next)
        if(!strcmp(np->name, name)){
            freeptr(np);
            return;
        }
}

void freeptr(struct nlist* ptr){
    if(ptr->next != NULL)
        freeptr(ptr->next);
    else {
        strcpy(ptr->name, "\0");
        strcpy(ptr->defn, "\0");
    }
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

int getword(char* word, int lim){
    int c;
    char* w = word;

    while(isspace(c = getch()))
        ;

    if(c != EOF)
        *w++ = c;

    if(!isValidChar(c, 1)){
        *w = '\0';
        return c;
    }

    for(; --lim > 0; w++){
        *w = getch();

        if(!isValidChar(*w, 0)){
            ungetch(*w);
            break;
        }
    }

    *w = '\0';
    return word[0];
}

int isValidChar(char c, int first){
    if(c == EOF)
        return 0;

    if(c == '_')
        return 1;

    if(isalpha(c))
        return 1;

    if(isdigit(c))
        return 1;

    if(c == '#')
        return 1 * first;

    if(c == '\n')
        return 0;

    if(c == ' ')
        return 0;

    if(c == ';')
        return 0;

    if(c == ',')
        return 0;

    return 0;
}

int main(){
    char keyword[MAXWORD];
    char var[MAXWORD];
    char value[MAXWORD];

    getword(keyword, 100);

    if(strcmp(keyword, "#define") != 0){
        fprintf(stderr, "#define command format not valid.\n");
        exit(1);
    }

    getword(var, 100);

    if(var[0] != '_' && !isalpha(var[0])){
        fprintf(stderr, "Variable name must start with _ or letter.\n");
        exit(1);
    }

    getword(value, 100);

    if(atoi(value) == 0){
        fprintf(stderr, "Value not a number.\n");
        exit(1);
    }

    install(var, value);
    printf("%s=%s\n", lookup(var)->name, lookup(var)->defn);
}
