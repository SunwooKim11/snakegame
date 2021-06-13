#include "Item.h"

Item::Item(Map& map, Snake& snake, bool active, int lifecycle, int hiddencycle)
:lifecycle(lifecycle), hiddencycle(hiddencycle){
    initialize(map, snake, active);
    srand(tp.time_since_epoch().count()%10000);
}

void Item::initialize(Map& map, Snake& snake, bool active){
    this->loc = {1, 1};
    this->active = active;
    if(toAvoid.size()>0) toAvoid.clear(); // make toAvoid empty
    // insert locations of walls and immune walls into toAvoid.
    for(int i=0; i<map.imw_size; i++) toAvoid.push_back(*(map.imwalls + i));
    for(int i=0; i<map.w_size; i++) toAvoid.push_back(*(map.walls + i));
    outline = LOC{map.size_y-1, map.size_x-1};
    num_blocks = toAvoid.end();
    insertToAvoid(snake);
    tp = steady_clock::now();   // time point
}
// event handler:
// insert locations of current snake into toAvoid.
void Item::insertToAvoid(Snake& snake){
    toAvoid.push_back(snake.getHead());
    toAvoid.insert(toAvoid.end(), snake.getBody().begin(), snake.getBody().end());
}
// remove locations of previous snake form toAvoid.
void Item::popToAvoid(Snake& snake){
    toAvoid.erase(num_blocks, num_blocks+snake.getLength());
}
// update toAvoid.
void Item::updateToAvoid(Snake& snake){
    popToAvoid(snake);
    insertToAvoid(snake);
}
// set values(active, tp, loc) depending on event.
void Item::setStatus(Snake& snake){
    // check if item is eaten by snake.
    bool eaten = beEaten(snake);
    if((!active) && // when item is invisble and time > hiddencycle 
    (duration_cast<milliseconds>(steady_clock::now()-tp).count() > hiddencycle)){
        // make item vislble, update tp and loc.
        active = true; 
        tp = steady_clock::now(); 
        setLoc();
        return;
    }

    if(eaten || (active && // when item is visble and time > lifecycle or eaten by snake.
    (duration_cast<milliseconds>(steady_clock::now()-tp).count() > lifecycle))){
        // make item invisible, update tp.
        active = false; 
        tp = steady_clock::now();
        return;
    }

}

void Item::setLoc(){
    // generate random loc.
    // if the obtained loc in toAvoid, regenerate
    // repeat this proecess.
    std::vector<LOC>::iterator tmp;
    do{
        int y = rand()%outline.y;
        int x = rand()%outline.x;
        y = (y) ? y: y+1;
        x = (x) ? x: x+1;
        loc = LOC{y, x};
        tmp = find(toAvoid.begin(), toAvoid.end(), loc);
    }while(toAvoid.end() != tmp);
}
