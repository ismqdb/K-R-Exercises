#include <stdio.h>

#define MAXLINE 15

int main(){
	int c;
	int wlen[MAXLINE];				// array that stores word lenght;
	int i;
	int wordln = 0;					// lenght of the current word
	char pointer = 'n';				// if pointer == 'y', we are in the word
	
	for(i = 0; i < MAXLINE; ++i)
		wlen[i] = 0;
	
	while((c = getchar()) != EOF){
		if(c != ' ' && c != '\t' && c != '\n' && pointer == 'n'){
			++wordln;
			pointer = 'y';
		}
		else if((c == ' ' || c == '\t' || c == '\n') && pointer == 'y'){
			pointer = 'n';
			++wlen[wordln];
			wordln = 0;
		}
		
		else if((c == ' ' || c == '\t' || c == '\n') && pointer == 'n');

		else if(c != ' ' && c != '\t' && c != '\n' && pointer == 'y')
			++wordln;
	}
	
	// baskets[0]: words with 0-3 lenght
	// baskets[1]: words with 4-6 lenght
	int baskets[6] = {0, 0, 0, 0, 0, 0};
	
	for(i = 0; i < MAXLINE; ++i){
		if(i < 3)
			baskets[0] += wlen[i];
		else if(i < 6)
			baskets[1] += wlen[i];
		else if(i < 9)
			baskets[2] += wlen[i];
		else if(i < 12)
			baskets[3] += wlen[i];
		else if(i < 15)
			baskets[4] += wlen[i];
		else if(i >= 15)
			baskets[5] += wlen[i];
	}
	
	putchar(10);
	putchar(10);
	
	for(i = 0; i < 6; ++i){
		if(i == 0)
			printf("00 - 03");
		else if(i == 1)
			printf("04 - 06");
		else if(i == 2)
			printf("07 - 09");
		else if(i == 3)
			printf("10 - 12");
		else if(i == 4)
			printf("13 - 15");
		else 
			printf("  >= 15");
			
		printf("   ");
		
		int k;
		
		for(k = 0; k < baskets[i]; ++k)
			putchar('*');
		
		putchar(10);
	}
	
}

















