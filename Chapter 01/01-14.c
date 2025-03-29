#include <stdio.h>

int main(){
	int c;
	int ccount[26];
	
	int i;
	
	for(i = 0; i < 26; ++i)
		ccount[i] = 0;
	
	while((c = getchar()) != EOF){
		if(c >= 'a' && c <= 'z')
			++ccount[c - 'a'];
		else if(c >= 'A' && c <= 'Z')
			++ccount[c - 'A'];
	}
		
	putchar(10);
	putchar(10);
	putchar('\t');
	
	for(i = 0; i < 26; ++i){
		putchar(i+97);
		putchar('|');
	}
	
	putchar(10);
	putchar('\t');
	
	for(i = 0; i < 26; ++i){
		putchar('-');
		putchar('|');
	}
	
	putchar(10);
	putchar('\t');	
	for(i = 0; i < 26; ++i){
		printf("%d", ccount[i]);
		putchar('|');
	}
}
