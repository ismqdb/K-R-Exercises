#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

typedef struct tnode {
    int x;
    int y;
    char dot;
    char sign;
    char convSpec;
    char escape;
    char eof_;
    char special;
} tnode;

int isConvSpec(char c);

int minscanf(char* fmt, ...);
tnode parseformat(char input[]);
tnode createnode();

int main(){
    int x;
    int y;
    float z;
    char s[20];

    minscanf("%s", s);
    printf("%s\n", s);
}

int minscanf(char* fmt, ...){
    va_list ap;
    static int charsRead = 0;
    char *line;

    tnode node;

    char* speci;
    int *ival;
    char *sval;

    va_start(ap, fmt);

    while(1){
        node = parseformat(fmt);

        if(node.eof_ == 1)
            break;

        if(errno == EIO){
            //perror("Error while reading printf format. Try again.\n");
            printf("System error: %s.\n\n", strerror(errno));

            break;
        }

        switch(node.convSpec){
            case 'd':
                ival = va_arg(ap, int*);
                scanf("%d", ival);
                break;
            case 'f':
                break;
            case 's':
                sval = va_arg(ap, char*);
                scanf("%s", sval);
                break;
            default:
                speci = va_arg(ap, char*);
                if(node.special == *speci)
                    ;
                else if(node.special == ' ')
                    ;
                else {
                    fprintf(stderr, "Invalid format string. Try again.\n");
                    va_end(ap);
                    return -1;
                }
                break;
        }
    }

    va_end(ap);
    return charsRead;
}

tnode parseformat(char input[]){
    tnode node = createnode();
    static int i = 0;

    /*if(input[i] != '%' && input[i] != ' ' && !isescape(input[i])){
        errno = EIO;
    }*/

    //while(input[i++] == ' ')
        ;

    int isFormat = (input[i] == '%') ? 1 : 0;

    while(1){
        if(isFormat){
            if(input[i] == '-' || input[i] == '+')
                node.sign = input[i];

            if(isdigit(input[i]))
                if(node.dot != '.')
                    node.x = input[i] - '0';
                else
                    if(node.dot == '.')
                        node.y = input[i] - '0';

            if(input[i] == '.'){
                node.dot = '.';
                if(node.x == '\0')
                    node.x = 0;
            }

            if(isConvSpec(input[i])){
                node.convSpec = input[i++];
                return node;
            }
        } else if(input[i] == '\0'){
            node.eof_ = 1;
            i++;
            return node;
        }
        else {
            node.special = input[i++];
            return node;
        }
        i++;
    }
}

tnode createnode(){
    tnode node;
    node.x = 0;
    node.y = 0;
    node.convSpec = '\0';
    node.dot = '\0';
    node.escape = '\0';
    node.sign = '\0';
    node.eof_ = '\0';
    node.special = '\0';

    return node;
}

int isConvSpec(char c){
    switch(c){
        case 'd':
        case 'i':
        case 'u':
        case 'c':
        case 's':
        case 'p':
        case 'o':
        case 'x':
        case 'X':
        case 'e':
        case 'E':
        case 'f':
        case 'g':
        case 'G':
            return 1;
        default:
            return 0;
    }
}
