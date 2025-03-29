#include <stdio.h>

#define swap(t, x, y) t temp; \
		temp = x; \
		x = y; \
		y = temp;

int main() {
	char x = 'a', y = 'b';
	swap(char, x, y);

	printf("%c %c", x, y);
}