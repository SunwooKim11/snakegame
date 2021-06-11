#include <iostream>
#include <vector>
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
    // std::vector<LOC>imwalls;
    int imw_size;
    const int IMWALL = 2;

    LOC* walls;
    // std::vector<LOC> walls;
    int w_size;
    const int WALL = 1;

public:
    //constructor
    Map(int size_x = 63, int size_y = 21, int n_imwalls = 6, int n_walls = 8): size_x(size_x), size_y(size_y){
        // imw_size = n_imwalls + 4;
        // w_size = n_walls + (2*size_x+2*size_y -8);
        imw_size = n_imwalls;
        w_size = n_walls;

        imwalls = new LOC[n_imwalls];
        walls = new LOC[n_walls];
    
        //set imwalls
        imwalls[0] = {0, 0};
        imwalls[1] = {size_y-1, 0};
        imwalls[2] = {size_y-1, size_x-1};
        imwalls[3] = {0, size_x-1};
        // 나머지
        imwalls[4] = {10, 20};
        imwalls[5] = {7, 44};
        
        // set walls
        int idx = 0;

        walls[0] = {10, 15};
        walls[1] = {10, 16};
        walls[2] = {10, 14};
        walls[3] = {11, 15};

        walls[4] = {5, 44};
        walls[5] = {4, 44};
        walls[6] = {5, 45};
        walls[7] = {23, 19};

        // for(int i=1; i<size_x-1; i++, idx++) walls[idx] = {0, i};
        // for(int i=1; i<size_y-1; i++, idx++) walls[idx] = {i, size_x-1};
        // for(int i=size_x-2; i>0; i--, idx++) walls[idx] = {size_y-1, i};
        // for(int i=i=size_y-2; i>0; i--, idx++ ) walls[idx] = {i, 0};


    }
    ~Map(){
        delete[] imwalls;
        delete[] walls;
    }

};


#endif