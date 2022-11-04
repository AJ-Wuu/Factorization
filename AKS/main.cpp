#include "AKS.h"
#include <chrono>
#include <future>
#include <inttypes.h>
#include <iostream>
#include <random>
#include <thread>
#include <vector>


using namespace std;
using std::chrono::duration;
using std::chrono::high_resolution_clock;
std::random_device rd;
std::mt19937 gen(rd());

uint64_t get_random(uint64_t min, uint64_t max) {
	std::uniform_int_distribution<uint64_t> distr(min, max); // define the range
	uint64_t n = distr(gen);

	int last_digit = n % 10;
	if (last_digit == 0 || last_digit == 2 || last_digit == 4 || last_digit == 5 || last_digit == 6 || last_digit == 8) { // even or multiple of 5
		n = get_random(min, max);
	}

	return n;
}

int main() {
	cout << "single thread to determine if a random number is prime or composite" << endl;
	uint64_t n = 2;
	bool prime = false;
	high_resolution_clock::time_point start, end;
	duration<double, std::milli> ms;

	for (int i = 1; i < 19; i++) {
		uint64_t temp = pow(10, i);
		n = get_random(temp, temp * 10);
		cout << n;

		start = high_resolution_clock::now();
		prime = is_prime(n);
		end = high_resolution_clock::now();
		if (prime) {
			cout << " is prime        ";
		}
		else {
			cout << " is composite    ";
		}

		ms = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
		cout << "Time taken: " << ms.count() << "ms" << endl;
	}

	/**********************************************************************************************************************************************/

	cout << "\n\nmultiple threads to get all the prime numbers within the limit" << endl;
	const uint64_t limit = 1000;
	const int numThreads = 5;
	vector<future<void>> threads;

	start = high_resolution_clock::now();
	for (int i = 0; i < numThreads; ++i) {
		threads.push_back(move(async(launch::async, [i]() {
			int start = i * limit / numThreads;
			int end = (i + 1) * (limit / numThreads);
			for (uint64_t j = start; j < end; ++j) {
				if (is_prime(j))
					printf("%" PRIu64 " ", j);
			}
		})));
	}

	for (int i = 0; i < threads.size(); ++i) {
		threads[i].wait();
	}

	end = high_resolution_clock::now();
	ms = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
	cout << "\nTime taken: " << ms.count() << "ms" << endl;
}
