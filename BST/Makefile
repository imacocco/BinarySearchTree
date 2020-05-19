EXE = exe

#LFLAGS = -lblass
CXX = c++
CXXFLAGS = -I include -g -std=c++14 -Wall -Wextra

SRC = main.cc src/bst.cc
OBJ = ${SRC:.cc=.o}
LIB = include/bst.hpp include/node.hpp include/iterator.hpp
all: $(EXE)

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)


$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE) $(LFLAGS)

main.o: $(LIB) 

src/bst.o: $(LIB)

clean:
	rm -rf src/*.o main.o $(EXE) */*~ *~

.PHONY: clean all


