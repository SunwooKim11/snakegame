#include<iostream>
#include<chrono>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<ctime>
#include"LOC.h"
#include"Snake.h"
#include"map.h"

using namespace std::chrono;

#ifndef __ITEM_H__
#define __ITEM_H__

class Item{
public:
    LOC loc;
    std::vector<LOC> toAvoid;
    milliseconds lifecycle;
    milliseconds hiddencycle;
    bool active;
    system_clock::time_point tp;
    std::vector<LOC>::iterator num_blocks;
    LOC outline;

public:
    Item(Map& map, Snake& snake, bool active=false, 
    milliseconds lifecycle = duration_cast<milliseconds>(milliseconds(5000)),
    milliseconds hiddencycle = duration_cast<milliseconds>(milliseconds(1500)));
    void insertToAvoid(Snake& snake);
    void popToAvoid(Snake& snake);
    void updateToAvoid(Snake& snake);
    void setLoc();
// virtual bool beEaten(Snake& snake);
    void setStatus();
virtual const int getColor();

};

#endif