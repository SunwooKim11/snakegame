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

void init_config(Map& map, Snake& snake, GrowthItem gItem, PoisonItem pItem){
    resize_term(25, 120);
    start_color();
    //configue color_pair
    init_pair(map.BACK_GROUND, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(map.WALL, COLOR_WHITE, COLOR_BLACK);
    init_pair(map.IMWALL, COLOR_WHITE, COLOR_WHITE);
    init_pair(snake.HEAD, COLOR_WHITE, COLOR_BLUE);
    init_pair(snake.BODY, COLOR_WHITE, COLOR_CYAN);
    init_pair(gItem.getColor(), COLOR_WHITE, COLOR_GREEN);
    init_pair(pItem.getColor(), COLOR_WHITE, COLOR_RED);


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

void displayUpdate(WINDOW *display, Map& map, Snake& snake, GrowthItem gItem, PoisonItem pItem){

    // background
    wbkgd(display, COLOR_PAIR(map.BACK_GROUND));

    // walls
    wattron(display, COLOR_PAIR(map.WALL));
    box(display, ' ', ' ');
    for(int i=0; i<map.w_size; i++){
        mvwprintw(display, map.walls[i].y, map.walls[i].x, " ");
    }
    wattroff(display, COLOR_PAIR(map.WALL));

    wattron(display, COLOR_PAIR(map.IMWALL));
    mvwprintw(display, 0, map.size_x-1, " ");
    mvwprintw(display, map.size_y-1, 0, " ");
    mvwprintw(display, map.size_y-1, map.size_x-1 ," ");
    mvwprintw(display, 0, 0, " ");
        for(int i=0; i<map.imw_size; i++){
        mvwprintw(display, map.imwalls[i].y, map.imwalls[i].x, " ");
    }
    wattroff(display, COLOR_PAIR(map.IMWALL));


    //snake
    wattron(display, COLOR_PAIR(snake.HEAD));
    mvwprintw(display, snake.head.y, snake.head.x, " ");
    wattroff(display, COLOR_PAIR(snake.HEAD));

    wattron(display, COLOR_PAIR(snake.BODY));
    for(std::vector<LOC>::iterator it = snake.body.begin(); it!=snake.body.end()-1; it++)
        mvwprintw(display, (*it).y, (*it).x, " ");
    wattroff(display, COLOR_PAIR(snake.BODY));

    // Item
    if(gItem.active){
        wattron(display, COLOR_PAIR(gItem.getColor()));
        mvwprintw(display, gItem.loc.y, gItem.loc.x , " ");
        wattroff(display, COLOR_PAIR(gItem.getColor()));
    }

    if(pItem.active){
        wattron(display, COLOR_PAIR(pItem.getColor()));
        mvwprintw(display, pItem.loc.y , pItem.loc.x, " ");
        wattroff(display, COLOR_PAIR(pItem.getColor()));
    }
    // show window 
    touchwin(display);
    wrefresh(display);
}

void print_fail(WINDOW* display){
    init_pair(31, COLOR_RED, COLOR_RED);
    init_pair(32, COLOR_RED, COLOR_YELLOW);
    mvwprintw(display, 18, 27, "      ");
    mvwprintw(display, 19, 28, "fail");
    mvwprintw(display, 20, 27, "      ");
}
int main(){
    initscr();
    // set variables 
    Map map1;
    LOC center = {map1.size_y/2, map1.size_x/2};
    Snake snake(center, 4);
    WINDOW *display = subwin(stdscr, map1.size_y, map1.size_x, 1, 1);
    GrowthItem gItem(map1, snake);
    PoisonItem pItem(map1, snake);
    // Item items[2] = {GrowthItem(map1, snake), PoisonItem(map1, snake)};
    int key;


    init_config(map1, snake, gItem, pItem);

    // displayUpdate(display, map1, snake);
    // std::thread tick(&Snake::move);
    while(1){
        if((key = getch()) != ERR) snake.setDirection(key);
        snake.move();
        if(snake.isFailed(map1, key)){
            print_fail(display);
            key = getch();
            break;
        }
        //Item
        // items[0].updateToAvoid(snake);
        // items[1].updateToAvoid(snake);

        // items[0].setStatus();
        // items[1].setStatus();
        gItem.updateToAvoid(snake);
        pItem.updateToAvoid(snake);
        gItem.setStatus(snake);
        pItem.setStatus(snake);
        if(key == 'q') break;
        displayUpdate(display, map1, snake, gItem, pItem);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // if(fail)

    delwin(display);
    endwin();
    
    return 0;
}