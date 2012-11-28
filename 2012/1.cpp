/* simple algorithm to loop through possible factors
 *
 * see 1alt.cpp for an alternative "sieve" algorithm that can solve part c)
 * efficiently
 *
 * the longest it can take is number/2 iterations. Half a million iterations of
 * simple operations will fit into a second comfortably for C++ code
 */

#include <iostream>
using namespace std;

/* global variables are bad in all code, except programming contests, where
 * you can use globals liberally.
 */
long number, factor, result = 1;

void test_factor() {
    if (number % factor == 0) {
        do {
            number /= factor;
        } while (number % factor == 0);
        result *= factor;
    }
}

int main() {
    cin >> number;

    factor = 2;
    test_factor();

    factor = 3;
    while (number > 1) {
        test_factor();

        // we can safely test odd factors only, after we've tested 2.
        factor += 2;
    }

    cout << result << endl;
    return 0;
}
