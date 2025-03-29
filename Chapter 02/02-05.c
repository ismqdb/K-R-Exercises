#include <stdio.h>

int any(char s1[], char s2[]){
	for(int i = 0; s1[i] != '\0'; i++)
		for(int j = 0; s2[j] != '\0'; j++)
			if(s1[i] == s2[i])
				return i;
				
	return -1;
}

int main(int argc, char **argv)
{
	char s1[] = "Hello World";
	char s2[] = "Wrl";
	int x = any(s1, s2);
	
	switch(x){
		case -1:
			printf("No matches found");
			break;
		default:
			printf("Match found at index: %d.", x);
			break;
	}
}
