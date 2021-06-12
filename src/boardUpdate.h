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
    std::string tmp ;
    int currLength, n_gate, n_gItem, n_pItem;
    char done_length, done_gate, done_gItem, done_pItem;
    int tn_gate, tn_gItem, tn_pItem; 
    steady_clock::time_point tp; //time point

public: 
    boardUpdate(Snake& snake){
        initialize(snake, 0);
    }

    void operator()(WINDOW* scoreBoard, WINDOW* missionBoard, Snake& snake, int stage){
        wattron(scoreBoard, COLOR_PAIR(2));
        wattron(missionBoard, COLOR_PAIR(2));
        box(scoreBoard, '|', '-');
        box(scoreBoard, '|', '-');
        
        {std::lock_guard<std::mutex> lck(dataMutex);
        while(this->stage<4){
            if(this->stage<stage) initialize(snake, stage);

            currLength = snake.getLength();
            n_gate = snake.getN_gate();
            n_gItem = snake.getN_gItem();
            n_pItem = snake.getN_pItem();

            //score board
            mvwprintw(scoreBoard, 1, 1, "Score Board");
            tmp = "B: "+std::to_string(currLength)+" / "+std::to_string(maxLength);
            mvwprintw(scoreBoard, 2, 1, tmp);
            mvwprintw(scoreBoard, 3, 1, std::format("+: {}", n_gate));
            mvwprintw(scoreBoard, 4, 1, std::format("-: {}", n_gItem));
            mvwprintw(scoreBoard, 4, 1, std::format("G: {}", n_pItem));
            mvwprintw(scoreBoard, 5, 1, std::format("TIME: {}", duration_cast<seconds>(steady_clock::now()-tp).count());

            if(done_length == ''&& currLength>=maxLength) done_length = 'V';
            if(done_gate == ''&& n_gate>=tn_gate) done_gate = 'V';
            if(done_gItem == ''&& n_gItem>=tn_gItem) done_gItem = 'V';
            if(done_pItem == ''&& n_pItem>=tn_pItem) done_pItem = 'V';

            //mission board
            mvwprintw(missionBoard, 1, 1, "Mission Board");
            mvwprintw(missionBoard, 2, 1, std::format("B: {} ({})", maxLength, done_length));
            mvwprintw(missionBoard, 3, 1, std::format("+: {} ({})", tn_gItem, done_gItem));
            mvwprintw(missionBoard, 4, 1, std::format("-: {} ({})", tn_pItem, done_pItem));
            mvwprintw(missionBoard, 5, 1, std::format("G: {} ({})", tn_gate, done_gate));

        }}
        wattroff(scoreBoard, COLOR_PAIR(2));
        wattroff(missionBoard, COLOR_PAIR(2));

    }
private:
    void initialize(Snake& snake, int stage){
        tp = steady_clock::now();
        currLength = snake.getLength();  // -> 수정 필요
        n_gate = n_pItem = n_gItem = 0;
        tn_gate = 1 + stage;
        tn_gItem = 5 + stage;
        tn_pItem = 2 + stage;
        maxLength = 10 + stage;
        done_length = '', done_gate = '', done_gItem = '', done_pItem = '';
    }
};
#endif