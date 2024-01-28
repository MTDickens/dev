#include <stdio.h>
#include <time.h>

#define ROWS 10
#define COLS 100000
#define TOT_TIME 1000

int main() {
    int arr[ROWS][COLS];

    // Good locality code
    int good_sum = 0;
    clock_t good_local_start, good_local_end;
    good_local_start = clock();
    for (int times = 0; times < TOT_TIME; ++times)
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                good_sum += arr[i][j];
            }
        }
    good_local_end = clock();

    // Bad locality code
    int bad_sum = 0;
    clock_t bad_local_start, bad_local_end;
    bad_local_start = clock();
    for (int times = 0; times < TOT_TIME; ++times)
        for (int j = 0; j < COLS; j++) {
            for (int i = 0; i < ROWS; i++) {
                bad_sum += arr[i][j];
            }
        }
    bad_local_end = clock();

    // print the times
    printf("Good locality code time: %f seconds\n", (double)(good_local_end - good_local_start) / CLOCKS_PER_SEC);
    printf("Bad locality code time: %f seconds\n", (double)(bad_local_end - bad_local_start) / CLOCKS_PER_SEC);

    return 0;
}