/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: severste
 *
 * Created on April 18, 2017, 3:26 PM
 */

#include <cstdlib>
#include <stack>
#include <iostream>

using namespace std;

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
int main( int argc, char** argv ) {

    string a = "(45 * (sin 56))";
    stack<char> s;

    if ( !testBrackets(a) ) {
        cout << "Zavorky jsou spatne" << endl;
    } else {
        cout << "Zavorky jsou spravne" << endl;

    }



    return 0;
}

