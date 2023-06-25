#pragma once 
#include <ncurses.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "Gameboard.hpp"
#include "Missionboard.hpp"
#include "Scoreboard.hpp"
#include "Drawable.hpp"
#include "Apple.hpp"
#include "Poison.hpp"
#include "Empty.hpp"
#include "Snake.hpp"


#define SUB_DIMS 10
#define SUB_ROWS SUB_DIMS
#define SUB_COLS SUB_DIMS * 4
#define STAGE 4


class Snakegame
{
public:
    const int NUM_STAGE = 4;
private:
    Gameboard game_board;
    Scoreboard score_board;
    Missionboard mission_board;
    
    Apple *apple = nullptr;
    Poison *poison = nullptr;
    bool stage_over;
    bool game_over;
    Snake snake;
    SnakePiece next;

    int stage;

public:
    Snakegame()
    {
        game_board = Gameboard();
        score_board = Scoreboard(SUB_ROWS, SUB_COLS, 0, game_board.getEndX());
        mission_board = Missionboard(SUB_ROWS, SUB_COLS, game_board.getEndY()-SUB_ROWS, game_board.getEndX());
        srand(time(NULL)); 
    };

    void processInput()
    {
        chtype input = game_board.getInput();
        // process input
        Direction direct = none;

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
            game_board.setTimeout(-1);
            while(game_board.getInput()!='p');
            game_board.setTimeout(500);

        default:
            break;
        }
        if(direct)
        {
            game_over=snake.setDirection(direct);
            
        }        
    }

    void updateState()
    {
        handleNextPiece();
        updateMissionBoard();
        stage_over = mission_board.updateMission();
        if(apple==nullptr) createApple(); 
        if(poison==nullptr) createPoison(); 
        
        
    }

    void redraw()
    {   
        game_board.refresh();
        score_board.redraw();
        mission_board.redraw();
    }

    bool isStageOver()
    {
        return stage_over;
    }
    
    bool isGameOver(){
        return game_over;
    }

    void setStage(int stage)
    {   
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        this->stage = stage;
        snake.initialize();
        next = snake.initHead(2, 2);

        if(apple!=nullptr) {
            delete apple;
            apple = nullptr;
        }
        if(poison!=nullptr){
            delete poison;
            poison = nullptr;
        }
        
        initialize();
    };

    int getStage()
    {
        return STAGE;
    };

    ~Snakegame()
    {
        
        // delete &game_board;
        // delete &game_board;
        // delete &score_board;

    };

private:
    
    void initialize()
    {
        game_board.initialize(stage);
        stage_over = false;
        game_over = false;


        // init snake
        snake.setDirection(down);
        game_board.add(next);
        snake.addPiece(next);
        
        next = snake.nextHead();
        game_board.add(next);
        snake.addPiece(next);

        next = snake.nextHead();
        game_board.add(next);
        snake.addPiece(next);
        
        if(apple==nullptr) createApple(); 
        if(poison==nullptr) createPoison(); 

        score_board.initialize(stage);
        mission_board.initialize(stage);
    }

    void handleNextPiece()
    {
        next = snake.nextHead();
    

        switch(game_board.getCharAt(next))
        {
            case 'A':
                eatApple();
                break;
            case 'P':
                eatPoison();
                break;
            case ' ':
                game_board.add(Empty(snake.tail()));
                snake.popPiece();
                break;
            default: // collision
                game_over=true;
                stage_over = true;
                break;
        }
        
        game_board.add(next);
        snake.addPiece(next);
    }

    void createApple()
    {
        int y, x;
        game_board.getEmptyCoordinates(y, x);
        apple = new Apple(y, x);
        game_board.add(*apple);
    }

    void createPoison()
    {
        int y, x;
        game_board.getEmptyCoordinates(y, x);
        poison = new Poison(y, x);
        game_board.add(*poison);
    }

    void eatApple()
    {
        delete apple;
        apple = nullptr;

        snake.updateLength(true);
        score_board.updateLen(snake.getLength());
        score_board.updatePlus();

    }

    void eatPoison()
    {
        delete poison;
        poison = nullptr;

        game_board.add(Empty(snake.tail()));
        snake.popPiece();
        game_board.add(Empty(snake.tail()));
        snake.popPiece();

        snake.updateLength(false);
        score_board.updateLen(snake.getLength());

        score_board.updateMinus();
    }

    void updateMissionBoard()
    {
        mission_board.updatePlus(score_board.getPlus());
        mission_board.updateMinus(score_board.getMinus());
        mission_board.updateLen(score_board.getLen());
    }
    
};

