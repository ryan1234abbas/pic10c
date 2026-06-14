all: HW8

HW8: HW8.o
	g++ -std=c++20 -O3 -o HW8 HW8.o

HW8.o: HW8.cpp ls_set.h
	g++ -std=c++20 -O3 -c HW8.cpp

clean:
	rm -f HW8 HW8.o