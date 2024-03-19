#include <stdio.h>
#define MAXLINE 1000

void getinput(int row[]);
void nospace(int row[], int subrow[]);
void nonewline(int row[]);

int main(){
	int row[MAXLINE];
	int subrow[MAXLINE];
	
	getinput(row);
	nospace(row, subrow);
	nonewline(subrow);
}

void getinput(int row[]){
	int c;
	int i;
	
	for(i = 0; (c = getchar()) != EOF; ++i)
		row[i] = c;
		
	row[i] = '\0';
}

void nonewline(int row[]){
	int i;
	char pointer = 'n';
	
	for(i = 0; row[i] != '\0'; ++i){
		if(pointer == 'n' && row[i] != '\n')
			putchar(row[i]);
		else if(pointer == 'n' && row[i] == '\n'){
			putchar(10);
			pointer = 'y';
		}
		else if(pointer == 'y' && row[i] != '\n')
			putchar(row[i]);
		else
			;
	}
}

void nospace(int row[], int subrow[]){
	int i;
	char pointer = 'n';
	int k = 0;
	
	for(i = 0; row[i] != '\0'; ++i){
		if(row[i] == '\t')
			row[i] = ' ';
		
		if(pointer == 'n' && row[i] == ' ')
			;
		else if(pointer == 'n' && row[i] != ' '){
			subrow[k] = row[i];
			++k;
			pointer = 'y';
		} else if(pointer == 'y' && row[i] == ' '){
			subrow[k] = row[i];
			++k;
			pointer = 'n';
		} else if(pointer == 'y' && row[i] != ' '){
			subrow[k] = row[i];
			++k;
		}
	}
	subrow[k] = '\0';
}
