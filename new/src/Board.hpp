#pragma once

#include<cstdlib>
#include<time.h>
#include "Drawable.hpp"

class Board
{
private:
    WINDOW *board_win;
    int height, width;
    int startY, startX;
public: 
    Board(int height = 17, int width = 17*2.5){
        construct(height, width);
    };

    void initialize(){
        clear();
        refresh();
    }
    

    // y, x를 ref로 받아. empty 한 좌표를 y, x에 할당시킴. 
    void getEmptyCoordinates(int &y, int &x){
        while ((mvwinch(board_win, y = rand() % height, x = rand() % width)) != ' ');       
    }

    void addBorder(){
        box(board_win, 0, 0);
    }
    
    void add(Drawable drawable)
    {
        addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
    }

    void addAt(int y, int x, chtype ch){
        mvwaddch(board_win, y, x, ch);  // win에서 커서를 이동하고, 문자를 붙여넣는다.
    }
    
     
    void clear(){
        wclear(board_win);
        addBorder();
    }

    void refresh(){
        wrefresh(board_win);
    }

    chtype getInput(){
        return wgetch(board_win);
    }

    void setTimeout(int timeout){
        wtimeout(board_win, timeout);
    }

    chtype getCharAt(Drawable obj)
    {
        return mvwinch(board_win, obj.getY(), obj.getX());
    }

private: 
    void construct(int height, int width){
        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);
        board_win = newwin(height, width, (yMax / 2) - (height / 2), (xMax / 2) - (width / 2));

        initialize();

        this->height = height;
        this->width = width;

        // Add timeout
        setTimeout(500);
        keypad(board_win, true);

    }
};


