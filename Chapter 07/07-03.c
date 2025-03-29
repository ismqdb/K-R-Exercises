#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

// format: %(+/-)x.yf

typedef struct tnode {
    int x;
    int y;
    char dot;
    char sign;
    char convSpec;
    char escape;
    char eof_;
} tnode;

tnode parseformat(char input[]);
int isescape(char c);
int isConvSpec(char c);

tnode createnode();

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;

    tnode node;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */

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
                ival = va_arg(ap, int);
                if(node.sign == '+'){
                    if(node.dot != '.')
                        printf("%+*d", node.x, ival);
                    else
                        printf("%+*.*d", node.x, node.y, ival);
                } else {
                    if(node.dot != '.')
                        printf("%-*d", node.x, ival);
                    else
                        printf("%-*.*d", node.x, node.y, ival);
                }
                break;
            case 'f':
                break;
            case 's':
                for(sval = va_arg(ap, char*); *sval; sval++)
                    putchar(*sval);
                break;
            default:
                putchar(node.escape);
                break;
        }
    }

    va_end(ap); /* clean up when done */
}

int main(){
    minprintf("%s %s\t%d\n", "string", "minprintf", 25);
}

tnode parseformat(char input[]){
    tnode node = createnode();
    static int i = 0;

    if(input[i] != '%' && input[i] != ' ' && !isescape(input[i])){
        errno = EIO;
    }

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
            node.escape = input[i++];
            return node;
        }
        i++;
    }
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

tnode createnode(){
    tnode node;
    node.x = 0;
    node.y = 0;
    node.convSpec = '\0';
    node.dot = '\0';
    node.escape = '\0';
    node.sign = '\0';
    node.eof_ = '\0';

    return node;
}

int isescape(char c){
    switch((int)c){
        case 0x07:
        case 0x08:
        case 0x1B:
        case 0x0C:
        case 0x0A:
        //case 0x0D:
        case 0x09:
        case 0x0B:
        case 0x5C:
        case 0x27:
        case 0x22:
        case 0x3F:
            return 1;
        default:
            return 0;
    }
}
