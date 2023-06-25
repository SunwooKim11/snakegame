/*
brew install ncurses
clang++ -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-c99-compat -Wno-poison-system-directories -pedantic -fsanitize=undefined,null -std=c++17 -cxx-isystem /usr/local/include -o Merlin2011 Merlin2011.cpp -lncurses
./Merlin2011
*/
#include <ncurses.h>
#include <clocale>
#include <iostream>
#include <fstream>
#include "src/Drawable.hpp"

#define DIMS 15
#define HEIGHT DIMS
#define WIDTH DIMS * 2.5

#define WALL 3

static int startx = 0;
static int starty = 0;

static int realX = 0;
static int realY = 0;

// static Drawable dot = Drawable()
static void redraw(WINDOW* map_win, Drawable ops);
static void saveFiles(WINDOW* map_win);
static void saveFile(WINDOW* map_win, const char* name);
char sane(int c) {
    if (c > ' ' && c <= '~')
        return static_cast<char>(c);
    return ' ';
}


int main() {
    int choice = 0;
    WINDOW* map_win;

    setlocale(LC_ALL, "");

    /* Initialize curses */
    initscr();
    clear();
    noecho();
    cbreak();  // Line buffering disabled. pass on everything
    keypad(stdscr, TRUE);
    halfdelay(1);

    /* Try to put the window in the middle of screen */
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;

    attron(A_REVERSE);
    mvprintw(23, 1, "Click on Exit to quit (Works best in a virtual console)");
    refresh();
    attroff(A_REVERSE);

    /* Print the menu for the first time */
    map_win = newwin(HEIGHT, WIDTH, starty, startx);
    scrollok(map_win, TRUE);
    keypad(map_win, TRUE);

    /* Get all the mouse events */
    //auto mm_success = mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
    /* Get just just the click event. */
    mmask_t mousemask_setting = NCURSES_BUTTON_CLICKED;
    auto mm_success = mousemask(mousemask_setting, nullptr);

    if (!mm_success) {
        mvprintw(22, 1, "FAIL: mousemask");
    } else if (mm_success == mousemask_setting) {
        mvprintw(22, 1, "SUCCESS: mousemask");
    } else {
        mvprintw(22, 1, "Partial success: mousemask %x of %x", mm_success, mousemask_setting);
    }
    refresh();

    bool loop{ true };

    while (loop) {
        auto c = wgetch(map_win);

        switch (c) {
            case KEY_MOUSE: {
                MEVENT event;
                mvprintw(20, 1, "Found mouse!");
                if (getmouse(&event) == OK) { /* When the user clicks left mouse button */
                    mvprintw(20, 1, "Found mouse! %3d %3d %d", event.x, event.y, event.bstate);
                    if(event.bstate & BUTTON1_PRESSED){
                        realX = event.x - startx;
                        realY = event.y - starty;
                        mvprintw(20, 1, "PRESSED %3d %3d MOUSE_CLICK", realX, realY);
                        redraw(map_win, Drawable(realY, realX, 'X'));
                    }
                    else if(event.bstate & BUTTON1_RELEASED){
                        realX = event.x - startx;
                        realY = event.y - starty;
                        mvprintw(20, 1, "RELEASED %3d %3d MOUSE_CLICK", realX, realY);
                        
                    }
                    else if (event.bstate  & BUTTON_CTRL) {
                        realX = event.x - startx;
                        realY = event.y - starty;
                        mvprintw(20, 1, "IMMUTABLE %3d %3d MOUSE_CLICK", realX, realY);
                        redraw(map_win, Drawable(realY, realX, 'X'));
                        
                    }
                    else if (event.bstate  & BUTTON_ALT) {
                        realX = event.x - startx;
                        realY = event.y - starty;
                        mvprintw(20, 1, "ERASE     %3d %3d MOUSE_CLICK", realX, realY);
                        redraw(map_win, Drawable(realY, realX, ' '));

                    }
                    else if (event.bstate  & NCURSES_BUTTON_CLICKED) {
                        realX = event.x - startx;
                        realY = event.y - starty;
                        mvprintw(20, 1, "NORMAL    %3d %3d MOUSE_CLICK", realX, realY);
                        redraw(map_win, Drawable(realY, realX, 'O'));

                    }
                }
            } break;

            case ERR: {
                static int count = 0;
                ++count;
                mvprintw(21, 0, "Nothing happened (%d).", count);
                refresh();
            } break;

            
            default: {
                static int x = 0;
                mvprintw(24+x, 0, "Key pressed is = %3d '%c'", c, sane(c));
                if (++x == 30)
                    x = 0;
                mvprintw(24+x, 0, "-------------------------");
                refresh();
                if (c == 'q'){
                saveFiles(map_win);
                loop = false;
                }
            } break;
        }
    }
    
    endwin();
}



     

void redraw(WINDOW* map_win, Drawable ops)
{   
    box(map_win, 0, 0);
    // wattron(map_win, COLOR_PAIR(WALL));
    mvwaddch(map_win, ops.getY(), ops.getX(), ops.getIcon());
    // wattroff(map_win, COLOR_PAIR(WALL));
    wrefresh(map_win);
}

void saveFiles(WINDOW* map_win)
{   
    saveFile(map_win, "normal.csv");
    saveFile(map_win, "immutable.csv");
}

void saveFile(WINDOW* map_win, const char* name)
{    
    chtype icon;
    if(name == "normal.csv") icon = 'O';
    else icon = 'X';

    std::fstream fs;
    fs.open(name, std::ios::out);

    for(int x=0; x<WIDTH; x++)
    {
        for(int y=0; y<HEIGHT; y++)
        {
            if((mvwinch(map_win, y, x)) == icon)
            {
                // fs << "(" << y << "," << x << ")" << ",";
                fs  << y << "," << x << "\n";
            }
        }
    }
    fs.close();
}

