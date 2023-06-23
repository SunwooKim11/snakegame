#pragma once

#include<cstdlib>
#include<time.h>
#include "Board.hpp"

#define GAME_DIMS 20
#define GAME_ROWS GAME_DIMS
#define GAME_COLS GAME_DIMS * 2.5

class Gameboard : public Board
{

public: 
    Gameboard(int height=GAME_ROWS, int width=GAME_COLS, int startY = 0, int startX = 0) : Board(height, width, startY, startX)
    {

    };
  

    // y, x를 ref로 받아. empty 한 좌표를 y, x에 할당시킴. 
    void getEmptyCoordinates(int &y, int &x){
        while ((mvwinch(board_win, y = rand() % height, x = rand() % width)) != ' ');       
    }

    chtype getInput(){
        return wgetch(board_win);
    }


    chtype getCharAt(Drawable obj)
    {
        return mvwinch(board_win, obj.getY(), obj.getX());
    }

    
private: 

};


