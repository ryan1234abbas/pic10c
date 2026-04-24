COMPILER=g++
EXEC=HW2.exe
CXXFLAGS=-std=c++20 -O3
OBJ= HW2.o hashtable.o

all: $(EXEC)

%.o:%.cpp hashtable.h
	$(COMPILER) $(CXXFLAGS) -c $< -o $@
$(EXEC):$(OBJ)
	$(COMPILER) $(CXXFLAGS) -o $@ $^

test: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(EXEC) $(OBJ)