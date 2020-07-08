/** 
 * CS2103 Coding Exercise 1 Special Semester 1
 * File:   GameState.h
 * Author: Kenneth Pan (U090283H)
 * Email: u0900283@nus.edu.sg
 * 
 * There are SIX files for this project.
 * main.cpp, Mine.h, GameBox.cpp, GameBox.h, GameState.cpp, GameState.h
 */

#ifndef GAMESTATE_H
#define	GAMESTATE_H

#define ERR_END "IN PROGRESS"
#define LOSE_GAME "LOST"
#define WIN_GAME "WON"
#include "GameBox.h"
#include <string>

using namespace std;

class GameState: public GameBox {
    protected:
        int _status;
        
        void printMsg(int);
        void printWin();
        void printLose();
        void printInProgress();
        
    public:
        void checkValue(int);
        bool checkState();
        void closeState();
        GameState();
        virtual ~GameState();
        
        
};

#endif	/* GAMESTATE_H */

