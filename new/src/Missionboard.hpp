#pragma once

#include<cstdlib>
#include<time.h>
#include "Board.hpp"

#define GOAL 3
class Missionboard : public Board
{
private:
    int max_len = 5;
    int plus_item = 1, minus_item = 1;
    int gate = 1;

    int completed = 0;

    char* v_max_len = " ";
    char* v_plus_item = " ";
    char* v_minus_item = " ";
    char* v_gate = " ";
public: 
    Missionboard(){};
    Missionboard(int height, int width, int startY , int startX) : Board(height, width, startY, startX)
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
        mvwprintw(board_win, 0, 1, "Mission Board");
        mvwprintw(board_win, 1, 1, "B:"); mvwprintw(board_win, 1, 4, "%d", max_len); mvwprintw(board_win, 1, 7, "( )"); 
        mvwprintw(board_win, 2, 1, "+:"); mvwprintw(board_win, 2, 4, "%d", plus_item); mvwprintw(board_win, 2, 7, "( )"); 
        mvwprintw(board_win, 3, 1, "-:"); mvwprintw(board_win, 3, 4, "%d", minus_item); mvwprintw(board_win, 3, 7, "( )"); 
        mvwprintw(board_win, 4, 1, "G:"); mvwprintw(board_win, 4, 4, "%d", gate); mvwprintw(board_win, 4, 7, "( ) "); 
    }
    
    void redraw()
    {
        updateMission();
        Board::refresh();
    };

    void updateMission()
    {
        mvwprintw(board_win, 1, 8, v_max_len);
        mvwprintw(board_win, 2, 8, v_plus_item);
        mvwprintw(board_win, 3, 8, v_minus_item);
        mvwprintw(board_win, 4, 8, v_gate);

        if (completed >= GOAL) drawCompleted();
    }

    void updateLen(int gate)
    {
        if(gate == max_len)
        {
            v_max_len = "v";
            completed++;
        }
        
    }

    void updatePlus(int plus_item)
    {
        if(plus_item == this->plus_item)
        {
            v_plus_item = "v";
            completed++;
        }
        
    }

    void updateMinus(int minus_item)
    {
        if(minus_item == this->minus_item)
        {
            v_minus_item = "v";
            completed++;    
        }
        
    }

    void updateGate(int gate)
    {
        if(gate == this->gate)
        {
            v_gate = "v";
            completed++;
        }
        
    }

    void drawCompleted()
    {
        mvwprintw(board_win, 6, 9, "Success!");
    }

};


