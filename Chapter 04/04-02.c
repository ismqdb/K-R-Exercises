#include <stdio.h>
#include <ctype.h>
#include <math.h>

/* atof: convert string s to double */
double atof(char s[]) {
	double val, power;
	int i, sign;

	char sciNotSign;
	char sciChars[20];
	double sciNotValue;

	for (i = 0; isspace(s[i]); i++)	/* skip whitespace */
		;

	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-') i++;

	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');

	if (s[i] == '.')
		i++;

	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}

	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		sciNotSign = (char)s[i];
		i++;

		int k;
		
		for (k = 0; s[i] != '\0'; k++, i++)
			sciChars[k] = s[i];

		sciChars[k] = '\0';

		sciNotValue = atof(sciChars);

		return (sign * val / power) * pow(10, sciNotValue * ((sciNotSign == '+') ? 1 : -1));
	}

	return sign * val / power;
}

int main() {
	double sum;

	sum = 0;
	char print[] = "\t%f\n";

	printf(print, sum += atof("125.121111e+3\0"));
	return 0;
}