#pragma once
#include "Drawable.hpp"

class Apple: public Drawable
{

public:
    Apple(int y, int x): Drawable(y, x, 'A'){};
};