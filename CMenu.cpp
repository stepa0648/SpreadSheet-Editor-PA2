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
#include <ncurses.h>

CMenu::CMenu() {
}

void CMenu::print() {
    mvprintw(2, 20, "   _____                          _     _               _     ______    _ _ _                    __   ___  ");
    mvprintw(3, 20, "  / ____|                        | |   | |             | |   |  ____|  | (_) |                  /_ | / _ \\ ");
    mvprintw(4, 20, " | (___  _ __  _ __ ___  __ _  __| |___| |__   ___  ___| |_  | |__   __| |_| |_ ___  _ __  __   _| || | | |");
    mvprintw(5, 20, "  \\___ \\| '_ \\| '__/ _ \\/ _` |/ _` / __| '_ \\ / _ \\/ _ \\ __| |  __| / _` | | __/ _ \\| '__| \\ \\ / / || | | |");
    mvprintw(6, 20, "  ____) | |_) | | |  __/ (_| | (_| \\__ \\ | | |  __/  __/ |_  | |___| (_| | | || (_) | |     \\ V /| || |_| |");
    mvprintw(7, 20, " |_____/| .__/|_|  \\___|\\__,_|\\__,_|___/_| |_|\\___|\\___|\\__| |______\\__,_|_|\\__\\___/|_|      \\_/ |_(_)___/ ");
    mvprintw(8, 20, "        | |                                                                                                          ");
    mvprintw(9, 20, "        |_|                                                                                                          ");

    mvprintw(11, 2, "Menu: ");
    mvprintw(12, 2, "1. Vytvorit novy spreadsheet");
    mvprintw(13, 2, "2. Nacist spreadsheet ze souboru");
    mvprintw(14, 2, "3. Konec");
    refresh();
}

void CMenu::run() {

    mvprintw(15, 2, "");
    char c;
    while (1) {
        c = getch(); // cekani na vstup od uzivatele a pote se vypne
        mvprintw(15, 2, "");
        if (c != '1' && c != '2' && c != '3') {
            mvprintw(16, 2, "Stisknete klavesu 1, 2, nebo 3");
            mvprintw(15, 2, "");
        }

        if (c == '3') {
            mvprintw(15, 2, "%c", c);
            break;
        }
    }
    refresh();
    mvprintw(16, 2, "Stisknete jakoukoli klavesu k ukonceni");

}

CMenu::CMenu(const CMenu& orig) {
}

CMenu::~CMenu() {
}

