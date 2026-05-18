CXX = g++
CXXFLAGS = -std=c++14 -O3

all: HW6P1

HW6P1: HW6P1.o
	$(CXX) $(CXXFLAGS) HW6P1.o -o HW6P1

HW6P1.o: HW6P1.cpp do_for_each_template.h
	$(CXX) $(CXXFLAGS) -c HW6P1.cpp -o HW6P1.o

clean:
	@rm -f HW6P1.o HW6P1
