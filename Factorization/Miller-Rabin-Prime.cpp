#include "Miller-Rabin-Prime.h"
#include "Modular-Power.h"
#include <time.h>
#include <cstdlib>

const int k = 10;

bool miller_rabin_test(long long d, long long n) {
    srand(time(NULL));
    long long a = 2 + rand() % (n - 4);  // make sure n > 4
    long long x = modular_pow(a, d, n);
    if (x == 1 || x == n - 1) {
        return true;
    }

    // Keep squaring x while one of the following doesn't happen
    // (i) d does not reach n-1
    // (ii) (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1) {
            return false;
        }
        if (x == n - 1) {
            return true;
        }
    }

    return false;
}

bool is_prime(long long n) {
    // edge cases, n <= 4
    if (n <= 1 || n == 4) {
        return false;
    }
    if (n <= 3) {
        return true;
    }

    // find r such that n = 2^d * r + 1 for some r >= 1
    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    for (int i = 0; i < k; i++) {
        if (!miller_rabin_test(d, n)) {
            return false;
        }
    }

    return true;
}
