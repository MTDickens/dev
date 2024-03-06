#include <stdio.h>

void Series_Sum( double sum[] );

int main()
{
    int i;
    double x, sum[3001];
    
    Series_Sum( sum );

    x = 0.0;
    for (i=0; i<3001; i++)
        printf("%6.2f %16.12f\n", x + (double)i * 0.10, sum[i]);

    return 0;
}

/* Your function will be put here */






#include <math.h>

#define MAX_N 10
#define SOME_LARGE_M 100
#define LEN 3000
#define LEN_DIV_10 301

#define PI (3.141592653589793)

double pre_list[LEN_DIV_10];

void Series_Sum(double sum[])
{
    /**
     * Preprocessing
     */
    pre_list[0] = PI * PI / 6.0;

    for (int i = 1; i <= LEN_DIV_10 - 1; ++i)
    {
        for (int j = i; j >= 1; --j)
        {
            pre_list[i] += 1.0 / j;
        }
        pre_list[i] /= i;
        printf("pre_list[%d]: %16.12f\n", i, pre_list[i]);
    }

    /**
     * Iteration
     */

    /**
     * \sum_{k = 1}^{inf} 1 / (k * (k + x)) - pre_list[round]
     * = \sum_{k = 1}^{inf} 1 / (k * (k + x)) - \sum_{k = 1}^{inf} 1 / (k * (k + round))
     * = \sum_{k = 1}^{inf} (round - x) * 1 / (k * (k + round) * (k + x))
     * = (round - x) * \sum_{k = 1}^{inf} 1 / (k * (k + round) * (k + x))
     */

    /**
     * Correction = 
    */
    // double correction = 0.0;
    // for (int i = 10000000; i > 100000; i--) 
    // {
    //     correction += 1 / ((double)(i) * (double)(i) * (double)(i + 1)); 
    // }
    const int times = 20000; // m
    for (int i = 0; i <= LEN; ++i)
    {
        double num = i / 10.0; // a
        int round = num + 0.95; 
        double correction;

        #ifndef USE_NUM
        if (round != 0)
        {
            correction = log((double)(round + times) / times) / (round * round) - 1.0 / ((round + times) * round);
        }
        else
        {
            correction = 1.0 / (2 * times * times);
        }
        #endif
        #ifdef USE_NUM
        if (num != 0.0)
        {
            correction = log((double)(num + times) / times) / (num * num) - 1.0 / ((num + times) * num);
        }
        else
        {
            correction = 1.0 / (2 * times * times);
        }
        #endif

        double sum_i = correction;
        for (int j = times; j >= 1; j--)
        {
            sum_i += 1 / (((double)(j) * (double)(j + round)) * (double)(j + num));
        }
        sum_i *= (round - num);

        sum[i] = pre_list[round] + sum_i;

    }
}