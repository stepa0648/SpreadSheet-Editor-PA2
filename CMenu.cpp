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
    cout << "'n' Vytvorit novy spreadsheet" << endl;
    cout << "'i' Informace a napoveda" << endl;
    cout << "'q' Konec" << endl;
}
void CMenu::printInfo() {
  //cout << "==============================================================" << endl;
  cout << endl;
  cout << "Informace" << endl;

  this->printHelp();
}

void CMenu::printHelp() {
  //cout << "==============================================================" << endl;
  cout << endl;
  cout << "Ovladani" << endl;
  cout << endl;
  cout << "'p' (print) Zobrazeni tabulky: zobrazuje se tabulka o velikosti 10x10, souradnice jsou leveho horniho rohu teto tabulky" << endl;
  cout << "'i' (insert) Vlozeni do tabulky: zadejte souradnice a pote text co chcete vlozit" << endl;
  cout << "             Pro vlozeni matematickeho vyrazu uvedte jako prvni znak \"=\"" << endl;
  cout << "'c' (print Cell) Zobrazeni obsahu bunky" << endl;
  cout << "'h' (help) Zobrazeni napovedy k ovladani" << endl;
  cout << "'q' (quit) Konec" << endl;
  cout << endl;
  //cout << "==============================" << endl;
}

int CMenu::getInput() {
    char c;
    while (1) {
        cin >> c;
        cin.ignore(INT_MAX, '\n');

        if (c != 'n' && c != 'i' && c != 'q') {
            cout << "Stisknete klavesu n, i nebo q" << endl;
        }

        if (c == 'n') {
            return 1;
        }
        if (c == 'i') {
            return 2;
        }
        if (c == 'q') {
            return 3;
        }
    }

}

CMenu::CMenu(const CMenu& orig) {
}

CMenu::~CMenu() {
}
