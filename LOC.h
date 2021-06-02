#include <iostream>

#ifndef __LOC_H__
#define __LOC_H__

struct LOC{
    int y = 0;
    int x = 0;

    int operator[](int idx){
        return (idx) ? y : x;
    }
};

#endif 