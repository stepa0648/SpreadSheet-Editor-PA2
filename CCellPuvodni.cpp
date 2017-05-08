/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: severste
 *
 * Created on April 23, 2017, 10:22 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;
class CCell {
public:

    CCell( ) : textVal( "" ), textLen( 0 ), result( 0 ), isNumber( false ) {
    }

    CCell( string text ) : textVal( text ), textLen( text.size( ) ), result( 0 ), isNumber( false ) {
    }

    friend ostream & operator<<(ostream & out, const CCell & a) {
        if ( a.isNumber ) {
            out << a.result;
        } else {
            if ( a.textLen > 10 ) {
                out << a.textVal.substr(0, 8).append("..");
            } else {
                out << a.textVal;
            }
        }

        return out;
    }

private:
    string textVal;
    size_t textLen;
    double result;
    bool isNumber;
};


/*
 *
 */
int main( int argc, char** argv ) {
    CCell a("Ahoj");
    CCell b("123456789011");
    CCell c("Ahoj jak se mas? Ja docela dobre, ale tak znas to");

    cout << "|" << setw(10) << a << "|" << endl;
    cout << "|" << setw(10) << b << "|" << endl;
    cout << "|" << setw(10) << c << "|" << endl;

    return 0;
}
