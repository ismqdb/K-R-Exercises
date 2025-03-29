#include <stdio.h>

#define ARRAYLEN 500

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;

    unsigned numOfIterations = 0;

    while (low <= high) {
        numOfIterations++;
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid + 1;
        else if (x > v[mid])
            low = mid + 1;
        else {
            printf("Num of iterations:%d.\n", numOfIterations);
            return mid;
        }
    }

    return -1;
}

/* Modified bin search*/
int binsearch_m(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;

    unsigned numOfIterations = 0;
    mid = (low + high) / 2;

    while (low <= high && x != v[mid]) {
        numOfIterations++;
        if (x < v[mid])
            high = mid + 1;
        else
            low = mid + 1;
        mid = (low + high) / 2;
    }

    printf("Num of iterations:%d.\n", numOfIterations);
    return (x == v[mid]) ? mid : -1;
}

int main() {
    int v[ARRAYLEN];
    for (int i = 0; i < ARRAYLEN; i++)
        v[i] = i * 10;

    printf("%d\n", binsearch(390, v, ARRAYLEN));
    printf("%d\n", binsearch_m(390, v, ARRAYLEN));
}

