#include "Snake.h"

Snake::Snake(LOC& head, int length): head(head), life(1){
    direct = 'a';
    opposite = 'd';
    body.push_back(LOC {head[1], head[0]+1});
    body.push_back(LOC {head[1], head[0]+2});
    inc = {0, -1};
}

void Snake::setDirection(char key){
    // 진행방향과 같은 입력이 들어오면 무시
    if (direct == key) return;
    if (direct == opposite) return;

    switch (key){
    case 'a': opposite = 'd'; inc = {0, -1}; break;
    case 'w': opposite = 's'; inc = {1, 0}; break;
    case 's': opposite = 'w'; inc = {-1, 0}; break;
    case 'd': opposite = 'a'; inc = {0, 1}; break;
    default: break;
    }
}

void Snake::move(){
    // std::lock_guard<std::mutex> lck(bodyMutex);
    body.insert(body.begin(), head);
    body.pop_back();
    head.y += inc.y; head.x += inc.x;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }


bool Snake::isDumpedBody(){
    std::vector<LOC>::iterator it = body.begin();
    for(it; it<body.end(); it++){
        if(head !=*it) return true;
    }
    return false;
}

bool Snake::isDumpedWall(Map& map){
    //바깥 테두리에 걸릴 때
    if(head[1]<=0 || head[1]>=map.size_y || head[0]<=0 || head[0]>=map.size_x) return true;
    return false;
}

bool Snake::pressedOps(char key){
    return (key==opposite) ? true : false;
}

bool Snake::isFailed(Map& map, char key){
    if (isDumpedBody()|| isDumpedWall(map) || pressedOps(key)){
        life = 0; return true;
    }
    return false;
}