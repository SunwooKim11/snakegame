#include "Item.h"

Item::Item(Map& map, Snake& snake, bool active, int lifecycle, int hiddencycle)
:lifecycle(lifecycle), hiddencycle(hiddencycle){
    initialize(map, snake, active);
    srand(tp.time_since_epoch().count()%10000);

}

void Item::initialize(Map& map, Snake& snake, bool active){
    this->loc = {1, 1};
    this->active = active;
    toAvoid.clear();
    toAvoid.insert(toAvoid.end(), map.imwalls, map.imwalls + map.imw_size); 
    toAvoid.insert(toAvoid.end(), map.walls, map.walls + map.w_size);    
    outline = LOC{map.size_y-1, map.size_x-1};
    num_blocks = toAvoid.end();
    insertToAvoid(snake);
    tp = steady_clock::now();
}

void Item::insertToAvoid(Snake& snake){
    toAvoid.push_back(snake.getHead());
    toAvoid.insert(toAvoid.end(), snake.getBody().begin(), snake.getBody().end());
}

void Item::popToAvoid(Snake& snake){
    toAvoid.erase(num_blocks, num_blocks+snake.getLength());
}

void Item::updateToAvoid(Snake& snake){
    popToAvoid(snake);
    insertToAvoid(snake);
}

void Item::setLoc(){
    // find로 찾았다면다시 loc 생성
    std::vector<LOC>::iterator tmp;
    do{
        //여기 해결 필요
        int y = rand()%outline.y;
        int x = rand()%outline.x;
        y = (y) ? y: y+1;
        x = (x) ? x: x+1;
        loc = LOC{y, x};
        tmp = find(toAvoid.begin(), toAvoid.end(), loc);
    }while(toAvoid.end() == tmp);
}

// bool Item::beEaten(Snake& snake){
//     if(!active) return false;
//     if(snake.getHead() == loc){
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
