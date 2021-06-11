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
public:
    LOC head;
    std::vector<LOC> body;
    char direct;
    char opposite;
    LOC inc;
    int length;
    const int HEAD = 3;
    const int BODY = 4;
    LOC prev;
public:
    //consturctor
    Snake(LOC& head, int length = 3);

    // move functions
    void setDirection(char key);
    void move();

    // event functions: get Item
    void grow(LOC& item_loc);
    void shrink(LOC& item_loc);

    // check fail condition
private:
    bool isDumpedBody();
    bool isDumpedWall(Map& map);
    bool pressedOps(char key);
    bool headIn(LOC* blocks, int size);

public:
    bool isFailed(Map& map, char key);
};


#endif