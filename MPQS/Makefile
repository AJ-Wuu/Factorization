all: mpqs
	./mpqs

mpqs: main.cpp MPQS.cpp
	g++ -O3 main.cpp MPQS.cpp -Wall -lgmp -lm -o mpqs -fopenmp
