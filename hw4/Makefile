COMPILER=g++
EXEC=HW4.exe
CXXFLAGS=-std=c++20 -O3
OBJ= HW4.o red_black_tree.o

all: $(EXEC)
%.o:%.cpp binary_search_tree.h
	$(COMPILER) $(CXXFLAGS) -c $< -o $@
$(EXEC):$(OBJ)
	$(COMPILER) $(CXXFLAGS) -o $@ $^

test: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(EXEC) $(OBJ)

