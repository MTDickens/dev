#include <stdio.h>

#define MAX_N 2
#define SOME_LARGE_M 100000
#define LEN 3001

double inv_psi_list[MAX_N + 1];

void Series_Sum(double sum[]);
double phi_approx(double x, int n, int m);
double phi1(double x);

int main()
{
    int i;
    double x, sum[LEN + 1];

    Series_Sum(sum);

    x = 0.0;
    // for (i = 0; i < LEN + 1; i++)
    //     printf("%6.2lf %16.12lf\n", (double)x + (double)i * 0.10, (double)sum[i]);

    printf("%6.2lf %16.12lf\n", (double)0 + (double)0.1 * 3000, 1+ (1-300) * phi_approx(300, 2, SOME_LARGE_M));
    return 0;
}

/**
 * phi(x, n, m) = \sum_{k = 1}^{m} 1 / ((k + x) * \prod_{j = 0}^{n - 1} (k + j))
 */
double phi_approx(double x, int n, int m)
{
    double ret_val = 0;
    for (int k = m; k >= 1; --k)
    {
        double kth = 1;
        for (int j = 0; j <= n - 1; ++j)
            kth *= k + j;
        kth *= k + x;
        ret_val += 1 / kth;
    }

    return ret_val;
}

/**
 * phi(x, n) = \sum_{k = 1}^{infty} ((k + x) * \prod_{j = 0}^{n - 1} (k + j))
 * phi(x, n) = (n - x) * phi(x, n + 1) + 1 / (n * factorial(n)) [n < MAX_N]
 * phi(x, n) <= phi_approx(x, n, SOME_LARGE_M) [n == MAX_N]
 */
double phi(double x, int n)
{
    double ret_val = phi_approx(x, MAX_N, SOME_LARGE_M);
    for (int i = MAX_N - 1; i >= n; --i)
    {
        // phi(x, i) = (i - x) * phi(x, i + 1) + 1 / (i * factorial(i)) = (i - x) * phi(x, i + 1) + inv_psi_list[i]
        ret_val = (i - x) * ret_val + 1.0 / inv_psi_list[i];
    }
    return ret_val;
}

double phi1(double x)
{
    return phi(x, 1);
}

void Series_Sum(double sum[])
{
    /**
     * Initialize psi list
     * inv_psi_list[n] = 1 / (\sum_{k = 1}^{infty} (\prod_{j = 0}^{n} (k + j))) = 1 / (1 / (n * fact(n))) = n * fact(n)
     */
    inv_psi_list[0] = 1.0;
    for (int i = 1; i <= MAX_N; ++i)
        inv_psi_list[i] = inv_psi_list[i - 1] * i;
    for (int i = 0; i <= MAX_N; ++i)
        inv_psi_list[i] *= i;

    /**
     * Iteration
    */
    for (int i = 0; i < LEN + 1; i++)
        sum[i] = phi1(i * 0.1);
}