#include "Pollard-p-1.h"
#include <stdio.h>
#include <iostream>
#include <cmath>

typedef unsigned long long ull;

ull gcd(ull a, ull b) {
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

long double dmod(long double x, long double y) {
    long long int temp = x / y;
    long double fraction = temp * y;
    std::cout << x - fraction << std::endl;
    return (x - fraction);
}

ull pollard(ull n) {
    long double a = 2;
    long double i = 2;
    while (true) {
        long double temp = pow(a, i);
        std::cout << temp << std::endl;
        a = dmod(temp, n);

        ull d = gcd(a - 1, n);
        if (d > 1) {
            return d;
        }

        i += 1;
    }
}