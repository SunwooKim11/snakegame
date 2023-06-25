#include <ncurses.h>
#include "src/Board.hpp"
#include "src/Snakegame.hpp"

// #define BOARD_DIM 40
// #define BOARD_ROWS BOARD_DIM
// #define BOARD_COLS BOARD_DIM * 2.5

int main(int argc, char *argv){
    initscr();
    refresh();
    noecho();
    curs_set(0);

    Snakegame game;
    

    for (int i=0; i<game.getStage(); i++)
    {   
        game.setStage(i);
        while (!game.isStageOver())
        {
            // 1. get input from user
            game.processInput();

            // 2. update game status ex) snake, item / score board
            game.updateState();

            // 3. update windows
            game.redraw();

            // 4. go to 1 unless gameover
        }
        
        if(game.isGameOver()){
            break;
        }
    }
    

    getch();
    endwin();

    return 0;
    
}