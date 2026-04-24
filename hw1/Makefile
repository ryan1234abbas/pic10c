compiler=g++
cxxflags=-std=c++17 -O3
exec=prog
obj= main.o def1.o def2.o

all: $(exec)

%.o:%.cpp H.h
	$(compiler) $(cxxflags) -c $< -o $@

$(exec): $(obj)
	$(compiler) $(cxxflags) -o $@ $^
clean:
	rm -f $(obj) $(exec)