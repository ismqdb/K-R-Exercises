#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
	if (year <= 0)
		return 0;

	if (month > (*daytab)[12] || month <= (*daytab)[0])
		return 0;

	if (day <= (*daytab)[0] || day > (*daytab)[12])
		return 0;

	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	if (leap && day > (*daytab)[15])
		return 0;

	if (!leap && day > (*daytab)[14])
		return 0;

	for (i = 1; i < month; i++)
		day += (*daytab)[13*leap+i];

	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int* pmonth, int* pday) {
	if (year <= 0 || yearday <= 0) {
		*pmonth = 0;
		*pday = 0;
		return;
	}

	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	for (i = 1; yearday > (*daytab)[13*leap+i]; i++)
		yearday -= (*daytab)[13*leap+i];

	*pmonth = i;
	*pday = yearday;
}

int main() {
	int year = 2000, month = 3, day = 24;

	int m, d;

	printf("day of year = %d\n", day_of_year(year, month, day));
	month_day(2000, 265, &m, &d);

	printf("month_day = %d.%d\n", m, d);

}