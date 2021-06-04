#include "Item.h"

Item::Item(Map& map, Snake& snake, bool active, milliseconds lifecycle, milliseconds hiddencycle): 
loc({1,1}), active(active), lifecycle(lifecycle), hiddencycle(hiddencycle){
    toAvoid.insert(toAvoid.end(), &(map.imwalls[0]), &(map.imwalls[map.imw_size])); 
    toAvoid.insert(toAvoid.end(), &(map.walls[0]), &(map.walls[map.w_size]));    
    outline = {map.size_y-1, map.size_x-1};
    num_blocks = toAvoid.end();
    insertToAvoid(snake);
    srand(time(NULL));
    tp = system_clock::now();
}

void Item::insertToAvoid(Snake& snake){
    toAvoid.push_back(snake.head);
    toAvoid.insert(toAvoid.end(), snake.body.begin(), snake.body.end());
}

void Item::popToAvoid(Snake& snake){
    toAvoid.erase(num_blocks, num_blocks+snake.length);
}

void Item::updateToAvoid(Snake& snake){
    popToAvoid(snake);
    insertToAvoid(snake);
}

void Item::setLoc(){
    do{
        loc = {rand()%outline[0]+1, rand()%outline[1]+1};
    }while(find(toAvoid.begin(), toAvoid.end(), loc)!=toAvoid.end());
}

// bool Item::beEaten(Snake& snake){
//     if(!active) return false;
//     if(snake.head == loc){
//         // snake.getItem(*this); 
//         active=false;
//     }
//     return false;
// }

void Item::setStatus(){
    if(!(active) && // Item이 invisible한 상태일 때 
    duration_cast<milliseconds>(system_clock::now()- tp).count() >= hiddencycle.count()){
        active = true; setLoc(); tp = system_clock::now(); return;
    }
    if(active && // Item이 visible한 상태일 때
    duration_cast<milliseconds>(system_clock::now()-tp).count()>= lifecycle.count()){
        active = false; tp = system_clock::now(); return;
    }

}

