#include "Item.h"

#ifndef __GROWTH_ITEM_H__
#define __GROWTH_ITEM_H__

class GrowthItem: public Item{

public:
    const int GROWTH = 5;

public:
    GrowthItem(Map& map, Snake& snake, bool active=false, 
    duration<milliseconds> lifecycle = duration_cast<duration<milliseconds>>(milliseconds(5000)),
    duration<milliseconds> hiddencycle = duration_cast<duration<milliseconds>>(milliseconds(1500)));
   
    bool beEaten(Snake& snake){
        if(!active) return false;
        if(snake.head == loc){
            snake.grow(loc);
        }
    }

    const int getColor(){return GROWTH;}
};

#endif