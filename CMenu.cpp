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
    cout << "        |_|                                                                 Autor: Stepan Severa (severste)\n";
    cout << endl;
}

void CMenu::printMenu() {
    cout << "Menu:" << endl;
    cout << "'n' Vytvorit novy spreadsheet" << endl;
    cout << "'h' Informace a napoveda" << endl;
    cout << "'q' Konec" << endl;
}


void CMenu::printHelp() {
  //cout << "==============================================================" << endl;
  cout << "Podporovane matematicke operatory:" << endl;
  cout << endl;
  cout << "+, -, *, /, ^(mocnina)"<< endl;
  cout << endl;
  cout << "Podporovane matematicko funkce:" << endl;
  cout << endl;
  cout << "sin(x): sinus" << endl;
  cout << "cos(x): cosinus" << endl;
  cout << "tan(x): tangens" << endl;
  cout << "cotg(x): cotangens" << endl;
  cout << "abs(x): absolutni hodnota" << endl;
  cout << "exp(x): exponencialni funkce" << endl;
  cout << "log(x): desitkovy logaritmus" << endl;
  cout << "ln(x): prirozeny logaritmus" << endl;
  cout << "sqrt(x): druha odmocnina" << endl;
  cout << endl;
  cout << "Ovladani:" << endl;
  cout << endl;
  cout << "'p' (print) Zobrazeni tabulky: zobrazuje se tabulka o velikosti 10x10, souradnice jsou leveho horniho rohu teto tabulky" << endl;
  cout << "             maximum souradnice: 999 990" << endl;
  cout << "'i' (insert) Vlozeni do tabulky: zadejte souradnice a pote text co chcete vlozit" << endl;
  cout << "             maximum souradnice: 1 000 000" << endl;
  cout << "             Pro vlozeni matematickeho vyrazu uvedte jako prvni znak \"=\"" << endl;
  cout << "             Pro vlozeni hodnoty bunky pouzijte \"[y;x]\" kde y je cislo radku a x cislo sloupce" << endl;
  cout << "             priklad: =10*sin(25)+[10;10]" << endl;
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

        if (c != 'n' && c != 'h' && c != 'q') {
            cout << "Stisknete klavesu n, h nebo q" << endl;
        }

        if (c == 'n') {
            return 1;
        }
        if (c == 'h') {
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
