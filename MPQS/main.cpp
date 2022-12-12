#include "MPQS.h"
#include <gmp.h>
#include <chrono>
#include <cstdio>
#include <cmath>
#include <iostream>

#define M 10000
#define FBBOUND 1000
#define THRESHOLD 15

using namespace std;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

int main() {
    high_resolution_clock::time_point start, end;
    start = high_resolution_clock::now();
    mpz_t n;
    mpz_init_set_str(n, "6241019306901997355512619014111", 10);
    //mpz_init_set_str(n, "68397633165470058274884361378645822467587248043012077070501", 10);
    mpqs(n, M, FBBOUND, THRESHOLD);
    end = high_resolution_clock::now();
    cout << std::chrono::duration_cast<duration<double, std::milli>>(end - start).count() << endl;
}

