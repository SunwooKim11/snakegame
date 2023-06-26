#pragma once

#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include "Board.hpp"

#define GAME_DIMS 20
#define GAME_ROWS GAME_DIMS
#define GAME_COLS GAME_DIMS * 2.5

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;
using std::istringstream;

class Gameboard : public Board
{

public: 
    Gameboard(int height=GAME_ROWS, int width=GAME_COLS, int startY = 0, int startX = 0) : Board(height, width, startY, startX)
    {

    };
  
    void initialize(int stage)
    {
        clear(stage);
        refresh();
        loadStage(stage);
        refresh();
    }

    void clear(int stage)
    {
        Board::clear();

        // for(int i=0; i<)
    }

    
    // ref C++ csv 파일 읽기
    //https://www.delftstack.com/ko/howto/cpp/read-csv-file-in-cpp/
    void loadStage(int stage)
    {
        int y, x;   
        string filename("normal.csv");
        string file_contents;
        char delimiter = ',';

        file_contents = readFileIntoString(filename);

        istringstream sstream(file_contents);
        std::vector<string> items;
        string record;

        while (std::getline(sstream, record)) {
            istringstream line(record);
            while (std::getline(line, record, delimiter)) {
                record.erase(std::remove_if(record.begin(), record.end(), isspace), record.end());
                items.push_back(record);
            }
            y = std::stoi(items[0]);
            x = std::stoi(items[1]);
            // addAt(y, x, 'O');
            mvwprintw(board_win, y, x, "0");
            items.clear();
        }

    }

    // y, x를 ref로 받아. empty 한 좌표를 y, x에 할당시킴. 
    void getEmptyCoordinates(int &y, int &x){
        while ((mvwinch(board_win, y = rand() % height, x = rand() % width)) != ' ');       
    }

    chtype getInput(){
        return wgetch(board_win);
    }


    chtype getCharAt(Drawable obj)
    {
        return mvwinch(board_win, obj.getY(), obj.getX());
    }

    
private: 
    string readFileIntoString(const string& path) 
    {    
        auto ss = ostringstream{};
        std::ifstream ifs;
        ifs.open ("normal.csv", std::ifstream::in); 

        // if (ifs.good()) {
        //     cerr << "Could not open the file - '"
        //          << path << "'" << endl;
        //     exit(EXIT_FAILURE);
        // }
        ss << ifs.rdbuf();
        return ss.str();
    }

};


