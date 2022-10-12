#include <stdio.h>

#include <iostream>
#include <vector>

#include "Lenstra-ECM.h"
#include "Miller-Rabin-Prime.h"
#include "Pollard-Rho.h"
#include "Trial-Division.h"
#include "BigInteger/BigIntegerLibrary.hh"

using namespace std;

int main() {
    long long n = 10967535067;  // integers between [0, 2^64)
    long long criteria = 1000uL;
    vector<long long> answer;
    cout << "n = " << n << " = ";

    while (true) {
        if (is_prime(n)) {
            answer.push_back(n);
            break;
        }

        long long factor = trial_division(n);
        if (factor == 0) {
            if (n < criteria) {
                factor = pollard_rho(n);
            } else {
                factor = ecm(n);
            }
        }

        answer.push_back(factor);
        n /= factor;
    }

    for (int i = 0; i < answer.size() - 1; i++) {
        printf("%lld * ", answer.at(i));
    }
    printf("%lld\n", answer.at(answer.size() - 1));
}