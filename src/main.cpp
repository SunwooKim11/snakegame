#include <iostream>
#include <ncurses.h>
#include <clocale>
#include <chrono>
// #include <mutex>
#include "LOC.h"
#include "map.h"
#include "Snake.h"
#include "Item.h"
#include "GrowthItem.h"
#include "PoisonItem.h"

using namespace std::chrono;

void init_config(Map& map, Snake& snake, Item *items){
    resize_term(25, 120);
    start_color();
    //configue color_pair
    init_pair(map.BACK_GROUND, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(map.WALL, COLOR_WHITE, COLOR_BLACK);
    init_pair(map.IMWALL, COLOR_WHITE, COLOR_WHITE);
    init_pair(snake.HEAD, COLOR_WHITE, COLOR_BLUE);
    init_pair(snake.BODY, COLOR_WHITE, COLOR_CYAN);
    init_pair(items[0].getColor(), COLOR_WHITE, COLOR_GREEN);
    init_pair(items[1].getColor(), COLOR_WHITE, COLOR_RED);

    //cursor no vision
    curs_set(0);
    //입력을 출력 x
    noecho();
    // 특수키 입력 가능 
    keypad(stdscr, TRUE);

    //getch 할때 기다리지 않음
    nodelay(stdscr, TRUE);

    cbreak();
}

void displayUpdate(WINDOW *display, Map& map, Snake& snake, Item *items){

    // background
    wbkgd(display, COLOR_PAIR(map.BACK_GROUND));

    // walls
    wattron(display, COLOR_PAIR(map.WALL));
    box(display, ' ', ' ');
    wattroff(display, COLOR_PAIR(map.WALL));

    wattron(display, COLOR_PAIR(map.IMWALL));
    mvwprintw(display, 0, map.size_x-1, " ");
    mvwprintw(display, map.size_y-1, 0, " ");
    mvwprintw(display, map.size_y-1, map.size_x-1 ," ");
    mvwprintw(display, 0, 0, " ");
    wattroff(display, COLOR_PAIR(map.IMWALL));

    //snake
    wattron(display, COLOR_PAIR(snake.HEAD));
    mvwprintw(display, snake.head[1], snake.head[0], " ");
    wattroff(display, COLOR_PAIR(snake.HEAD));

    wattron(display, COLOR_PAIR(snake.BODY));
    for(std::vector<LOC>::iterator it = snake.body.begin(); it<snake.body.end(); it++)
        mvwprintw(display, (*it)[1], (*it)[0], " ");
    wattroff(display, COLOR_PAIR(snake.BODY));

    // Item
    if(items[0].active){
        wattron(display, COLOR_PAIR(items[0].getColor()));
        mvwprintw(display, items[0].loc[1], items[0].loc[0], " ");
        wattroff(display, COLOR_PAIR(items[0].getColor()));
    }

    if(items[1].active){
        wattron(display, COLOR_PAIR(items[1].getColor()));
        mvwprintw(display, items[1].loc[1], items[1].loc[0], " ");
        wattroff(display, COLOR_PAIR(items[1].getColor()));
    }
    // show window 
    touchwin(display);
    wrefresh(display);
}



int main(){
    initscr();
    // set variables 
    Map map1;
    LOC center = {map1.size_y/2, map1.size_x/2};
    Snake snake(center, 3);
    WINDOW *display = subwin(stdscr, map1.size_y, map1.size_x, 1, 1);
    Item items[2] = {GrowthItem(map1, snake), PoisonItem(map1, snake)};
    int key;
    bool fail = false;


    // init_config(map1, snake);

    // displayUpdate(display, map1, snake);
    // std::thread tick(&Snake::move);
    while(1){
        if((key = getch()) != ERR) snake.setDirection(key);
        snake.move();
        if(fail=(snake.isFailed(map1, key))) break;
        
        //Item
        items[0].updateToAvoid(snake);
        items[1].updateToAvoid(snake);

        items[0].setStatus();
        items[1].setStatus();
        if(key == 'q') break;
        displayUpdate(display, map1, snake, items);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // if(fail)

    delwin(display);
    endwin();
    
    return 0;
}