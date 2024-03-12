#include <stdio.h>
#include <math.h>

#define ZERO 1e-13 /* X is considered to be 0 if |X|<ZERO */
#define MAXN 11    /* Max Polynomial Degree + 1 */

double Polynomial_Root(int n, double c[], double a, double b, double EPS);

int main()
{
    int n;
    double c[MAXN], a, b;
    double EPS = 0.00005;
    int i;

    scanf("%d", &n);
    for (i = n; i >= 0; i--)
        scanf("%lf", &c[i]);
    scanf("%lf %lf", &a, &b);
    printf("%.4f\n", Polynomial_Root(n, c, a, b, EPS));

    return 0;
}

/* Your function will be put here */

/**
 * Sample Input:
 * 2 1 1.5 -1
 * 0 2
 *
 * Sample Output:
 * 0.5000
 */
double Polynomial_Root(int n, double c[], double a, double b, double EPS)
{
    return 0.0;
}
