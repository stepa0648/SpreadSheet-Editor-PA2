/*
 * File:   main.cpp
 * Author: severste
 *
 * Created on April 9, 2017, 10:55 AM
 */

#include <stack>
#include "CMenu.h"
#include "CTable.h"
#include "CCell.h"

using namespace std;

/** parameter is string in which we want to test if the bracket are right.
*  it return false if not and true if yes
*/
bool testBrackets( string x ) {
    stack<char> s;
    char c;
    for ( size_t i = 0; i < x.size(); i++ ) {
        c = x[i];
        if ( c == '(' ) {
            s.push(c);
        } else if ( c == ')' ) {
            if ( s.empty() ) {
                return false;
            }
            if ( s.top() != '(' ) {
                return false;
            } else {
                s.pop();
            }
        }
    }
    if ( !s.empty() ) {
        return false;
    }
    return true;
}

/*
 *
 */
int main(int argc, char** argv) {
    CMenu menu;
    menu.print();
    int choice = menu.run();
    if( choice == 1 ){
      CTable table;
      /*for (int i = 0; i <= 10; i++) {
          for (int j = 0; j <= 10; j++) {
              table.insert(i, j, CCell("ahoj"));
          }
      }*/
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
