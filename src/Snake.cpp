#include "Snake.h"

//constructor -> 문제 없는지 확인필요
Snake::Snake(LOC& head, int length){
    initialize(head, length);
}

// initializer
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
}

// move functions
void Snake::control(char key){
    // 진행방향과 같은 입력이 들어오면 무시
    if (direct == key) return;
    if (key == opposite) return;

    switch (key){
    case 'a': setDirection('a', 'd', {0, -1}); break;
    case 'w': setDirection('w', 's', {-1, 0}); break;
    case 's': setDirection('s', 'w', {1, 0}); break;
    case 'd': setDirection('d', 'a', {0, 1}); break;
    default : break;
    /*
    case 'a': direct='a'; opposite = 'd'; inc = {0, -1}; break;
    case 'w': direct='w'; opposite = 's'; inc = {-1, 0}; break;
    case 's': direct='s'; opposite = 'w'; inc = {1, 0}; break;
    case 'd': direct='d'; opposite = 'a'; inc = {0, 1}; break; */
    }
}

void Snake::move(){
    // std::lock_guard<std::mutex> lck(bodyMutex);
    body.insert(body.begin(), head);
    prev = *(body.end()-1);
    body.pop_back();
    head.y += inc.y; head.x += inc.x;
}

// event functions: get Item
void Snake::grow(LOC& item_loc){
    //*(body.end()-1)은 invislbe 하지만, 증가를 나타내기 위해 필요함
    body.push_back(prev);
    head = item_loc;
    length++; ++n_gItem;
}

void Snake::shrink(LOC& item_loc){
    body.pop_back();
    length--; ++n_pItem;
}

// set variables
void Snake::setDirection(const char direct, const char ops, const LOC& inc){
    this->direct = direct;
    this->opposite = ops;
    this->inc = inc;
}
void Snake::setDirection(const LOC& loc){
    if(loc == LOC{0, 1}) setDirection('d', 'a', loc);
    else if(loc == LOC{1, 0}) setDirection('s', 'w', loc);
    else if(loc == LOC{0, -1}) setDirection('a', 'd', loc);
    else setDirection('w', 's', loc);
}

// check fail condition
bool Snake::isDumpedBody(){
    std::vector<LOC>::iterator it = body.begin();
    for(it; it!=body.end()-1; it++){
        if(head ==*it) return true;
    }
    return false;
}

bool Snake::isDumpedWall(Map& map, LOC gate_loc1, LOC gate_loc2, bool gate_active){
    //게이트를 통과할 때
    if(gate_active&&(head == gate_loc1 || head == gate_loc2)) return false;
    
    //바깥 테두리에 걸릴 때
    if(head[1]<1 || head[1]>=map.size_y-1 || head[0]<1 || head[0]>=map.size_x-1) return true;
    
    // 맵 내무 벽에 걸릴 때
    if(headIn(map.imwalls, map.imw_size) || headIn(map.walls, map.w_size)) return true;
    
    return false;
}

bool Snake::pressedOps(char key){
    return (key==opposite) ? true : false;
}

bool Snake::headIn(LOC* blocks, int size){
    for(int i=0; i<size; i++) if(head==blocks[i]) return true;
    return false;
}

bool Snake::isFailed(Map& map, LOC gate_loc1, LOC gate_loc2, bool gate_active, char key){
    if (isDumpedBody()|| isDumpedWall(map, gate_loc1, gate_loc2, gate_active) || pressedOps(key)|| length<3){
        return true;
    }
    return false;
}