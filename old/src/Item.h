#include<chrono>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include"LOC.h"
#include"Snake.h"
#include"Map.h"

using namespace std::chrono;

#ifndef __ITEM_H__
#define __ITEM_H__

class Item{
protected:
    LOC loc;
    std::vector<LOC> toAvoid; // locations of imwalls, walls and snake
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
    int hiddencycle = milliseconds(2000).count());

    // initializer
    void initialize(Map& map, Snake& snake, bool active = false);

    // event handler: 
    // insert locations of current snake into toAvoid.
    void insertToAvoid(Snake& snake);
    // remove locations of previous snake form toAvoid.
    void popToAvoid(Snake& snake);
    // update toAvoid.
    void updateToAvoid(Snake& snake);
    // set values(active, tp, loc) depending on event.
    void setStatus(Snake& snake);

    // setter:
    // set item loc
    void setLoc();

    // getter:
    bool getActive(){return active;}
    LOC getLoc(){return loc;}

    // event function:
    // dummy function for subclass event function
virtual bool beEaten(Snake& snake){return true;};
    // dummy function for getting subclass color
virtual const int getColor(){return 1;};
    // destructor
virtual ~Item(){
        toAvoid.clear();
    }
};

#endif