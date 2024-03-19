#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define MAXN 1000
enum {MAXTOKEN = 100, BUFSIZE = 100};

char buf[BUFSIZE];
int bufp = 0;

int getword(char*, int);
char* _strdup(const char* s);

int getch(void);
void ungetch(int);

int isValidChar(char c, int first);
int isNoiseWord(char* word);

int hasNewline(char* word);


const char* noiseWords[] = {
    "and",
    "or",
    "nor",
    "the",

};

struct tnode {
    char* word;
    int lineno;
    struct tnode* child;
};

struct tnode* addWord(struct tnode*, char*, int);
void treeprint(struct tnode*);

int main(){
    char word[MAXWORD];
    struct tnode* nodes[MAXN] = {NULL};
    int lineno = 0;

    while(getword(word, MAXWORD) != EOF){
        if(hasNewline(word))
            lineno++;
        if(!isNoiseWord(word)){
            int i;

            for(i = 0; nodes[i] != NULL; i++)
                if(!strcmp(nodes[i]->word, word)){
                    nodes[i] = addWord(nodes[i], word, lineno);
                    break;
                }

            if(nodes[i] == NULL)
                nodes[i] = addWord(nodes[i], word, lineno);
        }
    }

    for(int i = 0; nodes[i] != NULL; i++)
        treeprint(nodes[i]);

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

        if(*w == '\n'){
            w++;
            break;
        }

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

struct tnode* talloc(){
    return (struct tnode*)malloc(sizeof(struct tnode));
}

int isNoiseWord(char* word){
    for(int i = 0; noiseWords[i] != NULL; i++)
        if(strcmp(noiseWords[i], word) == 0)
            return 1;

    return 0;
}

struct tnode* addWord(struct tnode* node, char* word, int lineno){
    int i;

    if(node == NULL){
        node = talloc();
        node->word = _strdup(word);
        node->lineno = lineno;
        node->child = NULL;
    } else
        node->child = addWord(node->child, word, lineno);

    return node;

}

char* _strdup(const char* s){
    char* p = (char*)malloc(strlen(s)+1);

    if(p != NULL)
        strcpy(p, s);

    return p;
}

int hasNewline(char* word){
    for(int i = 0; *(word+i) != '\0'; i++)
        if(*(word+i) == '\n')
            return 1;

    return 0;
}

void treeprint(struct tnode* node){
    printf("\n\n");

    struct tnode* temp = node;
    printf("Word: %s\t", node->word);

    while(temp!=NULL){
        printf("%d ", temp->lineno);
        temp = temp->child;
    }

    printf("\n\n");
}
