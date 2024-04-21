// Реализовать программу 1-го практического задания с помощью биномиального коэффициента.

#include <stdio.h>

int binom(int n, int k)
{
    double res = 1;
    for (int i = 1; i <= k; ++i)
        res = res * (n - k + i) /
              i;
    return (int)(res + 0.01);
}

int main()
{
    int n, k;
    printf("Enter N and K :\n");
    scanf("%d %d", &n, &k);
    printf("%d\n", binom(n , k));

    return 0;
}
