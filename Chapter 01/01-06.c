#include <stdio.h>

int main() {

	int c;	

	while (printf("Getchar != EOF = %d.\n\n", (c = getchar()) != EOF))
		;

	return 0;
}