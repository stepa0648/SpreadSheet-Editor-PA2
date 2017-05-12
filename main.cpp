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

#define END 0
#define PRINT 1
#define INSERT 2
#define PRINTCELL 3
#define HELP 4

using namespace std;

void getCoords(int & y, int & x){
  cout << "Zadejte cislo radku: ";
  cin >> y;
  cout << "Zadejte cislo sloupce: ";
  cin >> x;
  cin.ignore(INT_MAX, '\n');
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
    default: cout << "Zadejte platne hodnoty" << endl;
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

    menu.printHelp();
    while(1){
      choice = inputHandler();


      if( choice == PRINT ){
        cout << "Vypis tabulky:" << endl;
        getCoords(y,x);
        table.print(y,x);
      }else if( choice == INSERT){
        cout << "Vlozeni hodnoty do bunky:" << endl;
        getCoords(y,x);
        cout << "Zadejte text: ";
        getline(cin, str); /** get text from user*/
        table.insert(y,x,str);
        cout << "Uspesne vlozeno" << endl;
      }else if(choice == PRINTCELL){
        cout << "Vypis hodnoty bunky:" << endl;
        getCoords(y,x);
        cout << "Bunka(" << y << "," << x <<") = ";
        table.getCell(y,x).printContent();
      }else if(choice == HELP){
        menu.printHelp();
      }else if( choice == END){
        break;
      }
    }
    cout << "Konec" << endl;
    return 0;
}
