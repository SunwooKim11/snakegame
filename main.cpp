#include <iostream>
#include <ncurses.h>
#include <clocale>
#include "LOC.h"
#include "map.h"

// const int WALL = 1;
// const int IMWALL = 2;
// const int HEAD = 3;
// const int BODY = 4;
// const int GROWTH_ITEM = 5;
// const int POISON_ITEM = 6;
// const int GATE = 7;
// const int BACK_GROUND = 8;

void init_config(Map& map){
    resize_term(25, 120);
    start_color();
    //configue color_pair
    init_pair(map.BACK_GROUND, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(map.WALL, COLOR_WHITE, COLOR_CYAN);
    init_pair(map.IMWALL, COLOR_WHITE, COLOR_BLUE);

    //cursor no vision
    curs_set(0);
    //입력을 출력 x
    noecho();
    // 특수키 입력 가능 
    keypad(stdscr, TRUE);
}

void displayUpdate(WINDOW *display, Map& map){
    wbkgd(display, COLOR_PAIR(map.BACK_GROUND));

    wattron(display, COLOR_PAIR(map.WALL));
    box(display, ' ', ' ');
    wattroff(display, COLOR_PAIR(map.WALL));

    wattron(display, COLOR_PAIR(map.IMWALL));
    mvwprintw(display, 0, map.size_x-1, " ");
    mvwprintw(display, map.size_y-1, 0, " ");
    mvwprintw(display, map.size_y-1, map.size_x-1 ," ");
    mvwprintw(display, 0, 0, " ");
    wattroff(display, COLOR_PAIR(map.IMWALL));


    // show window 
    touchwin(display);
    wrefresh(display);
}

int main(){
    initscr();
    // define class 
    Map map1;
    WINDOW *display = subwin(stdscr, map1.size_y, map1.size_x, 1, 1);

    init_config(map1);
    int key;

    displayUpdate(display, map1);

    while(1){
        key = getch();
        if(key == 'q') break;
    }
    delwin(display);
    endwin();
    
    return 0;
}