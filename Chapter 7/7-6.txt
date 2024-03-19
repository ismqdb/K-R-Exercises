#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *file1;
	FILE *file2;

	char *fpath1 = "./1.txt";
	char *fpath2 = "./2.txt";

	file1 = fopen(fpath1, "r");
	file2 = fopen(fpath2, "r");

	if(file1 == NULL || file2 == NULL){
		fprintf(stderr, "Can't open file. Try again.\n");
		exit(1);
	}

	unsigned line = 0;
	char c1;
	char c2;

	while(1){
		c1 = getc(file1);
		c2 = getc(file2);

		if(c1 == '\n' || c2 == '\n')
			line++;

		if(c1 != c2 || c1 == EOF || c2 == EOF){
			fprintf(stderr, "Mismatch at line %d.\n", line);
			break;
		}
	}

	return 0;
}
