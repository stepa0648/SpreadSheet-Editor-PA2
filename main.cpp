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
//#include <ncurses.h>
#include "CMenu.h"

using namespace std;

/*
 *
 */
int main(int argc, char** argv) {
    CMenu menu;

    menu.print();

    menu.run();


    return 0;
}
