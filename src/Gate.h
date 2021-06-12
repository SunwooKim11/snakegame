#include<iostream>
#include<chrono>
#include<cstdlib>
#include<algorithm>
#include"LOC.h"
#include"Snake.h"
#include"map.h"

using namespace std::chrono;

#ifndef __GATE_H__
#define __GATE_H__

class Gate{
private:
    LOC loc1, loc2;
    LOC entrace, exit;
    LOC enteredSpace;
    bool active, passing;
    int lifecycle;
    int hiddencycle;
    steady_clock::time_point tp; // time point
    
    const int GATE = 7;
    const LOC EXIT_DIRECT[4][4] = {
        // 진행 방향 기준
        {{0, -1}, {-1, 0}, {1, 0}, {0, 1}}, // 왼쪽
        {{-1, 0}, {0, 1}, {0, -1}, {1, 0}}, // 위
        {{0, 1}, {1, 0}, {-1, 0}, {0, -1}}, /// 오른쪽
        {{1, 0}, {0, -1}, {0, 1}, {-1, 0}} // 아래
    };

public:
    //constructor
    Gate(bool active = false, bool passing = false,
    int lifecycle = milliseconds(20000).count(),
    int hiddencycle = milliseconds(4000).count());

    // initializer
    void initialize(bool active = false, bool passing = false);

    // event handler
    bool snakeEntered(Map& map, Snake& snake);
    bool snakePassing(Snake& snake);
    void setStatus(Map& map, Snake& snake);

    // setter
    void setLoc(Map& map);

    // getter
    const int getColor(){return GATE;}
    bool getActive(){return active;}
    LOC& getLoc1(){return loc1;}
    LOC& getLoc2(){return loc2;}

private:
    LOC randomLOC(Map& map);
};


#endif