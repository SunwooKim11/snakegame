#include<iostream>
#include<chrono>
#include<cstdlib>
#include<algorithm>
#include"LOC.h"
#include"Snake.h"
#include"Map.h"

using namespace std::chrono;

#ifndef __GATE_H__
#define __GATE_H__

class Gate{
private:
    LOC loc1, loc2;
    LOC entrace, exit;

    // the location of head just before snake enters the gate.
    // used in checking if snake is going through the gate.
    LOC enteredSpace; 
    bool active, passing;
    int lifecycle;
    int hiddencycle;
    steady_clock::time_point tp; // time point
    
    const int GATE = 7;
    // exit direction priority
    const LOC EXIT_DIRECT[4][4] = {
        // based on snake's entry direction
        {{0, -1}, {-1, 0}, {1, 0}, {0, 1}}, // left
        {{-1, 0}, {0, 1}, {0, -1}, {1, 0}}, // up
        {{0, 1}, {1, 0}, {-1, 0}, {0, -1}}, // right
        {{1, 0}, {0, -1}, {0, 1}, {-1, 0}} // down
    };

public:
    //constructor:
    Gate(bool active = false, bool passing = false,
    int lifecycle = milliseconds(20000).count(),
    int hiddencycle = milliseconds(4000).count());

    // initializer:
    void initialize(bool active = false, bool passing = false);

    // event handler:

    // handle status when snake enters the gate
    bool snakeEntered(Map& map, Snake& snake);
    // check if snake is going through the gate.
    bool snakePassing(Snake& snake);
    // set values(active, tp, loc) depending on event.
    void setStatus(Map& map, Snake& snake);

    // setter:
    // for not gates overlapping, if loc1 equals to loc1 repeat randomLOC()
    void setLoc(Map& map);

    // getter:
    const int getColor(){return GATE;}
    bool getActive(){return active;}
    LOC& getLoc1(){return loc1;}
    LOC& getLoc2(){return loc2;}

private:
//  generate randoom loc
    LOC randomLOC(Map& map);
};


#endif