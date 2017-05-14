CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic
LD=g++
LDFLAGS=-std=c++11 -Wall -pedantic

all: spreadsheet

spreadsheet: main.o CTable.o CCell.o CToken.o CMenu.o
	$(LD) $(LDFLAGS) main.o CTable.o CCell.o CToken.o CMenu.o -o spreadsheet
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
clean:
	rm -f spreadsheet *.o *~ core
	
#automatically generated
CCell.o: CCell.cpp CCell.h
CMenu.o: CMenu.cpp CMenu.h
CTable.o: CTable.cpp CTable.h CCell.h CToken.h
CToken.o: CToken.cpp CToken.h
main.o: main.cpp CMenu.h CTable.h CCell.h
