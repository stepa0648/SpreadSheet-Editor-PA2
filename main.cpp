/**
 * \file main.cpp
 * \author severste
 * \date April 9, 2017, 10:55 AM
   \brief This is the mainfile of this project

   \mainpage Simple Spreadsheet Editor
   Simple Spreadsheet editor
 */

#include "CMenu.h"
#include "CTable.h"
#include "CCell.h"
#include <climits>
#include <exception>

/**
  \def END
   \brief END is constant that returns inputHandler if user whishes to end program
*/
#define END 0
/**
\def PRINT
 \brief PRINT is constant that returns inputHandler if user whishes to print table
*/
#define PRINT 1
/**
\def INSERT
\breif INSERT is constant that returns inputHandler if user whishes to insert into cell
*/
#define INSERT 2
/**
\def PRINTCELL
\brief PRINTCELL is constant that returns inputHandler if user whishes to print whole cell
*/
#define PRINTCELL 3
/**
\def HELP
\brief HELP is constant that returns inputHandler if user whishes to print the help
*/
#define HELP 4
/**
\def START
\brief START is constant that returns getInput if user whishes to start table
*/
#define START 5

using namespace std;

/**
  \class InvalidCoords
  \brief Class is used to be throw as an exception when user inputs invalid coords for example negative coords or NaN coords
*/
class InvalidCoords: public exception{
public:
virtual const char * what() const noexcept{
  return "Neplatne souradnice";
}
};


/**
  @brief getCoords is used to get coords of cell to specific operation
  @param y is number of a row
  @param x is number of a column
*/
void getCoords(int & y, int & x){

  cout << "Zadejte cislo radku: ";
  cin >> y;
  // if the input wasnt int throw exception
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
  // if the input wasnt int throw exception
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

/**
  \brief inputHandler is used to handle user inputHandler
  @return constant defined in this file, for example if user wants to print table it return PRINT
*/
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

/**
  \brief printTable is used to print a table
  CTable cannot be const because it also resizes the table if the printable area is out of table
  @param table, that will be printed out
*/
void printTable(CTable & table){
  int x, y;
  bool error = false;
  cout << "Vypis tabulky:" << endl;
  cout << "max souradnice: 499 990" << endl;
  try{
    getCoords(y,x);
  }catch( const exception & excp){
    cerr << excp.what() << endl;
    error = true;
  }
  if( !error && (y > 499990 || x > 499990)){
    cout << "Neplatne souradnice" << endl;
    error = true;
  }
  if(!error){
    // prints also resizes the table if the printable area is out of range so table cannot be const
    table.print(y,x);
  }
}

/**
  \brief insertCell is used to insert cell into the table
  If coords are bigger than our table it resizes itself
  @param table in which will be cell stored
*/
void insertCell(CTable & table){
  int y,x;
  bool error = false;

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

    string str;
    getline(cin, str); /** get text from user*/

    table.insert(y,x,str);
  }
}

/**
  \brief printCell is used to print whole cell
  If coords are bigger than our table it resizes itself
  Table cannot be const because it resizes it and evaluetes the parent cells. And they also may be
  out of table so we need to resize table.
  @param CTable table in which will be cell stored
*/
void printCell(CTable & table){
  int y,x;
  bool error = false;
  cout << "Vypis hodnoty bunky:" << endl;
  try{
    getCoords(y,x);
  }catch( const exception & excp){
    cerr << excp.what() << endl;
    error = true;
  }
  if(!error){
    cout << "Bunka(" << y << "," << x <<"): ";
    /* print content evaluates cell and if parent is not inicialised, it inicialise it so
      table cannot be const */
    table.getCell(y,x).printContent(table);
  }
}

/**
  \brief handleMenu is used to handle Menu

  @param menu, that will be printed out
  @return int END(defined) if the program should end and START(defined) if program should start
*/
int handleMenu(const CMenu & menu){
  menu.printHeader();
  menu.printMenu();

  //while cyclus that handles menu
  while(1){
    // print prompt
    cout << ">";
    // get user input
    int choice = menu.getInput();

    if( choice == START ){
      break;
    }else if( choice == HELP ){
      menu.printHelp();
      menu.printMenu();
    }else{
      cout << "Konec" << endl;
      return END;
    }
  }

  return START;
}

/**
 \brief Main function of this program
 */
int main(int argc, char** argv) {

  CMenu menu;
    if( handleMenu(menu) == END ){
      return 0;
    }

    CTable table;
    int choice;

    //prints help before the program starts
    menu.printHelp();
    while(1){
      //print prompt
      cout << ">";
      choice = inputHandler();
      // PRINT =================================================================
      if( choice == PRINT ){
        printTable(table);
      // INSERTION =============================================================
      }else if( choice == INSERT){
        insertCell(table);
      // PRINT CELL ============================================================
      }else if(choice == PRINTCELL){
        printCell(table);
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
