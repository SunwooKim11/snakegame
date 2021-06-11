#include "Item.h"

Item::Item(Map& map, Snake& snake, bool active, int lifecycle, int hiddencycle): 
loc({1,1}), active(active), lifecycle(lifecycle), hiddencycle(hiddencycle){
    toAvoid.insert(toAvoid.end(), &(map.imwalls[0]), &(map.imwalls[map.imw_size])); 
    toAvoid.insert(toAvoid.end(), &(map.walls[0]), &(map.walls[map.w_size]));    
    outline = LOC{map.size_y-1, map.size_x-1};
    num_blocks = toAvoid.end();
    insertToAvoid(snake);
    srand(2);
    tp = steady_clock::now();
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
    // find로 찾았다면다시 loc 생성
    do{
        loc = LOC{rand()%outline.y+1, rand()%outline.x+1};
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

void Item::setStatus(Snake& snake){
    bool eaten = beEaten(snake);

    if((!active) && // Item이 invisible한 상태일 때 
    (duration_cast<milliseconds>(steady_clock::now()-tp).count() > hiddencycle)){
        active = true; 
        tp = steady_clock::now(); 
        setLoc();
        return;
    }


    if(eaten || (active && // Item이 visible한 상태일 때
    (duration_cast<milliseconds>(steady_clock::now()-tp).count() > lifecycle))){
        active = false; 
        tp = steady_clock::now();
        return;
    }

}
