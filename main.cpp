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
    case '1': return 1; break;
    case '2': return 2; break;
    case '3': return 3; break;
    case '4': return 4; break;
    case 'x': return 0; break;
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

    table.print(0,0);
    while(1){
      choice = inputHandler();


      if( choice == 1 ){
        cout << "Vypis tabulky:" << endl;
        getCoords(y,x);
        table.print(y,x);
      }else if( choice == 2){
        cout << "Vlozeni hodnoty do bunky:" << endl;
        getCoords(y,x);
        cout << "Zadejte text: ";
        cin >> str; // odladit aby se neprerusil mezerou
        table.insert(y,x,str);
        cout << "Uspesne vlozeno" << endl;
      }else if(choice == 3){
        cout << "Vypis hodnoty bunky:" << endl;
        getCoords(y,x);
        table.getCell(y,x).printContent();
      }else if(choice == 4){
        menu.printHelp();
      }else if( choice == 0){
        break;
      }
    }
    cout << "Konec" << endl;
    return 0;
}
