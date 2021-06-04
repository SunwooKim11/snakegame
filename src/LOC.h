#include <iostream>

#ifndef __LOC_H__
#define __LOC_H__

struct LOC{
    int y = 0;
    int x = 0;

    int operator[](int idx){
        return (idx) ? y : x;
    }
    
    bool operator==(const LOC& ops){
        if((y==ops.y) && (x==ops.x)) return true;
        else return false;
    }

    bool operator!=(const LOC& ops){
        return !(*this==ops);
    }
};

#endif 