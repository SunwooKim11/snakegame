#include <vector>
#include <fstream>
#include <string>
#include "LOC.h"

#ifndef __MAP_H__
#define __MAP_H__

class Map{
public:
    
    const std::string dir = "../data/mapdata";
    std::string path;
    // size
    int size_x;
    int size_y;
    const int BACK_GROUND = 8;
    
    // immune wall
    LOC *imwalls;
    int imw_size;
    const int IMWALL = 2;

    LOC* walls;
    int w_size;
    const int WALL = 1;

public:
    //constructor
    Map(int stage = 0, int size_x = 32, int size_y = 21): size_x(size_x), size_y(size_y){
        initialize(stage);
    }
    // init member variables(expect size and constant) with data from files(txt)
    void initialize(int stage){
        path = dir + std::to_string(stage) +".txt";
        std::ifstream fin(path);
        if(!fin){
            return;
        }
        // std::cout <<"fin success";
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

    // check loc equals to a loc, which is wall or imwall
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