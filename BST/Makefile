EXE = exe

#LFLAGS = -lblass
CXX = c++
CXXFLAGS = -I include -std=c++14 -Wall -Wextra

SRC = main.cc
OBJ = ${SRC:.cc=.o}

all: $(EXE)

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)


$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE) $(LFLAGS)

main.o: include/bst.hpp include/node.hpp 

#src/bst.o: include/bst.hpp

clean:
	rm -rf src/*.o main.o $(EXE) */*~ *~

.PHONY: clean all


