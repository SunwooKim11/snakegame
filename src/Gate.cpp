#include "Gate.h"
//constructor:
Gate::Gate(bool active, bool passing, int lifecycle, int hiddencycle)
:active(active), passing(passing), lifecycle(lifecycle), hiddencycle(hiddencycle){}

// initializer:
// init active and passing
void Gate::initialize(bool active, bool passing){
    this->active = active; this->passing = passing;
}

// handle status when snake enters the gate
bool Gate::snakeEntered(Map& map, Snake& snake){
    // when snake does not enter
    if(!(snake.getHead() == loc1 || snake.getHead() == loc2)){
        return false;
    }

    // when snake enters
    passing = true;
    enteredSpace = snake.getBody()[0]; // the location of head just before snake enters the gate.
    snake.setN_gate(); // increase snake.n_gate by one.
    //set entrace, exit
    if(snake.getHead() == loc1){
        entrace = loc1; exit = loc2; 
    } else{
        entrace = loc2; exit = loc1;
    }

    if(exit.x == 0){ // exit on left outline
        snake.setHead({exit.y, exit.x+1});
        snake.setDirection('d', 'a', {0, 1});
    }
    else if(exit.y == 0){ // exit on up outline
        snake.setHead({exit.y+1, exit.x});
        snake.setDirection('s', 'w', {1, 0});
    }
    else if(exit.x == map.size_x-1){ // exit on right outline
        snake.setHead({exit.y, exit.x-1});
        snake.setDirection('a', 'd', {0, -1});
    }
    else if(exit.y == map.size_y-1){ // exit on down outline
        snake.setHead({exit.y-1, exit.x});
        snake.setDirection('w', 's', {-1, 0});
    }
    else{ // exit on inner walls
      int idx1, idx2 = -1;
      LOC tmp;
    // get snake's entry direction
        switch(snake.getDirect()){
          case 'a': idx1 = 0; break;
          case 'w': idx1 = 1; break;
          case 'd': idx1 = 2; break;
          case 's': idx1 = 3; break;
      }  

    // decide where to exit in priority order until the entry point is not a wall
      do{
          tmp = EXIT_DIRECT[idx1][++idx2];
          snake.getHead() = exit+tmp;
          snake.setDirection(tmp);
      }while(map.in(exit+tmp));

    }
    return true;
}

// check if snake is going through the gate.
bool Gate::snakePassing(Snake& snake){
    for(auto it = snake.getBody().begin(); it!=snake.getBody().end(); it++){
        if(enteredSpace == *it) return true;
    }   
    return false;
}
// set values(active, tp, loc) depending on event.
void Gate::setStatus(Map& map, Snake& snake){

    if((!active)&& // when gate is invisible and time > hiddencycle and snake length > 4
    (duration_cast<milliseconds>(steady_clock::now()-tp).count() > hiddencycle)&&
    snake.getLength()>4    
    ){
        // make item visible, update tp and loc.
        active = true; 
        tp = steady_clock::now(); 
        setLoc(map);    
        return;
    } 
    snakeEntered(map, snake);
    passing = snakePassing(snake);
    if(passing) return;

    if((active && // when gate is visible and time > lifecycle
    (duration_cast<milliseconds>(steady_clock::now()-tp).count() > lifecycle))){
        // make item invisible, update tp.
        active = false; 
        tp = steady_clock::now();
        return;
    }
}

// setter:
// for not gates overlapping, if loc1 equals to loc1 repeat randomLOC()
void Gate::setLoc(Map& map){
    loc1 = randomLOC(map);
    do{
        loc2 = randomLOC(map);
    }while(loc1 == loc2);
    return;
}

// private function
// generate randoom loc
LOC Gate::randomLOC(Map& map){
    int tmp = rand()%5;
    int x, y;
    LOC loc;
    switch(tmp){
        case 0: // inner walls
            loc= map.walls[rand()%map.w_size]; break;
        case 1: // left outline
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