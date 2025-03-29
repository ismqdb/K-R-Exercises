#include <stdio.h>
#include <syscall.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>

#ifdef cat
#undef cat
#endif

void filecopy(FILE*, FILE*);
void filecop2(int, int);

int cat(int argc, char *argv[]){
	FILE *fp1;
	FILE *fp2;

	if(argc == 1)
		filecopy(stdin, stdout);
	else
		while(--argc > 0){
			if((fp1 = fopen(*++argv, "r")) == NULL || (fp2 = fopen(*++argv, "r")) == NULL){
				printf("cat: can't open %s.\n", *argv);
				return 1;
			} else {
				filecopy(fp1, fp2);
				fclose(fp1);
			}
			return 0;
		}
}

int ct2(int argc, char *argv[]){
	int ifd;
	int ofd;

	if(argc == 1)
		filecop2(0, 1);
	else
		while(--argc > 0){
			if((ifd = open(*++argv, O_RDONLY, 0)) == -1 || (ofd = open(*++argv, O_RDWR, 0)) == -1){
				fprintf("Cat: can't open %s.\n", *argv);
				return 1;
			} else {
				filecop2(ifd, ofd);
				close(ifd);
				close(ofd);
				return 0;
			}
		}
}

void filecopy(FILE *ifp, FILE *ofp){
	int c;

	while((c = getc(ifp)) != EOF)
		putc(c, ofp);
}

void filecop2(int ifd, int ofd){
	char c;
	int res;

	while((res = read(ifd, &c, 1)) > 0)
		write(ofd, (const void*)&c, 1);
}

int main(int argc, char *argv[]){
	clock_t start1, end1;
	double dif1;

	start1 = clock();
	cat(argc, argv);
	end1 = clock();
	dif1 = (float)(end1 - start1) / CLOCKS_PER_SEC;

	clock_t start2, end2;
	double dif2;

	start2 = clock();
	ct2(argc, argv);
	end2 = clock();
	dif2 = (float)(end2 - start2) / CLOCKS_PER_SEC;

	printf("Cat1: %f\nCat2: %f\n", dif1, dif2);
}
