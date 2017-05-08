/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: severste
 *
 * Created on April 9, 2017, 10:55 AM
 */

#include <cstdlib>
#include "CMenu.h"
#include "CTable.h"
#include "CCell.h"

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
      for (int i = 0; i <= 10; i++) {
          for (int j = 0; j <= 10; j++) {
              table.insert(i, j, CCell("ahoj"));
          }
      }
      table.insert(10, 2, CCell("Nazdarek"));
      table.insert(11, 2, CCell("Nazdar"));
      table.insert(1, 11, CCell("2*(4+1)-sin(29"));

      table.print();
    }else if( choice == 2 ){
      //vytiskni info
      cout << "Informace" << endl;
    }

    cout << "Konec" << endl;
    return 0;
}
