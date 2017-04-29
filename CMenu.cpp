/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   CMenu.cpp
 * Author: severste
 *
 * Created on April 12, 2017, 7:46 PM
 */

#include "CMenu.h"
#include <iostream>
using namespace std;
CMenu::CMenu() {
}

void CMenu::print() {
    cout << "   _____                          _     _               _     ______    _ _ _                    __   ___  \n";
    cout << "  / ____|                        | |   | |             | |   |  ____|  | (_) |                  /_ | / _ \\ \n";
    cout << " | (___  _ __  _ __ ___  __ _  __| |___| |__   ___  ___| |_  | |__   __| |_| |_ ___  _ __  __   _| || | | |\n";
    cout << "  \\___ \\| '_ \\| '__/ _ \\/ _` |/ _` / __| '_ \\ / _ \\/ _ \\ __| |  __| / _` | | __/ _ \\| '__| \\ \\ / / || | | |\n";
    cout << "  ____) | |_) | | |  __/ (_| | (_| \\__ \\ | | |  __/  __/ |_  | |___| (_| | | || (_) | |     \\ V /| || |_| |\n";
    cout << " |_____/| .__/|_|  \\___|\\__,_|\\__,_|___/_| |_|\\___|\\___|\\__| |______\\__,_|_|\\__\\___/|_|      \\_/ |_(_)___/ \n";
    cout << "        | |                                                                                                          \n";
    cout << "        |_|                                                                                                          \n";
    cout << endl;
    cout << "Menu: \n";
    cout << "1. Vytvorit novy spreadsheet\n";
    cout << "2. Nacist spreadsheet ze souboru\n";
    cout << "3. Informace\n";
    cout << "4. Konec\n";
}

void CMenu::run() {

    char c;
    while (1) {
        cin >> c;
        if (c != '1' && c != '2' && c != '3' && c != '4') {
            //vypisuje se tolikrat kolik je chybnych znaku opravit
            cout << "Stisknete klavesu 1, 2, 3, nebo 4" << endl;
        }

        if (c == '4') {
            break;
        }
    }
    cout << "Konec" << endl;

}

CMenu::CMenu(const CMenu& orig) {
}

CMenu::~CMenu() {
}
