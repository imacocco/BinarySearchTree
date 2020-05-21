EXE = test

#LFLAGS = -lblass
CXX = c++
CXXFLAGS = -I include -g -std=c++14 -Wall -Wextra

SRC = main.cc src/bst.cc
SRC_B = main_benchmark.cc src/bst.cc

OBJ = ${SRC:.cc=.o}
OBJ_B = ${SRC_B:.cc=.o}

LIB = include/bst.hpp include/node.hpp include/iterator.hpp
all: $(EXE) documentation benchmark

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)

benchmark: $(OBJ_B)
	$(CXX) $^ -o benchmark $(LFLAGS)	
	
$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE) $(LFLAGS)

documentation: Doxygen/doxy.in
	doxygen $^

main.o: $(LIB) 

src/bst.o: $(LIB)

clean:
	rm -rf src/*.o main.o $(EXE) */*~ *~ latex html

.PHONY: clean all documentation


