#pragma once 
#include <ncurses.h>
#include <iostream>
#include "Board.hpp"
#include "Drawable.hpp"
#include "Apple.hpp"
#include "Empty.hpp"
#include "Snake.hpp"

class Snakegame
{
private:
    Board board;
    Apple *apple = nullptr;
    bool game_over;
    bool same_input;
    Snake snake;
    SnakePiece next = SnakePiece(1, 1);

public:
    Snakegame(int height, int width)
    {
        board = Board(height, width);
        initialize();
    };

    void processInput()
    {
        chtype input = board.getInput();
        // process input
        Direction direct = none;
        same_input = false;

        switch (input)
        {
        case KEY_UP:
        case 'w':
            direct = up;
            break;

        case KEY_DOWN:
        case 's':
            direct = down;
            break;

        case KEY_RIGHT:
        case 'd':
            direct = right;
            break;

        case KEY_LEFT:
        case 'a':
            direct = left;
            break;

        case 'p':
            board.setTimeout(-1);
            while(board.getInput()!='p');
            board.setTimeout(500);

        default:
            break;
        }
        if(snake.getCurrDirection()==direct)
        {
            same_input = true;
        }
        else if(direct)
        {
            game_over=snake.setDirection(direct);
        }        
    }

    void updateState()
    {
        if(same_input) return;
        handleNextPiece(); 
        if(apple==nullptr) createApple(); 
    }

    void redraw()
    {   
        board.refresh();
    }

    bool isOver()
    {
        return game_over;
    }


    ~Snakegame()
    {
        delete apple;
    };

private:
    void initialize()
    {
        board.initialize();
        game_over = false;
        same_input = false;
        srand(time(NULL)); 
        // init snake
        snake.setDirection(down);
        board.add(next);
        snake.addPiece(next);
        
        handleNextPiece();
        handleNextPiece();
        handleNextPiece();

        
        if(apple==nullptr) createApple(); 
    }

    void handleNextPiece()
    {
        next = snake.nextHead();
    

        if(apple!=nullptr)
        {
            switch(board.getCharAt(next))
            {
                case 'A':
                    destroyApple();
                    break;
                case ' ':
                    board.add(Empty(snake.tail()));
                    snake.popPiece();
                    break;
                default: // collision
                    game_over=true;
                    break;
            }
        }
        board.add(next);
        snake.addPiece(next);
    }

    void createApple()
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        apple = new Apple(y, x);
        board.add(*apple);
    }

    void destroyApple()
    {
        delete apple;
        apple = nullptr;
    }
    
};

