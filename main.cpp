/*
 * File:   main.cpp
 * Author: severste
 *
 * Created on April 9, 2017, 10:55 AM
 */

#include "CMenu.h"
#include "CTable.h"

using namespace std;



/*
 *
 */
int main(int argc, char** argv) {
    CMenu menu;
    menu.print();
    int choice = menu.run();
    if( choice == 1 ){

      CTable table;


      table.insert(3, 2, "Nazdarek");
      table.insert(3, 4, "Nazdarek");
      table.insert(3, 5, "Nazdarek");
      table.insert(12, 2, "Nazdarek");
      table.insert(11, 2, "Nazdar");
      table.insert(1, 15, "2*(4+1)-sin(29");


      table.print( 1, 1 );
    }else if( choice == 2 ){
      //vytiskni info
      cout << "Informace" << endl;
    }

    cout << "Konec" << endl;
    return 0;
}
