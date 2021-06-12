#include <iostream>

#ifndef __LOC_H__   
#define __LOC_H__

struct LOC{
    int y = 0;
    int x = 0;

    int operator[](int idx){
        return (idx) ? y : x;
    }
    
    bool operator==(const LOC& ops) const{
        if((y==ops.y) && (x==ops.x)) return true;
        else return false;
    }

    bool operator!=(const LOC& ops) const{
        return !(*this==ops);
    }
    
    LOC& operator= (const LOC& loc){
        y = loc.y; x = loc.x;
    }

    LOC operator+ (const LOC& loc){
        return LOC({y+loc.y, x+loc.x});
    }

    LOC& operator+= (const LOC& loc){
        *this = *this+loc;
        return *this;
    }
    // friend std::ostream& operator<<(std::ostream& os, const LOC& loc);
};

// std::ostream& operator<<(std::ostream& os, const LOC& loc){
//     os <<"{" << loc.y << ", " << loc.x << "}\n";
//     return os;
// }

#endif 