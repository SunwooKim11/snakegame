#pragma once
#include <ncurses.h>

// 뱀, 아이템의 표현을 나타냄
// 1) y, x 좌표
// 2) 색깔, 모양등 겉모습

class Drawable
{
    // apple, empty class한테 상속줄꺼라서 이렇게 했구나.
protected:
    int y, x;
    chtype icon;
public:
    Drawable(int y, int x, chtype ch)
    {
        this->y = y;
        this->x = x;
        this->icon = ch;
    };

    Drawable(const Drawable& ops){
        this->y = ops.y;
        this->x = ops.x;
        this->icon = ops.icon;
    }

    int getX(){
        return x;
    }

    int getY(){
        return y;
    }
    
    chtype getIcon(){
        return icon;
    }
    
    bool operator==(const Drawable& ops) const{
        if((y==ops.y) && (x==ops.x)) return true;
        else return false;
    }

    bool operator!=(const Drawable& ops) const{
        return !(*this==ops);
    }

};

