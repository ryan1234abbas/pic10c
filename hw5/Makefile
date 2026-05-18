CXX = g++
CXXFLAGS = -std=c++20 -O3

all: HW3.exe

HW3.exe: HW5.o
	$(CXX) $(CXXFLAGS) HW5.o -o HW3.exe

HW5.o: HW5.cpp binary_search_tree.h
	$(CXX) $(CXXFLAGS) -c HW5.cpp -o HW5.o

test: HW3.exe
	./HW3.exe

clean:
	rm -f HW5.o HW3.exe