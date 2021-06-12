#include "Gate.h"

Gate::Gate(bool active, bool passing, int lifecycle, int hiddencycle)
:active(active), passing(passing), lifecycle(lifecycle), hiddencycle(hiddencycle){}

void Gate::initialize(bool active, bool passing){
    this->active = active; this->passing = passing;
}

bool Gate::snakeEntered(Map& map, Snake& snake){
    // 들어 오지 않았을 때
    if(!(snake.getHead() == loc1 || snake.getHead() == loc2)){
        return false;
    }

    // 들어 왔을 때
    passing = true;
    enteredSpace = snake.getBody()[0];
    snake.setN_gate();
    if(snake.getHead() == loc1){
        entrace = loc1; exit = loc2; 
    } else{
        entrace = loc2; exit = loc1;
    }

    if(exit.x == 0){ // 왼쪽 테두리
        snake.setHead({exit.y, exit.x+1});
        snake.setDirection('d', 'a', {0, 1});
    }
    else if(exit.y == 0){ // 위쪽 테두리
        snake.setHead({exit.y+1, exit.x});
        snake.setDirection('s', 'w', {1, 0});
    }
    else if(exit.x == map.size_x-1){ // 오른쪽 테두리
        snake.setHead({exit.y, exit.x-1});
        snake.setDirection('a', 'd', {0, -1});
    }
    else if(exit.y == map.size_y-1){ // 아래쪽 테두리
        snake.setHead({exit.y-1, exit.x});
        snake.setDirection('w', 's', {-1, 0});
    }
    else{ // 내부에 있을 때
      int idx1, idx2 = -1;
      LOC tmp;
    // 방향을 알아차림
        switch(snake.getDirect()){
          case 'a': idx1 = 0; break;
          case 'w': idx1 = 1; break;
          case 'd': idx1 = 2; break;
          case 's': idx1 = 3; break;
      }  

    // 진출하는 곳이 벽이 아닐 때 까지 우선순위대로 진출하는 곳 결정
      do{
          tmp = EXIT_DIRECT[idx1][++idx2];
          snake.getHead() = exit+tmp;
          snake.setDirection(tmp);
      }while(map.in(exit+tmp));

    }
    return true;
}
bool Gate::snakePassing(Snake& snake){
    for(auto it = snake.getBody().begin(); it!=snake.getBody().end(); it++){
        if(enteredSpace == *it) return true;
    }   
    return false;
}

void Gate::setStatus(Map& map, Snake& snake){

    if((!active)&& //gate가 invisible한 상태 일 때,
    (duration_cast<milliseconds>(steady_clock::now()-tp).count() > hiddencycle)&&
    snake.getLength()>4    
    ){
        active = true; 
        tp = steady_clock::now(); 
        setLoc(map);    
        return;
    } 
    snakeEntered(map, snake);
    passing = snakePassing(snake);
    if(passing) return;

    if((active && // gate이 visible한 상태일 때
    (duration_cast<milliseconds>(steady_clock::now()-tp).count() > lifecycle))){
        active = false; 
        tp = steady_clock::now();
        return;
    }
}

void Gate::setLoc(Map& map){
    // 게이트가 겹치지 않도록, loc2와 loc1이 같으면 계속 randomLOC 실행

    loc1 = randomLOC(map);
    do{
        loc2 = randomLOC(map);
        // std::cout << (loc1== loc2 )<< std::endl;
    }while(loc1 == loc2);
    return;
}

// private function
LOC Gate::randomLOC(Map& map){
    int tmp = rand()%5;
    int x, y;
    LOC loc;
    switch(tmp){
        case 0: // 내부 벽
            loc= map.walls[rand()%map.w_size]; break;
        case 1: // 왼쪽 테두리
            y = rand()%(map.size_y-1);
            loc= {(y)? y: y+1, 0};
            break;
        case 2: // 위쪽 테두리
            x = rand()%(map.size_x-1);
            loc= {0 ,(x) ? x: x+1};
            break;
        case 3: // 오른쪽 테두리
            y = rand()%(map.size_y-1);
            loc= {(y)? y: y+1, map.size_x-1};
            break;
        case 4: // 아래 테두리
            x = rand()%(map.size_x-1);
            loc= {map.size_y-1, (x) ? x: x+1};
            break;
        default: break;
    }
    return loc;
}