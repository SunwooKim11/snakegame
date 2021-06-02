#include <iostream>

#ifndef __LOC_H__
#define __LOC_H__

struct LOC{
    int y = 0;
    int x = 0;

    // LOC(int y, int x): y(y), x(x) {};
    int operator[](int idx){
        return (idx) ? y : x;
    }
    
    // void operator=(LOC& diff){
    //     y = diff.y;
    //     x = diff.x;
    // }

    bool operator==(LOC& ops){
        if((y==ops.y) && (x==ops.x)) return true;
        else return false;
    }

    bool operator!=(LOC& ops){
        return !(*this==ops);
    }
};

#endif 