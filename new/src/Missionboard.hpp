#pragma once

#include<cstdlib>
#include<time.h>
#include "Board.hpp"

#define GOAL 3
class Missionboard : public Board
{
    
private:
    int arr_max_len[4] = {5, 4, 4, 5};
    int arr_plus_item[4] = {1, 1, 1, 0};
    int arr_minus_item[4] = {1, 1, 0, 0};
    int arr_gate[4] = {1, 0, 0, 0};

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
    void initialize(int stage)
    {   
        initValue(stage);
        clear(stage);
        redraw();

        
    };

    void initValue(int stage)
    {
        completed = 0;
        max_len = arr_max_len[stage];
        plus_item = arr_plus_item[stage];
        minus_item = arr_minus_item[stage];
        gate = arr_gate[stage];

        v_max_len = " ";
        v_plus_item = " ";
        v_minus_item = " ";
        v_gate = " ";
    };

    void clear(int stage)
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

    bool updateMission()
    {
        mvwprintw(board_win, 1, 8, v_max_len);
        mvwprintw(board_win, 2, 8, v_plus_item);
        mvwprintw(board_win, 3, 8, v_minus_item);
        mvwprintw(board_win, 4, 8, v_gate);

        if (completed >= GOAL) return true;
        else return false;
    }

    void updateLen(int len)
    {
        if(v_max_len != "v" && len >= max_len)
        {
            v_max_len = "v";
            completed++;
        }
        
    }

    void updatePlus(int plus_item)
    {
        if(v_plus_item != "v" && plus_item >= this->plus_item)
        {
            v_plus_item = "v";
            completed++;
        }
        
    }

    void updateMinus(int minus_item)
    {
        if(v_minus_item != "v" && minus_item >= this->minus_item)
        {
            v_minus_item = "v";
            completed++;    
        }
        
    }

    void updateGate(int gate)
    {
        if(v_gate != "v" && gate >= this->gate)
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


