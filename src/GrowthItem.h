#include "Item.h"

#ifndef __GROWTH_ITEM_H__
#define __GROWTH_ITEM_H__

class GrowthItem: public Item{

public:
    const int GROWTH = 5;

public:
    GrowthItem(Map& map, Snake& snake)
    :Item(map, snake)
    {};   
    
    bool beEaten(Snake& snake){
        if(snake.getHead() == loc){
            snake.grow(loc);
            return true;
        }
        return false;
    }

    const int getColor(){return GROWTH;}

    ~GrowthItem(){
        // std::cout <<"~Growth Item" << std::endl;
    };
};

#endif