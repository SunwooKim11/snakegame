#pragma once
#include <ncurses.h>

class Scoreboard
{
private:
    WINDOW *score_win;
public:
    Scoreboard()
    {

    };

    Scoreboard(int height, int width, int y, int x)
    {
        score_win = newwin(1, width, y, x);
    }

    void initializse()
    {
        clear();
        mvwprintw(score_win, 0, 0, "Score: ");


    }

    void updateScore(int score)
    {

    }

    void clear()
    {
        wclear(score_win);
    }

    void refresh()
    {

    }

};
