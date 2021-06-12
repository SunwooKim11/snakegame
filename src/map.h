#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "LOC.h"

#ifndef __MAP_H__
#define __MAP_H__

class Map{
public:
    
    const std::string dir = "/home/sunwoo/kmu/kmu-lessons-2021-01/CPP/snakegame/data/mapdata";
    std::string path;
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
    Map(int stage = 0, int size_x = 32, int size_y = 21): size_x(size_x), size_y(size_y){
        initialize(stage);
        // imw_size = n_imwalls;
        // w_size = n_walls;

        // imwalls = new LOC[n_imwalls];
        // walls = new LOC[n_walls];
    
        // //set imwalls
        // imwalls[0] = {0, 0}; imwalls[1] = {size_y-1, 0}; imwalls[2] = {size_y-1, size_x-1}; imwalls[3] = {0, size_x-1};
        // // 나머지
        // imwalls[4] = {3, 20};
        // imwalls[5] = {7, 14};
        
        // // set walls
        // walls[0] = {10, 7}; walls[1] = {10, 8}; walls[2] = {10, 9}; walls[3] = {11, 8};
        // walls[4] = {5, 24}; walls[5] = {4, 24}; walls[6] = {5, 25}; 

        // walls[7] = {15, 19}; walls[8] = {2, 11}; walls[9] = {9, 2}; walls[10] = {9, 23};
        // walls[11] = {18, 13}; walls[12] = {3, 28}; walls[13] = {5, 9};
    }
    void initialize(int stage){
        path = dir + std::to_string(stage) +".txt";
        std::ifstream fin(path);
        if(!fin){
            return;
        }
        std::cout <<"fin success";
        if(stage>0){delete[] walls; delete[] imwalls;}
        
        int delim = 0;
        std::string num;
        //imw_size;
        std::getline(fin, num);
        imw_size = std::stoi(num);
        //w_size;
        std::getline(fin, num);
        w_size = std::stoi(num);
        imwalls = new LOC[imw_size];
        walls = new LOC[w_size];
        //set imwalls
        imwalls[0] = {0, 0}; imwalls[1] = {size_y-1, 0}; imwalls[2] = {size_y-1, size_x-1}; imwalls[3] = {0, size_x-1};
        for(int i=4; i<imw_size; i++){
            std::getline(fin, num);
            delim = num.find(",");
            imwalls[i] = LOC{std::stoi(num.substr(0, delim)), std::stoi(num.substr(delim+1))};
        }
        //set walls
       for(int i=0; i<w_size; i++){
            std::getline(fin, num);
            delim = num.find(",");
            walls[i] = LOC{std::stoi(num.substr(0, delim)), std::stoi(num.substr(delim+1))};
        }
        fin.close();

    }

    bool in(const LOC& loc){
        for(int i=0; i<imw_size; i++){
            if(*(imwalls+i) == loc ) return true;
        }
        for(int i=0; i<w_size; i++){
            if(*(walls+i) == loc) return true;
        }
        return false;
    }

    ~Map(){
        delete[] imwalls;
        delete[] walls;
    }

};


#endif