/*
 * File:   main.cpp
 * Author: severste
 *
 * Created on April 9, 2017, 10:55 AM
 */

#include "CMenu.h"
#include "CTable.h"
#include "CCell.h"
#include <climits>
#include <exception>

#define END 0
#define PRINT 1
#define INSERT 2
#define PRINTCELL 3
#define HELP 4

using namespace std;

class InvalidCoords: public exception{
public:
virtual const char * what() const noexcept{
  return "Invalid Coordinates";
}
};

void getCoords(int & y, int & x){
  cout << "Zadejte cislo radku: ";
  cin >> y;
  cout << "Zadejte cislo sloupce: ";
  cin >> x;
  cin.ignore(INT_MAX, '\n');
  if( y < 0 || x < 0 ){
    throw InvalidCoords();
  }
}

int inputHandler(){
  char x;
  cin >> x;
  cin.ignore(INT_MAX, '\n');

  switch (x) {
    case 'p': return PRINT; break;
    case 'i': return INSERT; break;
    case 'c': return PRINTCELL; break;
    case 'h': return HELP; break;
    case 'q': return END; break;
    default: cout << "Zadejte platne hodnoty. Stisknete h pro napovedu" << endl; return -1;
  }

  return -1;
}

/*
 *
 */
int main(int argc, char** argv) {
    CMenu menu;

    menu.printHeader();
    menu.printMenu();
    while(1){
      int choice = menu.getInput();
      if( choice == 1 ){
        break;
      }else if( choice == 2 ){
        menu.printInfo();
        menu.printMenu();
      }else{
        cout << "Konec" << endl;
        return 0;
      }
    }

    CTable table;
    int choice;
    int x, y;
    string str;
    bool error = false;

    menu.printHelp();
    while(1){

      choice = inputHandler();
      error = false;

      if( choice == PRINT ){
        cout << "Vypis tabulky:" << endl;
        try{
          getCoords(y,x);
        }catch( const exception & excp){
        	cerr << excp.what() << endl;
        	error = true;
        }
        if(!error){
          table.print(y,x);
        }
      }else if( choice == INSERT){
        cout << "Vlozeni hodnoty do bunky:" << endl;
        try{
          getCoords(y,x);
        }catch( const exception & excp){
        	cerr << excp.what() << endl;
        	error = true;
        }

        if(!error){
          cout << "Zadejte text: ";
          getline(cin, str); /** get text from user*/

          table.insert(y,x,str);
        }

      }else if(choice == PRINTCELL){
        cout << "Vypis hodnoty bunky:" << endl;
        try{
          getCoords(y,x);
        }catch( const exception & excp){
        	cerr << excp.what() << endl;
        	error = true;
        }
        if(!error){
          cout << "Bunka(" << y << "," << x <<"): ";
          table.getCell(y,x).printContent(table);
        }
      }else if(choice == HELP){
        menu.printHelp();
      }else if( choice == END){
        break;
      }
    }
    cout << "Konec" << endl;
    return 0;
}
