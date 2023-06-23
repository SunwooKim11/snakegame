#pragma once
#include "Drawable.hpp"

class Wall: public Drawable
{

public:
    Wall(int y, int x): Drawable(y, x, 'W'){};
};