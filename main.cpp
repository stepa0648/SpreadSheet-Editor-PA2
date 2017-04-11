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
#include <ncurses.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    char c;
    initscr();
    mvprintw(2, 20, "   _____                          _     _               _     ______    _ _ _                    __   ___  ");
    mvprintw(3, 20, "  / ____|                        | |   | |             | |   |  ____|  | (_) |                  /_ | / _ \\ ");
    mvprintw(4, 20, " | (___  _ __  _ __ ___  __ _  __| |___| |__   ___  ___| |_  | |__   __| |_| |_ ___  _ __  __   _| || | | |");
    mvprintw(5, 20, "  \\___ \\| '_ \\| '__/ _ \\/ _` |/ _` / __| '_ \\ / _ \\/ _ \\ __| |  __| / _` | | __/ _ \\| '__| \\ \\ / / || | | |");
    mvprintw(6, 20, "  ____) | |_) | | |  __/ (_| | (_| \\__ \\ | | |  __/  __/ |_  | |___| (_| | | || (_) | |     \\ V /| || |_| |");
    mvprintw(7, 20, " |_____/| .__/|_|  \\___|\\__,_|\\__,_|___/_| |_|\\___|\\___|\\__| |______\\__,_|_|\\__\\___/|_|      \\_/ |_(_)___/ ");
    mvprintw(8, 20, "        | |");
    mvprintw(9, 20, "        |_|");
    noecho();
    c = getch();
    mvprintw(11, 2, "Stisknuta klavesa byla: %c", c);
    noecho();
    refresh();
    getch();
    endwin();
    
    return 0;
}

