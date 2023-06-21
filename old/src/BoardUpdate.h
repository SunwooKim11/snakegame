#include<iostream>
#include<chrono>
#include<mutex>
#include<ncurses.h>
#include<thread>
#include<string>
#include"Snake.h"

using namespace std::chrono;

#ifndef __BOARDUDPATE_H__
#define __BOARDUPDATE_H__

std::mutex dataMutex;

class boardUpdate{
private:
    int stage = 0;
    int maxLength;
    int currLength, n_gate, n_gItem, n_pItem;
    char done_length, done_gate, done_gItem, done_pItem;
    int tn_gate, tn_gItem, tn_pItem; 
    steady_clock::time_point tp; //time point

public: 
    boardUpdate(){
        initialize(0);
    }

    void operator()(WINDOW* scoreBoard, WINDOW* missionBoard, Snake& snake, int& stage){
        wattron(scoreBoard, COLOR_PAIR(2));
        // wattron(missionBoard, COLOR_PAIR(2));
        box(scoreBoard, '|', '-');
        nodelay(scoreBoard, FALSE);
        // box(missionBoard, '|', '-');
        
        while(stage<4){
            if(this->stage<stage) initialize(stage);
            {
            std::lock_guard<std::mutex> lck(dataMutex);
            currLength = snake.getLength();
            n_gate = snake.getN_gate();
            n_gItem = snake.getN_gItem();
            n_pItem = snake.getN_pItem();
            }

            //score board
            mvwprintw(scoreBoard, 1, 1, "            ");
            mvwprintw(scoreBoard, 2, 1, "            ");
            mvwprintw(scoreBoard, 3, 1, "            ");
            mvwprintw(scoreBoard, 4, 1, "            ");
            mvwprintw(scoreBoard, 5, 1, "            ");
            mvwprintw(scoreBoard, 6, 1, "            ");

            mvwprintw(scoreBoard, 1, 1, "Score Board");
            mvwprintw(scoreBoard, 2, 1, "B: %d / %d", currLength, maxLength);
            mvwprintw(scoreBoard, 3, 1, "+: %d", n_gItem);
            mvwprintw(scoreBoard, 4, 1, "-: %d", n_pItem);
            mvwprintw(scoreBoard, 5, 1, "G: %d", n_gate);
            mvwprintw(scoreBoard, 6, 1, "TIME: %d", duration_cast<seconds>(steady_clock::now()-tp).count());
            touchwin(scoreBoard);
            wrefresh(scoreBoard);
            
            if(done_length == ' '&& currLength>=maxLength) done_length = 'V';
            if(done_gate == ' '&& n_gate>=tn_gate) done_gate = 'V';
            if(done_gItem == ' '&& n_gItem>=tn_gItem) done_gItem = 'V';
            if(done_pItem == ' '&& n_pItem>=tn_pItem) done_pItem = 'V';

            //mission board
            // mvwprintw(missionBoard, 1, 1, "Mission Board");
            // mvwprintw(missionBoard, 2, 1, "B: %d (%c)", maxLength, done_length);
            // mvwprintw(missionBoard, 3, 1, "+: %d (%c)", tn_gItem, done_gItem);
            // mvwprintw(missionBoard, 4, 1, "-: %d (%c)", tn_pItem, done_pItem);
            // mvwprintw(missionBoard, 5, 1, "G: %d (%c)", tn_gate, done_gate);
            // touchwin(missionBoard);
            // wrefresh(missionBoard);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        wattroff(scoreBoard, COLOR_PAIR(2));
        // wattroff(missionBoard, COLOR_PAIR(2));

    }
private:
    void initialize(int stage){
        tp = steady_clock::now();
        this->stage = stage;
        // currLength = snake.getLength();  // -> 수정 필요
        currLength = 3;
        n_gate = n_pItem = n_gItem = 0;
        tn_gate = 1 + stage;
        tn_gItem = 5 + stage;
        tn_pItem = 2 + stage;
        maxLength = 10 + stage;
        done_length = ' ', done_gate = ' ', done_gItem = ' ', done_pItem = ' ';
    }
};
#endif