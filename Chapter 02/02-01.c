#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

double calculateLowerLimit(int bits) {
	return -(pow(2, bits - 1));
}

double calculateUpperLimit(int bits) {
	return (pow(2, bits - 1) - 1);
}

double calculateUnsigned(int bits) {
	return pow(2, bits) - 1;
}

float calculateFloat(int sign) {
	if(sign == 0)
		return pow(2, 127) * 1.9999998807907104;
	else if(sign == 1)
		return pow(2, -126) * 1;
}

double calculateDouble(int sign) {
	if(sign == 0)
		return pow(2, 1023) * (1 + (1 - pow(2, -52)));
	else if(sign == 1)
		return pow(2, -1022) * (1 - pow(2, -52));
}

void limitsFromHeaders() {
	printf("Limits from headers:\n");
	printf("Signed char:\t%d - %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("Unsigned char:\t%d\n", UCHAR_MAX);
	printf("Signed short:\t%d - %d\n", SHRT_MIN, SHRT_MAX);
	printf("Unsigned short:\t%d\n", USHRT_MAX);
	printf("Signed int:\t%d - %d\n", INT_MIN, INT_MAX);
	printf("Unsigned int:\t%u\n", UINT_MAX);
	printf("Signed long:\t%d - %d\n", LONG_MIN, LONG_MAX);
	printf("Unsigned long:\t%u\n", ULONG_MAX);

	printf("Float:\t\t%.10e% - .10e\n", FLT_MIN, FLT_MAX);
	printf("Double:\t\t%.10e% - .10e\n", DBL_MIN, DBL_MAX);

	printf("\n");
}

void calculateLimits() {
	int bitsNeeded = 0;

	int schar_min = calculateLowerLimit(8);
	int schar_max = calculateUpperLimit(8);
	int uchar = calculateUnsigned(8);

	int short_min = calculateLowerLimit(16);
	int short_max = calculateUpperLimit(16);
	int ushort = calculateUnsigned(16);

	int int_min = calculateLowerLimit(8 * sizeof(signed int));
	int int_max = calculateUpperLimit(8 * sizeof(signed int));
	unsigned int uint = calculateUnsigned(8 * sizeof(unsigned int));

	long long_min = calculateLowerLimit(32);
	long long_max = calculateUpperLimit(32);
	unsigned long ulong = calculateUnsigned(32);

	float float_min = calculateFloat(1);
	float float_max = calculateFloat(0);

	double double_min = calculateDouble(1);
	double double_max = calculateDouble(0);


	printf("Limits from calculations:\n");
	printf("Signed char:\t%d - %d\n", schar_min, schar_max);
	printf("Unsigned char:\t%d\n", uchar);
	printf("Signed short:\t%d - %d\n", short_min, short_max);
	printf("Unsigned short:\t%d\n", ushort);
	printf("Signed int:\t%d - %d\n", int_min, int_max);
	printf("Unsigned int:\t%u\n", uint);
	printf("Signed long:\t%d - %d\n", long_min, long_max);
	printf("Unsigned long:\t%u\n", ulong);

	printf("Float:\t\t%.10e - %.10e\n", float_min, float_max);
	printf("Double:\t\t%.10e - %.10e\n", double_min, double_max);
}

int main() {
	limitsFromHeaders();
	calculateLimits();
}