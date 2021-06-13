// #include <iostream>
#include <ncurses.h>
#include <clocale>
#include <chrono>
#include <mutex>
#include <thread>
#include "LOC.h"
#include "Map.h"
#include "Snake.h"
#include "Item.h"
#include "GrowthItem.h"
#include "PoisonItem.h"
#include "Gate.h"
// #include "BoardUpdate.h"

using namespace std::chrono;

void set_getch_option(WINDOW* display, bool isPlaying=TRUE){
    // make user can input a special key
    keypad(display, TRUE);
    // make getch no blocking
    nodelay(display, isPlaying);
    cbreak();
};

void init_config(Map& map, Snake& snake, GrowthItem& gItem, PoisonItem& pItem, Gate& gate){
    resize_term(30, 120);
    start_color();
    //configue color_pair
    init_pair(map.BACK_GROUND, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(map.WALL, COLOR_WHITE, COLOR_WHITE);
    init_pair(map.IMWALL, COLOR_WHITE, COLOR_BLACK);
    init_pair(snake.getHeadColor(), COLOR_WHITE, COLOR_BLUE);
    init_pair(snake.getBodyColor(), COLOR_WHITE, COLOR_CYAN);
    init_pair(gItem.getColor(), COLOR_WHITE, COLOR_GREEN);
    init_pair(pItem.getColor(), COLOR_WHITE, COLOR_RED);
    init_pair(gate.getColor(), COLOR_MAGENTA, COLOR_MAGENTA);
    //cursor no vision
    curs_set(0);
    // don't print input value.
    noecho();
}

// redraw the entrie screen
void displayUpdate(WINDOW *display, Map& map, Snake& snake, GrowthItem& gItem, PoisonItem& pItem, Gate& gate){
    
    werase(display);
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

    for(int i=0; i<map.imw_size; i++){
        mvwprintw(display, map.imwalls[i].y, map.imwalls[i].x, " ");
    }
    wattroff(display, COLOR_PAIR(map.IMWALL));

    // Item
    if(gItem.getActive()){
        wattron(display, COLOR_PAIR(gItem.getColor()));
        mvwprintw(display, gItem.getLoc().y, gItem.getLoc().x , " ");
        wattroff(display, COLOR_PAIR(gItem.getColor()));
    }

    if(pItem.getActive()){
        wattron(display, COLOR_PAIR(pItem.getColor()));
        mvwprintw(display, pItem.getLoc().y , pItem.getLoc().x, " ");
        wattroff(display, COLOR_PAIR(pItem.getColor()));
    }
    
    //snake
    wattron(display, COLOR_PAIR(snake.getHeadColor()));
    mvwprintw(display, snake.getHead().y, snake.getHead().x, " ");
    wattroff(display, COLOR_PAIR(snake.getHeadColor()));

    wattron(display, COLOR_PAIR(snake.getBodyColor()));
    for(std::vector<LOC>::iterator it = snake.getBody().begin(); it!=snake.getBody().end(); it++)
        mvwprintw(display, (*it).y, (*it).x, " ");
    wattroff(display, COLOR_PAIR(snake.getBodyColor()));

    //gate
    if(gate.getActive()){
        wattron(display, COLOR_PAIR(gate.getColor()));
        mvwprintw(display, gate.getLoc1().y, gate.getLoc1().x, " ");
        mvwprintw(display, gate.getLoc2().y, gate.getLoc2().x, " ");
        wattroff(display, COLOR_PAIR(gate.getColor()));
    }
    // show window 
    touchwin(display);
    wrefresh(display);
}

// if fail, print fail in screen
void print_fail(WINDOW* display){
    init_pair(31, COLOR_RED, COLOR_RED);
    init_pair(32, COLOR_RED, COLOR_YELLOW);
    
    wattron(display, COLOR_PAIR(31));
    mvwprintw(display, 15, 13, "      ");
    mvwprintw(display, 17, 13, "      ");
    wattroff(display, COLOR_PAIR(31));
    wattron(display, COLOR_PAIR(32));
    mvwprintw(display, 16, 14, "fail");
    wattroff(display, COLOR_PAIR(32));

    touchwin(display);
    wrefresh(display);
}

// print start screen
void print_start(){
    mvprintw(8, 34, "snake game");
    mvprintw(10, 30, "20203039 Kim SunWoo");
    mvprintw(12, 29, "Press r key to start");
    touchwin(stdscr);
    refresh();
    while(getch()!= 'r');
    mvprintw(8, 34, "          ");
    mvprintw(10, 30, "                   ");
    mvprintw(12, 29, "                      ");    
    touchwin(stdscr);
    refresh();
}

int main(){
    initscr();
    // map.size is {21, 32}
    Map map;
    LOC center = {17, map.size_x/2};
    Snake snake(center, 3);
    WINDOW *display = subwin(stdscr, map.size_y, map.size_x, 1, 1);
    WINDOW *scoreBoard = subwin(stdscr, 10, map.size_x, 1, 37);
    WINDOW *missionBoard = subwin(stdscr, 10, map.size_x, 13, 37);
    GrowthItem gItem(map, snake);
    PoisonItem pItem(map, snake);
    Gate gate;
    
    int key, stage=0;

    init_config(map, snake, gItem, pItem, gate);
    set_getch_option(display);
    print_start();
    
    // std::thread t1(boardUpdate(), scoreBoard, missionBoard, std::ref(snake), std::ref(stage));

    while(1){
        if((key = wgetch(display)) != ERR) snake.control(key);

        snake.move();
        // if game fail call 'print_fail()'
        if(snake.isFailed(map, gate.getLoc1(), gate.getLoc2(), gate.getActive(), key)){
            stage = 5;
            print_fail(display);
            nodelay(stdscr, false);
            key = getch();
            break;
        }
        // handle Item
        gItem.updateToAvoid(snake);
        pItem.updateToAvoid(snake);
        gItem.setStatus(snake);
        pItem.setStatus(snake);
        // handle Gate 
        gate.setStatus(map, snake);
        // if users pressed 'q', end the program
        if(key == 'q'){stage = 5; break;}
        displayUpdate(display, map, snake, gItem, pItem, gate);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    delwin(display);
    // if(t1.joinable()){t1.join(); delwin(scoreBoard); delwin(missionBoard);}
    endwin();

    return 0;
}