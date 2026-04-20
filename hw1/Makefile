COMPILER= g++
CFLAGS= -std=c++20 -O3
LINKER= $(COMPILER)
OBJ= prog
EXEC= main.o def1.o def2.o 

all: $(EXEC)
#compile
%.o : %.cpp H.h
	$(COMPILER) $(CFLAGS) -c $< -o $@
#link
 $(EXEC):$(OBJ)
	$(LINKER) -o $@ $^
#clean
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: clean