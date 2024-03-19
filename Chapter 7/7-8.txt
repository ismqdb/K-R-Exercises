#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFile(char*);

int main(){
	printFile("1.txt");
	printFile("2.txt");
}

void printFile(char* filePath){
	FILE *file = fopen(filePath, "r");

	if(file == NULL){
		fprintf(stderr, "Can't open file. Please try again.\n");
		exit(1);
	}

	putchar(10);
	putchar(10);

	unsigned lineCount = 1;
	char line[256];

	printf("\tFile name: %s.\n\n", filePath);
	while(fgets(line, sizeof(line), file)){
		printf("Line %d: %s", lineCount, line);
		lineCount++;
	}

	fclose(file);
}
