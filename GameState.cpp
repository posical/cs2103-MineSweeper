/** 
 * CS2103 Coding Exercise 1 Special Semester 1
 * File:   GameState.cpp
 * Author: Kenneth Pan (U090283H)
 * Email: u0900283@nus.edu.sg
 * 
 * There are SIX files for this project.
 * main.cpp, Mine.h, GameBox.cpp, GameBox.h, GameState.cpp, GameState.h 
 */

#include "GameBox.h"
#include "GameState.h"
#include <iostream>

using namespace std;

GameState::GameState() 
{
    _isOpened = 1;
    _status = 2;
}

GameState::~GameState() 
{

}

bool GameState::checkState()
{
    return getStatus();
}

void GameState::printMsg(int check)
{
    switch(check)
    {
        case 0:
            printWin();
            break;
            
        case 1:
            printLose();
            break;
        
        case 2:
            printInProgress();
            break;
        
        default:
            break;
    }
}

void GameState::printWin()
{
    cout << WIN_GAME << endl;
}

void GameState::printLose()
{
    cout << LOSE_GAME << endl;
}

void GameState::printInProgress()
{
    cout << ERR_END << endl;
}

void GameState::checkValue(int msg)
{
    printMsg(msg);
}

void GameState::closeState()
{
    _isOpened = 0;
}
