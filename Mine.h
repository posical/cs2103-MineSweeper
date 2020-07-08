/**
 * CS2103 Coding Exercise 1 Special Semester 1
 * File:   Mine.h
 * Author: Kenneth Pan (U090283H)
 * Email: u0900283@nus.edu.sg
 * 
 * There are SIX files for this project.
 * main.cpp, Mine.h, GameBox.cpp, GameBox.h, GameState.cpp, GameState.h
 */

#ifndef MINE_H
#define	MINE_H


#include "GameBox.h"
#include "GameState.h"

    void checkMsg(GameState*);
    void openClick(int, GameBox*);
    void markClick(int, GameBox*);
    void assignClick(int,int,int,char,GameBox*,int);
    void scanBoard(GameBox*,GameState*,int);
    void checkAdj(int,GameBox*,int,int);
    void checkLeft(int,GameBox*,int,int);
    void checkRight(int,GameBox*,int,int);
    void checkTop(int,GameBox*,int,int);
    void checkBtm(int,GameBox*,int,int);
    void checkBtmLeft(int,GameBox*,int,int);
    void checkBtmRight(int,GameBox*,int,int);
    void checkTopLeft(int,GameBox*,int,int);
    void checkTopRight(int,GameBox*,int,int);
    void printBoard(GameBox*,int,int);

#endif	/* MINE_H */

