#include "Lenstra-ECM.h"
#include "Miller-Rabin-Prime.h"
#include "Pollard-Rho.h"
#include "Trial-Division.h"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    unsigned long long n = 10967535067; // integers between [0, 2^64)
    unsigned long long criteria = 100000000000uL;
    vector<unsigned long long> answer;
    cout << "n = " << n << " = ";

    while (true) {
        if (is_prime(n)) {
            answer.push_back(n);
            break;
        }

        unsigned long long factor = trial_division(n);
        if (factor == 0) {
            if (n < criteria) {
                factor = pollard_rho(n);
            } else {
                break;
                // factor = 1;  // ecm(n);
            }
        }

        answer.push_back(factor);
        n /= factor;
    }

    for (unsigned int i = 0; i < answer.size() - 1; i++) {
        printf("%lld * ", answer.at(i));
    }
    printf("%lld\n", answer.at(answer.size()-1));
}