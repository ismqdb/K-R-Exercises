 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

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

int main(){
    install("MAXN", "100");
    undef("MAXN");

    install("MAXN", "100");
    printf("%s=%s\n", lookup("MAXN")->name, lookup("MAXN")->defn);
}
