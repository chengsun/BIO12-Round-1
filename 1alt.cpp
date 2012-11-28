#include <iostream>
using namespace std;

/* this uses the same idea as a prime sieve */

/* distinctProd[i] gives the distinct prime product of i */ 
long distinctProd[1000001] = {};
/* freqSums[p] contains how many numbers i have a distinctProd[i] = p*/
long freqSums[1000001] = {};

void init()
{
    /* each integer starts with a product of 1 */
    for (long i = 1; i <= 1000000; ++i) {
        distinctProd[i] = 1;
    }
    /* then, for each possible prime factor i, we multiply distinctProd by it
     * for every number that has that prime factor. */
    for (long i = 2; i <= 1000000; ++i) {
        /* we know it's prime if the distinctProd is still 1 */
        if (distinctProd[i] == 1) {
            for (long j = i; j <= 1000000; j += i) {
                distinctProd[j] *= i;
            }
        }
    }
}

void a()
{
    int number;
    cin >> number;
    cout << distinctProd[number] << endl;
    return;
}

void c()
{
    /* we look for the most frequent distinctProd */
    for (long i = 1; i <= 1000000; ++i) {
        ++freqSums[distinctProd[i]];
    }
    long maxSum = 0, maxI = -1;
    for (long i = 1; i <= 1000000; ++i) {
        if (freqSums[distinctProd[i]] > maxSum) {
            /* this is the new maximum */
            maxSum = freqSums[distinctProd[i]];
            maxI = i;
        }
    }

    cout << distinctProd[maxI] << endl;
}

int main()
{
    init();
    a();
    /* call c(); instead if we want to find the answer to part c) */
    return 0;
}
