#pragma once
#include <ncurses.h>
#include "Drawable.hpp"
#include <queue>

#define LEN 3

enum Direction{
    up = -1,
    down = 1,
    left = -2,
    right = 2,
    none = 0
};

class SnakePiece : public Drawable
{
public:
    SnakePiece() : Drawable(1, 1, '#'){};

    SnakePiece(int y, int x) : Drawable(y, x, '#'){};

};

class Snake
{
private:
    std::queue<SnakePiece> prev_pieces;
    Direction curr_direction;
    Direction prev_direction;
    int length;

public:
    Snake()
    {
        prev_direction = left;
        curr_direction = right;
    }

    void initialize()
    {
        length = LEN;
        while(prev_pieces.size() > 0)
        {
            this->popPiece();
        }
        // return this->initHead();
    }

    void updateLength(bool plus)
    {
        if(plus) length++;
        else length--;
    }
    
    int getLength()
    {
        return length;
    }

    void addPiece(SnakePiece piece)
    {
        prev_pieces.push(piece);
    }

    void popPiece()
    {
        prev_pieces.pop();
    }

    SnakePiece tail()
    {
        return prev_pieces.front();
    }

    SnakePiece head()
    {
        return prev_pieces.back();
    }


    Direction getPrevDirection()
    {
        return prev_direction;
    }

    Direction getCurrDirection()
    {
        return curr_direction;
    }

    bool setDirection(Direction d)
    {   
        // gameover
        if(!(curr_direction+d)) return true;
        prev_direction = curr_direction;
        curr_direction = d;
        return false;
    }
    SnakePiece initHead(int y = 1, int x = 1)
    {
        return SnakePiece(y, x);
    }
    SnakePiece nextHead()
    {
        int y = this->head().getY();
        int x = this->head().getX();

        switch(curr_direction)
        {
            case up:
                y--;
                break;

            case down:
                y++;
                break;
            case left:
                x--;
                break;

            case right:
                x++;
                break;
        }

        return SnakePiece(y, x);
    }
    

};