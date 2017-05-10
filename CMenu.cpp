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
#include <climits>
using namespace std;
CMenu::CMenu() {
}

void CMenu::printHeader() {
    cout << "   _____                          _     _               _     ______    _ _ _                    __   ___  \n";
    cout << "  / ____|                        | |   | |             | |   |  ____|  | (_) |                  /_ | / _ \\ \n";
    cout << " | (___  _ __  _ __ ___  __ _  __| |___| |__   ___  ___| |_  | |__   __| |_| |_ ___  _ __  __   _| || | | |\n";
    cout << "  \\___ \\| '_ \\| '__/ _ \\/ _` |/ _` / __| '_ \\ / _ \\/ _ \\ __| |  __| / _` | | __/ _ \\| '__| \\ \\ / / || | | |\n";
    cout << "  ____) | |_) | | |  __/ (_| | (_| \\__ \\ | | |  __/  __/ |_  | |___| (_| | | || (_) | |     \\ V /| || |_| |\n";
    cout << " |_____/| .__/|_|  \\___|\\__,_|\\__,_|___/_| |_|\\___|\\___|\\__| |______\\__,_|_|\\__\\___/|_|      \\_/ |_(_)___/ \n";
    cout << "        | |                                                                                                          \n";
    cout << "        |_|                                                                                                          \n";
    cout << endl;
}

void CMenu::printMenu() {
    cout << "Menu:" << endl;
    cout << "1. Vytvorit novy spreadsheet" << endl;
    cout << "2. Informace" << endl;
    cout << "3. Konec" << endl;
}
void CMenu::printInfo() {
  cout << "==============================================================" << endl;
  cout << "Informace" << endl;

  cout << "Napoveda" << endl;
  cout << endl;
  cout << "1. Zobrazeni tabulky: zobrazuje se tabulka o velikosti 10x10, souradnice jsou leveho horniho rohu" << endl;
  cout << "2. Vlozeni do tabulky: zadejte souradnice a pote text co chcete vlozit" << endl;
  cout << "3. Zobrazeni napovedy" << endl;
  cout << endl;
  cout << "==============================" << endl;
}

void CMenu::printHelp() {
  cout << "==============================================================" << endl;
  cout << "Napoveda" << endl;
  cout << endl;
  cout << "1. Zobrazeni tabulky: zobrazuje se tabulka o velikosti 10x10, souradnice jsou leveho horniho rohu" << endl;
  cout << "2. Vlozeni do tabulky: zadejte souradnice a pote text co chcete vlozit" << endl;
  cout << "3. Zobrazeni napovedy" << endl;
  cout << endl;
  cout << "==============================" << endl;
}

int CMenu::getInput() {
    char c;
    while (1) {
        cin >> c;
        cin.ignore(INT_MAX, '\n');

        if (c != '1' && c != '2' && c != '3') {
            cout << "Stisknete klavesu 1, 2 nebo 3" << endl;
        }

        if (c == '1') {
            return 1;
        }
        if (c == '2') {
            return 2;
        }
        if (c == '3') {
            return 3;
        }
    }

}

CMenu::CMenu(const CMenu& orig) {
}

CMenu::~CMenu() {
}
