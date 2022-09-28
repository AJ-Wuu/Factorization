#include "Trial-Division.h"

unsigned long long trial_division(unsigned long long initial_value) {
    int factors[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    for (unsigned int i = 0; i < sizeof(factors) / sizeof(int); i++) {
        if (initial_value % factors[i] == 0) {
            return (unsigned long long)factors[i];
        }
    }
    return 0;
}