# Makefile for files_demo

CXX = g++
CXXFLAGS = -std=c++17
TARGET = files_demo
SRC = files_demo.cpp
OBJ = $(SRC:.cpp=.o)

# Targets
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Phony targets
.PHONY: all clean

clean:
	rm -f $(OBJ) $(TARGET)
