#include<iostream>
#include<vector>
#include<thread>
// #include<mutex>
#include"LOC.h"
#include"map.h"
#ifndef __SNAKE_H__
#define __SNAKE_H__

// std::mutex bodyMutex;

class Snake{
private:
    LOC head; 
    std::vector<LOC> body;
    char direct;
    char opposite;
    LOC inc;
    LOC prev; // grow할 때 쓰는 변수
    int length;
    int n_gate, n_pItem, n_gItem;

    const int HEAD = 3;
    const int BODY = 4;

public:
    //consturctor
    Snake(LOC& head, int length = 3);

    // initializer
    void initialize(LOC& head, int length);
    // move functions
    void control(char key);
    void move();

    // event functions: get Item
    void grow(LOC& item_loc);
    void shrink(LOC& item_loc);

    // set variables;
    void setHead(const LOC& loc){head=loc;}
    void setDirection(const char direct, const char ops, const LOC& loc);
    void setDirection(const LOC& loc);
    void setN_gate(int init = 1){ n_gate = (init) ? n_gate+1 : init; }
    void setN_gItem(){ n_gItem = 0; }
    void setN_pItem(){ n_pItem = 0; }

    // get variables;
    int getLength(){return length;}
    const int getHeadColor(){return HEAD;}
    const int getBodyColor(){return BODY;}
    char getDirect(){return direct;}
    LOC& getHead(){return head;}
    std::vector<LOC>& getBody(){return body;}
    int getN_gate(){return n_gate;}
    int getN_gItem(){return n_gItem;}
    int getN_pItem(){return n_pItem;}

    // check fail condition
private:
    bool isDumpedBody();
    bool isDumpedWall(Map& map, LOC gate_loc1, LOC gate_loc2, bool gate_active);
    bool pressedOps(char key);
    bool headIn(LOC* blocks, int size);

public:
    bool isFailed(Map& map, LOC gate_loc1, LOC gate_loc2, bool gate_active, char key);
};


#endif