#include <stdio.h>

int main() {

	int c, count = 0;

	while ((c = getchar()) != EOF)
		if (c == '\n' || c == '\t' || c == ' ')
			++count;

	printf("%d\n", count);

}