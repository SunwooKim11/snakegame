#pragma once
#include "Drawable.hpp"

class Empty: public Drawable
{

      
public:
    Empty(int y, int x) : Drawable(y, x, ' '){};
    Empty(const Drawable& ops) : Drawable(ops)
    {
        this->icon = ' ';
    };
};