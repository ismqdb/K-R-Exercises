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

struct tnode {
    char* word;
    int count;
};

void addWord(struct tnode*[], char*, int*);
void quicksort(struct tnode* v[], int left, int right);
void print(struct tnode* nodes[]);
void swap(struct tnode* v[], int i, int j);

int main(){
    char word[MAXWORD];
    struct tnode* nodes[MAXN];
    int arraySize = 0;

    while(getword(word, MAXWORD) != EOF)
        addWord(nodes, word, &arraySize);

    quicksort(nodes, 0, arraySize-1);

    print(nodes);

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

struct tnode* talloc(){
    return (struct tnode*)malloc(sizeof(struct tnode));
}

void addWord(struct tnode* nodes[], char* word, int* arraySize){
    int i;

    for(i = 0; nodes[i] != NULL; i++)
        if(!strcmp(nodes[i]->word, word)){
            nodes[i]->count++;
            return;
        }

    // node is null
    nodes[i] = talloc();
    nodes[i]->count = 1;
    nodes[i]->word = _strdup(word);
    (*arraySize)++;
}

char* _strdup(const char* s){
    char* p = (char*)malloc(strlen(s)+1);

    if(p != NULL)
        strcpy(p, s);

    return p;
}

// increasing order, middle pivot
void quicksort(struct tnode* v[], int left, int right) {
	int i, last;

	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;

	for (i = left + 1; i <= right; i++)
		if (v[i]->count > v[left]->count)
			swap(v, ++last, i);


	swap(v, left, last);
	quicksort(v, left, last - 1);
	quicksort(v, last + 1, right);
}

void print(struct tnode* nodes[]){
    printf("\n\n");

    for(int i = 0; nodes[i] != NULL; i++)
        printf("%d: %s.\n", nodes[i]->count, nodes[i]->word);
}

void swap(struct tnode* v[], int i, int j) {
    if(i == j) return;

	struct tnode temp;

	temp = *v[i];
	*v[i] = *v[j];
	*v[j] = temp;
}
