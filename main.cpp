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

//Smazat
//#include "Math.h"

#define END 0
#define PRINT 1
#define INSERT 2
#define PRINTCELL 3
#define HELP 4

using namespace std;

/**
  \class InvalidCoords
  Class that is thrown when user inputs invalid coords for example negative coords or NaN coords
*/
class InvalidCoords: public exception{
public:
virtual const char * what() const noexcept{
  return "Neplatne souradnice";
}
};


void getCoords(int & y, int & x){

  cout << "Zadejte cislo radku: ";

  cin >> y;
  if(cin.fail()){
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    throw InvalidCoords();
  }
  cin.ignore(INT_MAX, '\n');

  if( y < 0 || y > 500000 ){
    throw InvalidCoords();
  }

  cout << "Zadejte cislo sloupce: ";

  cin >> x;
  if(cin.fail()){
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    throw InvalidCoords();
  }
  cin.ignore(INT_MAX, '\n');

  if( x < 0 || x > 500000 ){
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
      cout << ">";
      int choice = menu.getInput();
      if( choice == 1 ){
        break;
      }else if( choice == 2 ){
        menu.printHelp();
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
      cout << ">";
      choice = inputHandler();
      error = false;

      // PRINT =================================================================
      if( choice == PRINT ){
        cout << "Vypis tabulky:" << endl;
        cout << "max souradnice: 499 990" << endl;
        try{
          getCoords(y,x);
        }catch( const exception & excp){
        	cerr << excp.what() << endl;
        	error = true;
        }
        if(y > 499990 || x > 499990){
          cout << "Neplatne souradnice" << endl;
          error = true;
        }
        if(!error){
          table.print(y,x);
        }

      // INSERTION =============================================================
      }else if( choice == INSERT){
        cout << "Vlozeni hodnoty do bunky:" << endl;
        cout << "max souradnice: 500000" << endl;
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

      // PRINT CELL ============================================================
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

      // HELP ==================================================================
      }else if(choice == HELP){
        menu.printHelp();

      // END ===================================================================
      }else if( choice == END){
        break;
      }
    }
    cout << "Konec" << endl;

    return 0;
}
