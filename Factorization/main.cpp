#include <chrono>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>
#include "BigInteger/BigIntegerLibrary.hh"
#include "Modular-Power.h"
#include "Miller-Rabin-Prime.h"
#include "Trial-Division.h"
#include "Pollard-Rho.h"
#include "Lenstra-ECM.h"

#pragma warning(suppress : 6387)

using namespace std;

void generate_number(int digits, char* string) {
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(0.0, 10.0); //range is 20 to 22

    int random = 0;
    for (int i = 0; i < digits; i++) {
        random = abs((int)dist(mt) % 10);
        while (i == 0 && random == 0) { // make sure the first bit is non-zero
            random = abs((int)dist(mt) % 10);
        }
        while (i == digits - 1 && random % 2 == 0) { // make sure the number is not even
            random = abs((int)dist(mt) % 10);
        }
        *(string + i) = random + '0';
    }
    *(string + digits) = '\0'; // add the end mark of this string
}

/*
   For different range of input, the most convincing way is to perform them with the same steps,
   meaning that it's better to add trial-division and pollard-rho to over 18-digit cases.
   
   It is possible that when the primality test suggests a number to be non-prime, but Lenstra cannot find its factor.
   In this case, we either execute more loops of Lenstra with the belief of it being non-prime, or follow the factorization result that it might be prime.
 */
int main() {
    //long long n = 10967535067;  // initial test
    long long criteria = 1000uL;
    std::chrono::duration<double> elapsed;
    
    // number that within the range of long long
    for (int i = 2; i <= 18; i++) {
        char* n_string = (char*)malloc((i + 1) * sizeof(char));
        generate_number(i, n_string);
        long long n = stoll(n_string);
        vector<long long> answer;
        cout << "n = " << n << " = ";

        auto start = std::chrono::high_resolution_clock::now();
        while (true && n != 1) {
            if (is_prime(n)) {
                answer.push_back(n);
                break;
            }

            long long factor = trial_division(n);
            if (factor == 0) {
                if (n < criteria) {
                    factor = pollard_rho(n);
                }
                else {
                    factor = ecm_longlong(n);
                }
            }

            answer.push_back(factor);
            n /= factor;
        }
        auto finish = std::chrono::high_resolution_clock::now();
        elapsed = finish - start;

        for (int i = 0; i < answer.size() - 1; i++) {
            cout << answer.at(i) << " * ";
        }
        cout << answer.at(answer.size() - 1) << " ";
        cout << "(" << elapsed.count() << "s)\n";

        free(n_string);
    }
    
    // number that has to use BigInteger
    for (int i = 19; i <= 40; i++) {
        char* n_string = (char*)malloc((i + 1) * sizeof(char));
        generate_number(i, n_string);
        BigInteger n = stringToBigInteger(n_string);
        cout << "n = " << n << " = ";
        BigInteger prev = n, next = 0;

        auto start = std::chrono::high_resolution_clock::now();
        while (true) {
            next = ecm_biginteger(prev);
            prev /= next;
            if (prev != 1) {
                cout << bigIntegerToString(next) << " * ";
            }
            else {
                cout << bigIntegerToString(next) << " ";
                break;
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();
        elapsed = finish - start;
        cout << "(" << elapsed.count() << "s)\n";

        free(n_string);
    }
}
