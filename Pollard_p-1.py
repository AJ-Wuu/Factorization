# Pollard's p-1 Factorization Method

import math
import sympy


def pollard(n):
	# base
	a = 2
	# exponent
	k = 2
	
	# iterate until obtaining a prime factor
	while (True):
		# recompute a as required
		a = (a**k) % n
	
		# finde gcd of a-1 and n
		d = math.gcd((a-1), n)
	
		# check if factor is obtained
		if (d > 1):
			return d
	
		# increase exponent by one for next round
		k += 1


if __name__ == "__main__":
	n = 540143
	num = n
	prime_factors = []

	while (True):
		d = pollard(num)
		prime_factors.append(d)
		r = int(num/d)

		if (sympy.isprime(r)):
			prime_factors.append(r)
			break
		else:
			num = r
	
	print("Prime factors of", n, "are", *prime_factors)
