#include <iostream>
#include <ncurses.h>
#include <clocale>
#include <thread>
// #include <mutex>
#include "LOC.h"
#include "map.h"
#include "Snake.h"

void init_config(Map& map, Snake& snake){
    resize_term(25, 120);
    start_color();
    //configue color_pair
    init_pair(map.BACK_GROUND, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(map.WALL, COLOR_WHITE, COLOR_CYAN);
    init_pair(map.IMWALL, COLOR_WHITE, COLOR_BLUE);
    init_pair(snake.HEAD, COLOR_WHITE, COLOR_RED);
    init_pair(snake.BODY, COLOR_WHITE, COLOR_GREEN);

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

void displayUpdate(WINDOW *display, Map& map, Snake& snake){
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

    wattron(display, COLOR_PAIR(snake.HEAD));
    mvwprintw(display, snake.head[1], snake.head[0], " ");
    wattroff(display, COLOR_PAIR(snake.HEAD));

    wattron(display, COLOR_PAIR(snake.BODY));
    for(std::vector<LOC>::iterator it = snake.body.begin(); it<snake.body.end(); it++)
        mvwprintw(display, (*it)[1], (*it)[0], " ");
    wattroff(display, COLOR_PAIR(snake.BODY));

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
    int key;
    

    init_config(map1, snake);

    // displayUpdate(display, map1, snake);
    // std::thread tick(&Snake::move);
    while(!(snake.isFailed(map1, key))){
        if((key = getch()) != ERR) snake.setDirection(key);
        snake.move();
        displayUpdate(display, map1, snake);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if(key == 'q') break;
    }
    // if(tick.joinable()) tick.join();

    // key = getch();

    delwin(display);
    endwin();
    
    return 0;
}