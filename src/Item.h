#include<iostream>
#include<chrono>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include"LOC.h"
#include"Snake.h"
#include"map.h"

using namespace std::chrono;

#ifndef __ITEM_H__
#define __ITEM_H__

class Item{
protected:
    LOC loc;
    std::vector<LOC> toAvoid;
    int lifecycle;
    int hiddencycle;
    bool active;
    steady_clock::time_point tp; //time point
    std::vector<LOC>::iterator num_blocks;
    LOC outline;

public:
    // consturctor
    Item(Map& map, Snake& snake, bool active=false, 
    int lifecycle = milliseconds(10000).count(),
    int hiddencycle = milliseconds(1500).count());

    // initializer
    void initialize(Map& map, Snake& snake, bool active = false);

    // event handler
    void insertToAvoid(Snake& snake);
    void popToAvoid(Snake& snake);
    void updateToAvoid(Snake& snake);
    void setStatus(Snake& snake);

    // setter
    void setLoc();

    // getter
    bool getActive(){return active;}
    LOC& getLoc(){return loc;}

    // event function
virtual bool beEaten(Snake& snake){return true;};
virtual const int getColor(){return 1;};
virtual ~Item(){
        toAvoid.clear();
        // std::cout <<"~Item" << std::endl;
        // std::vector().swap(toAvoid);
    }
};

#endif