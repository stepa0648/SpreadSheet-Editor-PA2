CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic
LD=g++
LDFLAGS=-std=c++11 -Wall -pedantic

all: compile doc

compile: main.o CTable.o CCell.o CToken.o CMenu.o Math.o
	$(LD) $(LDFLAGS) main.o CTable.o CCell.o CToken.o CMenu.o Math.o -o severste

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	./severste

doc:
	doxygen Doxyfile

clean:
	rm -fR ./doc spreadsheet *.o *~ core

#automatically generated
CCell.o: CCell.cpp CCell.h Math.h CToken.h CTable.h
CMenu.o: CMenu.cpp CMenu.h
CTable.o: CTable.cpp CTable.h CCell.h CToken.h Math.h
CToken.o: CToken.cpp CToken.h
Math.o: Math.cpp CToken.h CTable.h CCell.h
main.o: main.cpp CMenu.h CTable.h CCell.h
