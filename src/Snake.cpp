#include "Snake.h"

Snake::Snake(LOC& head, int length): head(head), length(length){
    direct = 'a';
    opposite = 'd';
    for(int i=1; i<length+1; i++){
        body.push_back(LOC{head[1], head[0]+i});
    }
    inc = {0, -1};
}

void Snake::setDirection(char key){
    // 진행방향과 같은 입력이 들어오면 무시
    if (direct == key) return;
    if (key == opposite) return;

    switch (key){
    case 'a': direct='a'; opposite = 'd'; inc = {0, -1}; break;
    case 'w': direct='w'; opposite = 's'; inc = {-1, 0}; break;
    case 's': direct='s'; opposite = 'w'; inc = {1, 0}; break;
    case 'd': direct='d'; opposite = 'a'; inc = {0, 1}; break;
    default: break;
    }
}

void Snake::move(){
    // std::lock_guard<std::mutex> lck(bodyMutex);
    body.insert(body.begin(), head);
    prev = *(body.end()-1);
    body.pop_back();
    head.y += inc.y; head.x += inc.x;
    }

void Snake::grow(LOC& item_loc){
    //*(body.end()-1)은 invislbe 하지만, 증가를 나타내기 위해 필요함
    body.push_back(prev);
    head = item_loc;
    length++;
}

void Snake::shrink(LOC& item_loc){
    body.pop_back();
    length--;
}

bool Snake::isDumpedBody(){
    std::vector<LOC>::iterator it = body.begin();
    for(it; it!=body.end()-1; it++){
        if(head ==*it) return true;
    }
    return false;
}

bool Snake::isDumpedWall(Map& map){
    //바깥 테두리에 걸릴 때
    if(head[1]<=1 || head[1]>=map.size_y-1 || head[0]<=1 || head[0]>=map.size_x-1) return true;
    return false;
}

bool Snake::pressedOps(char key){
    return (key==opposite) ? true : false;
}

bool Snake::isFailed(Map& map, char key){
    if (isDumpedBody()|| isDumpedWall(map) || pressedOps(key)|| length<3){
        length = -1; return true;
    }
    return false;
}