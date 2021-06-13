#include "Item.h"

#ifndef __POISON_ITEM_H__
#define __POISON_ITEM_H__

class PoisonItem: public Item{

private: 
    const int POISON = 6;

public:
    PoisonItem(Map& map, Snake& snake)
    :Item(map, snake){};
    // event function:
    // check if snake head equals to the location of poision item.
    // and if true, make snake shrunk.
    bool beEaten(Snake& snake){
        if(snake.getHead() == loc){
            snake.shrink(loc);
            return true;
        }
        return false;
    }

    const int getColor(){return POISON;}

    ~PoisonItem(){}

};
#endif