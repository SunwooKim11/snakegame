#pragma once
#include "Drawable.hpp"

class Poison: public Drawable
{

public:
    Poison(int y, int x): Drawable(y, x, 'P'){};
};