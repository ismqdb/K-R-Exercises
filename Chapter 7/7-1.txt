 
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void convert(char array[], int type){
    // type = 0 -> to lower, type = 1 -> to upper
    for(size_t i = 0; i < strlen(array); i++)
        if(!type)
            array[i] = tolower(array[i]);
        else
            array[i] = toupper(array[i]);
}

int main(int argc, char* argv[]){
    // argv should be toupper, tolower
    char array[100];
    char c = '.';

    for(int i = 0; c != EOF; i++){
        c = getchar();
        array[i] = c;
    }

    if(!strcmp(argv[0], "/home/ismqdb/Desktop/Programiranje/C/K&R C projects/tolower"))
        convert(array, 0);
    else if(!strcmp(argv[0], "toupper"))
        convert(array, 1);
    else {
        printf("Invalid program name. Try again.\n\n");
        exit(0);
    }

    printf("%s\n\n", array);

    return 0;
}
