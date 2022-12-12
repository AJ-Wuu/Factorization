#ifndef MPQS_H
#define MPQS_H

#include <gmp.h>

typedef signed long long int sint64_t;

typedef struct ARRAYS *ARRAYS_PT;

typedef struct ARRAYS {
	sint64_t num_of_primes;
	sint64_t *factors, *exponents;
} ARRAYS_T[1];

void sieve_of_eratothenes(ARRAYS_PT ARRS, int n);
void calc_nullspace(ARRAYS_PT ARRS, sint64_t **arr, sint64_t fbsize);
void evaluate_nullspace(mpz_t n, mpz_t *kArr, mpz_t *lArr);
int mpz_sqrt_mod_p(mpz_t q, const mpz_t n, const mpz_t p);
int mpz_sqrt_mod_pe(mpz_t q, const mpz_t a, const mpz_t p, const int e);
void mpqs(mpz_t n, sint64_t M, sint64_t FBBOUND, sint64_t THRESHOD);

#endif

