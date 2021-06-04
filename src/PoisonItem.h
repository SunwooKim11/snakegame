#include "Item.h"

#ifndef __POISON_ITEM_H__
#define __POISON_ITEM_H__

class PoisonItem: public Item{

public: 
    const int POISON = 6;

public:
    PoisonItem(Map& map, Snake& snake, bool active=false, 
    duration<milliseconds> lifecycle = duration_cast<duration<milliseconds>>(milliseconds(5000)),
    duration<milliseconds> hiddencycle = duration_cast<duration<milliseconds>>(milliseconds(1500)));

    bool beEaten(Snake& snake){
        if(!active) return false;
        if(snake.head == loc){
            snake.shrink(loc);
        }
    }

    const int getColor(){return POISON;}

};
#endif