#pragma once

#include<cstdlib>
#include<time.h>
#include "Board.hpp"

#define SCORE_DIMS 10
#define SCORE_ROWS SCORE_DIMS
#define SCORE_COLS SCORE_DIMS * 4

class Scoreboard : public Board
{
private:
    int curr_len = 3, max_len = 3;
    int plus_item = 0, minus_item = 0;
    int gate = 0;
public: 
    Scoreboard(){};
    Scoreboard(int height, int width, int startY , int startX) : Board(height, width, startY, startX)
    {

    };
    void initialize()
    {
        clear();
        redraw();
    }
    void clear()
    {
        Board::clear();
        mvwprintw(board_win, 0, 1, "Score Board");
        mvwprintw(board_win, 1, 1, "B:");
        mvwprintw(board_win, 2, 1, "+:");
        mvwprintw(board_win, 3, 1, "-:");
        mvwprintw(board_win, 4, 1, "G:");
    }
    
    void redraw()
    {
        updateScore();
        Board::refresh();
    };

    void updateScore()
    {
        mvwprintw(board_win, 1, 4, "%d", curr_len);
        mvwprintw(board_win, 1, 6, "/");
        mvwprintw(board_win, 1, 8, "%d", max_len);
        
        mvwprintw(board_win, 2, 4, "%d", plus_item);
        mvwprintw(board_win, 3, 4, "%d", minus_item);
        mvwprintw(board_win, 4, 4, "%d", gate);
    }

    void updateLen(int len)
    {
        if(len>max_len)
        {
            max_len = len;
        }
        curr_len = len;
    }

    void updatePlus()
    {
        plus_item++;
    }

    void updateMinus()
    {
        minus_item++;
    }
    void updateGate()
    {
        gate++;
    }

    int getLen()
    {
        return max_len;
    }

    int getPlus()
    {
        return plus_item;
    }

     int getMinus()
    {
        return minus_item;
    }

     int getGate()
    {
        return gate;
    }
private:

};


