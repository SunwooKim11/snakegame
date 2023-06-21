#include<thread>
#include"Map.h"
#ifndef __SNAKE_H__
#define __SNAKE_H__


class Snake{
private:
    LOC head; 
    std::vector<LOC> body; 
    char direct;    // snake's direction
    char opposite;  // the opposite of snake's direction
    LOC inc;    // direction of shifting head at a certain time -> used in move func 
    LOC prev;   // location of snake's tail which was one tick before from current  -> used in grow func
    int length;
    // count variables: head is equal to gate, poision item, growth item.
    int n_gate, n_pItem, n_gItem; 

    const int HEAD = 3;
    const int BODY = 4;

public:
    //consturctor:
    Snake(LOC& head, int length = 3);

    // initializer:

    // init all memeber variables
    void initialize(LOC& head, int length);

    // move functions:

    // control direct, opposite, inc depending on key
    void control(char key);

    // put head in the front part of body, 
    // and move snake's head by adding inc to head,
    // and remove the last part of body(tail).
    void move();

    // event functions: 

    // by setting head loc growth item loc and
    // appending prev to tail,
    // this make snake looks like growing up
    void grow(LOC& item_loc);

    // by removing tail(the end part of body),
    // this make snake looks shrunk
    void shrink(LOC& item_loc);

    // set variables:
    void setHead(const LOC& loc){head=loc;}
    void setDirection(const char direct, const char ops, const LOC& loc);
    void setDirection(const LOC& loc); //set direct, opposite by inc(loc)
    void setN_gate(int init = 1){ n_gate = (init) ? n_gate+1 : init; }
    void setN_gItem(){ n_gItem = 0; }
    void setN_pItem(){ n_pItem = 0; }

    // get variables:
    int getLength(){return length;}
    const int getHeadColor(){return HEAD;}
    const int getBodyColor(){return BODY;}
    char getDirect(){return direct;}
    LOC& getHead(){return head;}
    std::vector<LOC>& getBody(){return body;}
    int getN_gate(){return n_gate;}
    int getN_gItem(){return n_gItem;}
    int getN_pItem(){return n_pItem;}

    // check fail condition:
private:

    // check if snake's head bumped into its body
    bool isDumpedBody();   

    // check if snake's head bumped into all walls
    bool isDumpedWall(Map& map, LOC gate_loc1, LOC gate_loc2, bool gate_active); 
    
    // check if user pressed the key of which direction is snake's opposite
    bool pressedOps(char key);
    
    // check if snake's head bumped into the inner walls(not outline walls)
    bool headIn(LOC* blocks, int size);

public:
    // check all conditions above and return whether it is failed or not.
    bool isFailed(Map& map, LOC gate_loc1, LOC gate_loc2, bool gate_active, char key);
};


#endif