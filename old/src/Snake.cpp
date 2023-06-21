#include "Snake.h"

//constructor:

Snake::Snake(LOC& head, int length){
    initialize(head, length);
}

// initializer:

// init all memeber variables
void Snake::initialize(LOC& head, int length){
    this->head = head;
    this->length = length;
    direct = 'a';
    opposite = 'd';
    body.clear();
    for(int i=1; i<length; i++){
        body.push_back(LOC{head[1], head[0]+i});
    }
    prev = LOC{head[1], head[0]+length};
    inc = {0, -1};
    n_gate = 0; n_pItem = 0; n_gItem = 0;
}

// move functions:

// control direct, opposite, inc depending on key
void Snake::control(char key){
    // neglect if key equals to direct or opposite
    if (direct == key) return;
    if (key == opposite) return;

    // change direct, opposite, inc depending on key
    switch (key){
    case 'a': setDirection('a', 'd', {0, -1}); break;
    case 'w': setDirection('w', 's', {-1, 0}); break;
    case 's': setDirection('s', 'w', {1, 0}); break;
    case 'd': setDirection('d', 'a', {0, 1}); break;
    default : break;
    }
}

// put head in the front part of body, 
// and move snake's head by adding inc to head,
// and remove the last part of body(tail).
void Snake::move(){
    body.insert(body.begin(), head);
    prev = *(body.end()-1);
    body.pop_back();
    head.y += inc.y; head.x += inc.x;
}
// event functions: 

// by setting head loc growth item loc and
// appending prev to tail,
// this make snake looks like growing up
void Snake::grow(LOC& item_loc){
    body.push_back(prev);
    head = item_loc;
    length++; ++n_gItem;
}

// by removing tail(the end part of body),
// this make snake looks shrunk
void Snake::shrink(LOC& item_loc){

    body.pop_back();
    length--; ++n_pItem;
}

// set variables:

//set direct, opposite, inc
void Snake::setDirection(const char direct, const char ops, const LOC& inc){
    this->direct = direct;
    this->opposite = ops;
    this->inc = inc;
}

//set direct, opposite by inc(loc)
void Snake::setDirection(const LOC& loc){
    if(loc == LOC{0, 1}) setDirection('d', 'a', loc);
    else if(loc == LOC{1, 0}) setDirection('s', 'w', loc);
    else if(loc == LOC{0, -1}) setDirection('a', 'd', loc);
    else setDirection('w', 's', loc);
}

// check fail condition:

// check if snake's head bumped into its body
bool Snake::isDumpedBody(){
    std::vector<LOC>::iterator it = body.begin();
    for(it; it!=body.end()-1; it++){
        if(head ==*it) return true;
    }
    return false;
}

// check if snake's head bumped into all walls
bool Snake::isDumpedWall(Map& map, LOC gate_loc1, LOC gate_loc2, bool gate_active){
    // not fail-> when snake goes through the gate
    if(gate_active&&(head == gate_loc1 || head == gate_loc2)) return false;
    
    // fail-> when head bumped into ouline walls
    if(head[1]<1 || head[1]>=map.size_y-1 || head[0]<1 || head[0]>=map.size_x-1) return true;
    
    // fail-> when head bumped into the inner walls(not outline walls)
    if(headIn(map.imwalls, map.imw_size) || headIn(map.walls, map.w_size)) return true;
    
    return false;
}

// check if user pressed the key of which direction is snake's opposite
bool Snake::pressedOps(char key){
    return (key==opposite) ? true : false;
}

// fail-> when head bumped into the inner walls(blocks, not outline walls)
bool Snake::headIn(LOC* blocks, int size){
    for(int i=0; i<size; i++) if(head==blocks[i]) return true;
    return false;
}

// check all conditions above and return whether it is failed or not.
bool Snake::isFailed(Map& map, LOC gate_loc1, LOC gate_loc2, bool gate_active, char key){
    if (isDumpedBody()|| isDumpedWall(map, gate_loc1, gate_loc2, gate_active) || pressedOps(key)|| length<3){
        return true;
    }
    return false;
}