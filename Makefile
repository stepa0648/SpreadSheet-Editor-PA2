CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic
LD=g++
LDFLAGS=-std=c++11 -Wall -pedantic

all: compile doc

compile: severste

severste: ./src/main.o ./src/CTable.o ./src/CCell.o ./src/CToken.o ./src/CMenu.o ./src/Math.o
	$(LD) $(LDFLAGS) ./src/main.o ./src/CTable.o ./src/CCell.o ./src/CToken.o ./src/CMenu.o ./src/Math.o -o severste

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: compile
	./severste

test:
	./severste < ./examples/in_0001.txt

doc: ./src/main.cpp ./src/CTable.cpp ./src/CCell.cpp ./src/CToken.cpp ./src/CMenu.cpp ./src/Math.cpp ./src/CTable.h ./src/CCell.h ./src/CToken.h ./src/CMenu.h ./src/Math.h
	doxygen ./src/Doxyfile

clean:
	rm -fR ./doc severste ./src/*.o *~ core

#automatically generated
CCell.o: ./src/CCell.cpp ./src/CCell.h ./src/Math.h ./src/CToken.h ./src/CTable.h
CMenu.o: ./src/CMenu.cpp ./src/CMenu.h
CTable.o: ./src/CTable.cpp ./src/CTable.h ./src/CCell.h ./src/CToken.h ./src/Math.h
CToken.o: ./src/CToken.cpp ./src/CToken.h
Math.o: ./src/Math.cpp ./src/CToken.h ./src/CTable.h ./src/CCell.h
main.o: ./src/main.cpp ./src/CMenu.h ./src/CTable.h ./src/CCell.h
