CXX = g++
CXXFLAGS = -std=c++20 -O3

all: HW6P2

HW6P2: HW6P2.o
	$(CXX) $(CXXFLAGS) HW6P2.o -o HW6P2

HW6P2.o: HW6P2.cpp array_template.h selection_sort_template.h
	$(CXX) $(CXXFLAGS) -c HW6P2.cpp -o HW6P2.o

clean:
	@rm -f HW6P2.o HW6P2
