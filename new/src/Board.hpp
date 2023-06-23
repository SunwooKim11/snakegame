#pragma once

#include "Drawable.hpp"
#include <fstream>
class Board
{
protected:
    WINDOW *board_win;
    int height, width;
    int startY, startX;
    int endY, endX;
public: 
    Board(){};
    Board(int height, int width, int startY = 0, int startX = 0){
        
        int xMax, yMax;            
        getmaxyx(stdscr, yMax, xMax);
        
        if(!startY) startY = yMax/10;
        if(!startX) startX = xMax/20;

        construct(height, width, startY, startX);
        
        std::ofstream file("test.txt");
        if(file.is_open()) {
            file << "Create Board.\n";  
            file.close();
        } 

    };

    // ~Board(){
    //     delwin(board_win);
    // }

    void initialize(){
        clear();
        refresh();
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
    void setTimeout(int timeout){
        wtimeout(board_win, timeout);
    }

    int getEndY()
    {
        return endY;
    }

    int getEndX(){
        return endX;
    }

protected: 
    void construct(int height, int width, int startY, int startX){
        
        board_win = newwin(height, width, startY, startX);

        initialize();

        this->height = height;
        this->width = width;
        this->startY = startY;
        this->startX = startX;

        this->endY = startY + height;
        this->endX = startX + width;

        keypad(board_win, true);
        setTimeout(300);
    }
};


