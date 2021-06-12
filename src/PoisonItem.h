#include "Item.h"

#ifndef __POISON_ITEM_H__
#define __POISON_ITEM_H__

class PoisonItem: public Item{

public: 
    const int POISON = 6;

public:
    PoisonItem(Map& map, Snake& snake)
    :Item(map, snake)
    {};

    bool beEaten(Snake& snake){
        if(snake.getHead() == loc){
            snake.shrink(loc);
            return true;
        }
        return false;
    }

    const int getColor(){return POISON;}

    ~PoisonItem(){
        // std::cout <<"~Poision Item" << std::endl;
    }

};
#endif