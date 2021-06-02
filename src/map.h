#include <iostream>
#include "LOC.h"

#ifndef __MAP_H__
#define __MAP_H__

class Map{
public:
    // size
    int size_x;
    int size_y;
    const int BACK_GROUND = 8;

    // immune wall
    LOC *imwalls;
    const int IMWALL = 2;

    // wall
    LOC *walls;
    const int WALL = 1;

public:
    //constructor
    Map(int size_x = 63, int size_y = 21, int n_imwalls = 4, int n_walls =8): size_x(size_x), size_y(size_y){
        imwalls = new LOC[n_imwalls];
        walls = new LOC[n_walls];
    }

};


#endif