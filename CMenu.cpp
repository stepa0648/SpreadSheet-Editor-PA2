/**
 * \file CMenu.cpp
 * \author severste
   \brief This is the file where CMenu class is inicialised

 */

#include "CMenu.h"
#include <iostream>
#include <climits>
/**
  \def END is constant that returns getInput if user whishes to end program
*/
#define END 0
/**
\def START is constant that returns getInput if user whishes to start table
*/
#define START 5
/**
\def HELP is constant that returns getInput if user whishes to print the help
*/
#define HELP 4

using namespace std;

CMenu::CMenu() {
}

void CMenu::printHeader() const {
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


void CMenu::printMenu()const {
    cout << "Menu:" << endl;
    cout << "'n' Vytvorit novy spreadsheet" << endl;
    cout << "'h' Informace a napoveda" << endl;
    cout << "'q' Konec" << endl;
}



void CMenu::printHelp()const {
  cout << "==============================================================" << endl;
  cout << "Podporovane matematicke operatory:" << endl;
  cout << endl;
  cout << "+, -, *, /, ^(mocnina)"<< endl;
  cout << "U retezeni mocnin pouzivejte zavorky! Napr: 2^3^4 se vyhodnoti jako (2^3)^4" << endl;
  cout << endl;
  cout << "Podporovane matematicke funkce:" << endl;
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
  cout << "             maximum souradnice: 499 990" << endl;
  cout << "'i' (insert) Vlozeni do tabulky: zadejte souradnice a pote text co chcete vlozit" << endl;
  cout << "             maximum souradnice:  500 000" << endl;
  cout << "             Pro vlozeni matematickeho vyrazu uvedte jako prvni znak \"=\"" << endl;
  cout << "             Pro vlozeni hodnoty bunky pouzijte \"[y;x]\" kde y je cislo radku a x cislo sloupce" << endl;
  cout << "             priklad: =10*sin(25)+[10;10]" << endl;
  cout << "'c' (print Cell) Zobrazeni obsahu bunky" << endl;
  cout << "'h' (help) Zobrazeni napovedy k ovladani" << endl;
  cout << "'q' (quit) Konec" << endl;
  cout << endl;
  //cout << "==============================" << endl;
}


int CMenu::getInput()const {
    char c;
    while (1) {
        cin >> c;
        cin.ignore(INT_MAX, '\n');

        if (c != 'n' && c != 'h' && c != 'q') {
            cout << "Stisknete klavesu n, h nebo q" << endl;
        }

        if (c == 'n') {
            return START;
        }
        if (c == 'h') {
            return HELP;
        }
        if (c == 'q') {
            return END;
        }
    }

}
