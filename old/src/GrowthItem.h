#include "Item.h"

#ifndef __GROWTH_ITEM_H__
#define __GROWTH_ITEM_H__

class GrowthItem: public Item{
private:
    const int GROWTH = 5;

public:
    GrowthItem(Map& map, Snake& snake)
    :Item(map, snake){};   
    
    // event function:
    // check if snake head equals to the location of growth item.
    // and if true, make snake grow up.
    bool beEaten(Snake& snake){
        if(snake.getHead() == loc){
            snake.grow(loc);
            return true;
        }
        return false;
    }
    // getter:
    const int getColor(){return GROWTH;}

    // destructor:
    ~GrowthItem(){};
};

#endif