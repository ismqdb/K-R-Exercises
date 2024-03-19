
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct key {
    char* word;
    int count;
} const keytab[] = {
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

#define MAXWORD 100
#define MAXN 100
#define NKEYS (sizeof keytab) / (sizeof keytab[0])

enum {MAXTOKEN = 100, BUFSIZE = 100};

char buf[BUFSIZE];
int bufp = 0;

int getword(char*, int);

int getch(void);
void ungetch(int);

int isValidChar(char c, int first);
int isKeyword(char* word);
int isVarName(char* word);

struct tnode {
    char* word;
    struct tnode* child;
};

struct tnode* talloc();
void treefree(struct tnode* root);
void treeprint(struct tnode* root);

void swapWords(char*, char*);

struct tnode* addnode(struct tnode*, const char*);
int checkFirstn(const char*, const char*, int);
int parseCmdArgs(int argc, char* argv[]);

char* _strdup(const char*);

int main(int argc, char* argv[]){
    unsigned firstN = 6;
    firstN = parseCmdArgs(argc, argv);

    char word[MAXWORD];
    struct tnode* nodes[MAXN] = {NULL};

    while(getword(word, MAXWORD) != EOF)
        if(isVarName(word)){
            int i;
            for(i = 0; nodes[i] != NULL; i++){
                if(checkFirstn(nodes[i]->word, word, firstN)){
                    nodes[i] = addnode(nodes[i], word);
                    break;
                }
            }
            nodes[i] = addnode(nodes[i], word);
        }

    for(int i = 0; i < MAXN; i++)
        if(nodes[i] != NULL){
            printf("\n\n");
            printf("Node no. %d:\n", i);
            treeprint(nodes[i]);
        }

    for(int i = 0; i < MAXN; i++)
        if(nodes[i] != NULL)
            treefree(nodes[i]);

    return 0;
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

int getch(void){                    /* get a character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if(bufp > BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int isValidChar(char c, int first){
    if(c == EOF)
        return 0;

    if(c == '_')
        return 1;

    if(isalpha(c))
        return 1;

    if(isdigit(c))
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

int isVarName(char* word){
    if(!isalpha(*word) && *word != '_')
        return 0;

    if(isKeyword(word))
        return 0;

    return 1;
}

int isKeyword(char* word){
    for(size_t i = 0; i < NKEYS; i++)
        if(strcmp(word, keytab[i].word) == 0)
            return 1;

    return 0;
}

struct tnode* addnode(struct tnode* node, const char* word){
    int cond;

    if(node == NULL){
        node = talloc();
        node->word = _strdup(word);
        node->child = NULL;
    } else if((cond = strcmp(word, node->word)) == 0)
        ;
    else if(cond > 0){
        node->child = addnode(node->child, word);
    }
    else {
        struct tnode* temp = talloc();
        temp->word = _strdup(word);
        temp->child = node;
        return temp;
    }

    return node;
}

void swapWords(char* x, char* y){
    char* temp;

    temp = x;
    x = y;
    y = temp;
}

int checkFirstn(const char* x, const char* y, int firstN){
    if(x == NULL || y == NULL)
        return 0;

    for(int i = 0; i < firstN; i++)
        if(*(x+i) != *(y+i))
            return 0;

    return 1;
}

struct tnode* talloc(){
    return (struct tnode*)malloc(sizeof(struct tnode));
}

int parseCmdArgs(int argc, char* argv[]){
    int ret = 6;

    if(argc == 2){
        ret = atoi(argv[1]);
        if(ret <= 0 || ret > 10)
            fprintf(stderr, "Invalid format. Using default value of 6.\n\n");
    } else
        fprintf(stderr, "Invalid format. Using default value of 6.\n\n");


    return ret;
}

void treefree(struct tnode* root){
    if(root != NULL){
        treefree(root->child);
        free(root);
    }
}

void treeprint(struct tnode* root){
    if(root!=NULL){
        printf("\t%s\n", root->word);
        treeprint(root->child);
    }
}

char* _strdup(const char* s){
    char* p = (char*)malloc(strlen(s)+1);

    if(p != NULL)
        strcpy(p, s);

    return p;
}
