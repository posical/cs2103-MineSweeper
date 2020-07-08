/** 
 * CS2103 Coding Exercise 1 Special Semester 1
 * File:   main.cpp
 * Author: Kenneth Pan (U090283H)
 * Email: u0900283@nus.edu.sg
 * 
 * There are SIX files for this project.
 * main.cpp, Mine.h, GameBox.cpp, GameBox.h, GameState.cpp, GameState.h
 */

/** in.txt has to be in the same folder as the main.cpp for it to work*/

/** Identifier Naming Convention
 * 
 *      Class Name
 * Pascal Case (aka Upper Camel Case)
 * The first letter of each word should be capitalized
 * All words are concatenated without space or underscore
 * Acronym should be avoided, unless it's very popular (eg. XML)
 * Acronym is treated as one word
 * Digits and underscore should be avoided
 * eg. EntityManager, SoundGenerator, UrlReader
 *
 *      Function Name 
 * Camel Case
 * The first letter of the first word kept lowercase, while the first letter of the subsequent words are capitalized
 * All words are concatenated without space or underscore
 * Acronym should be avoided, unless it's very popular (eg. XML)
 * Acronym is treated as one word
 * Digits and underscore should be avoided
 * Try to name function that queries a boolean value with isXXXX() (eg. isRunning() )
 * eg. run(), onMouseEvent(), getXmlHttpRequest()
 *
 *      Variables
 * Camel Case
 * The first letter of the first word kept lowercase, while the first letter of the subsequent words are capitalized
 * All words are concatenated without space or underscore
 * Private/protected class field should be preceded with underscore
 * The identifier should be mnemonic
 * eg. _vertexBuffer, _context3D
 * 
 *      Constants
 * All uppercase letters
 * Space should be replaced by underscore
 * eg. DEFAULT_FRAME_RATE, SOUND_DATA_BUFFER_SIZE
 *
 */

#include "Mine.h"
#include "GameState.h"
#include "GameBox.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() 
{
    /*===============Declarations of variables=============*/
    ifstream readFile("in.txt");
    int _xSize,_ySize,_errFlag=0,_keyFlag=1, _maxLength=0;
    char _click;
    int _gridRow,_gridColumn;
    char _tempChar;
    GameState *_state;
    GameBox *_tempHolder;
    GameBox *_boxArray;
    
    readFile >> _xSize;
    readFile >> _ySize;
   
    _maxLength = _ySize*_xSize;
    _boxArray = new GameBox[_maxLength];
    
    
         for(int j=_maxLength-1;j>=0;j--)
        {
             readFile >> _tempChar;
             _tempHolder = 0;
             _tempHolder = new GameBox();
             _tempHolder->setupBox(_tempChar);
             _boxArray[j]=*_tempHolder;
        }
        
    readFile.close();
    
    _state = new GameState();
    /*===========End of Declarations of variables======*/
    
    /*============Start of game cycle==================*/
    while(_state->checkState() == 1)
    {
        goto print;
        print:
            scanBoard(_boxArray,_state,_maxLength);
            printBoard(_boxArray,_xSize,_maxLength);
  
            _errFlag = 0;
            goto play;
        
        play:
            do{   
                cin >> _click;
                
                switch(_click)
                {
                    case 'q':
                    case 'Q':
                    case 'r':
                    case 'R':
                    case 'l':
                    case 'L':
                        _keyFlag = 0;
                        break;
                    
                    default:
                        goto print;
                        break;
                }
                
            }while(_keyFlag==1);
            
            if((_click == 'Q' || _click == 'q') && _errFlag == 0)
            {
                checkMsg(_state);
                goto print;
            }
            else if(_click =='Q' || _click == 'q')
            {
                goto print;
            }
            
            else 
            {
                goto next;
            }
        
        next:
            _errFlag = 1;
            cin >> _gridColumn >> _gridRow;
           
                assignClick(_xSize,_gridColumn,_gridRow,_click,_boxArray,_maxLength);
               _keyFlag = 1;
                goto play;
    }
    /*============End of game cycle==================*/                         
 
    return 0;
}

void checkMsg(GameState *v)
{
   v->checkValue(2);
}

void assignClick(int _xSize, int x, int y, char c, GameBox *gameBoard,int _maxLength)
{
    int index;
    if(x == 0 || y == 0)
    {
    }
    else
    {
        index = (_xSize-x)+(_xSize*(y-1));
            
        switch(c)
        {
            case 'L':
                checkAdj(index,gameBoard,_xSize,_maxLength);
                break;
            case 'l':
                checkAdj(index,gameBoard,_xSize,_maxLength);
                break;
            case 'R':
                markClick(index,gameBoard);
                break;
            case 'r':
                markClick(index,gameBoard);
                break;
            default:
                break;
        }
    }
}

void markClick(int index, GameBox *gameBoard)
{   
    gameBoard[index].writeClosedBox();
}

void openClick(int index, GameBox *gameBoard)
{
    gameBoard[index].openBox();
}

void scanBoard(GameBox *gameBoard, GameState *updater, int _maxLength)
{
    int openMine=0;
    int closeMine=0;
    int maxMine=0;
    int decision=0;
    int openedNumbers=0;
    int totalNumbers=0;
    
    for(int a=0;a<_maxLength;a++)
    {
        if(gameBoard[a].readOpenBox()=='*')
        {
         closeMine++;   
        }
        if(gameBoard[a].readBox()> 47 && gameBoard[a].readBox()<57)
        {
            openedNumbers++;
        }
    }
    maxMine = closeMine;
    totalNumbers = _maxLength - maxMine;
    
    for(int z=0;z<_maxLength;z++)
    {
        if(gameBoard[z].readBox()=='*')
        {
            openMine++;
            closeMine--;
        }
    }
    
    if(openMine>0)
    {
        updater->closeState();
        for(int m=0;m<_maxLength;m++)
        {
            gameBoard[m].forceOpenBox();
        }
        decision = 1;
    }
    
    if(closeMine==maxMine && openedNumbers==totalNumbers)
    {
        updater->closeState();
        for(int m=0;m<_maxLength;m++)
        {
            gameBoard[m].forceOpenBox();
        }
        decision = 2;
    }
    
    switch(decision)
    {
            case 1:
                updater->checkValue(1);
                break;
            case 2:
                updater->checkValue(0);
                break;
            default:
                break;
    }           
}

void checkAdj(int index, GameBox *gameBoard, int _xSize, int _maxLength)
{
    if(gameBoard[index].readBox()=='/')
    {
    }
    else
    { 
        openClick(index,gameBoard);
        if(gameBoard[index].readOpenBox()=='0')
        {
            checkLeft(index,gameBoard,_xSize,_maxLength);
            checkRight(index,gameBoard,_xSize,_maxLength);
            checkTop(index,gameBoard,_xSize,_maxLength);
            checkBtm(index,gameBoard,_xSize,_maxLength);
            checkBtmLeft(index,gameBoard,_xSize,_maxLength);
            checkBtmRight(index,gameBoard,_xSize,_maxLength);
            checkTopLeft(index,gameBoard,_xSize,_maxLength);
            checkTopRight(index,gameBoard,_xSize,_maxLength);
        }
    }
    /*check adjacent box if current is 0
     recursive here*/
}

void checkTop(int index, GameBox *gameBoard, int _xSize, int _maxLength)
{
    int top;
    top = index + _xSize;
    
    if(top<_maxLength && gameBoard[top].readOpenBox()!='*' && gameBoard[index].readOpenBox()=='0')
    {
        gameBoard[top].openBox();
        checkTop(top,gameBoard,_xSize,_maxLength);
        checkLeft(top,gameBoard,_xSize,_maxLength);
        checkRight(top,gameBoard,_xSize,_maxLength);
        checkTopLeft(top,gameBoard,_xSize,_maxLength);
        checkTopRight(top,gameBoard,_xSize,_maxLength);
    }
}

void checkBtm(int index, GameBox *gameBoard, int _xSize, int _maxLength)
{
    int btm;
    btm = index - _xSize;
    
    if(btm>0 && gameBoard[btm].readOpenBox()!='*' && gameBoard[index].readOpenBox()=='0')
    {
        gameBoard[btm].openBox();
        checkBtm(btm,gameBoard,_xSize,_maxLength);
        checkLeft(btm,gameBoard,_xSize,_maxLength);
        checkRight(btm,gameBoard,_xSize,_maxLength);
        checkBtmLeft(btm,gameBoard,_xSize,_maxLength);
        checkBtmRight(btm,gameBoard,_xSize,_maxLength);
    }
}

void checkLeft(int index, GameBox *gameBoard, int _xSize, int _maxLength)
{
    int left;
    left = index + 1;

    if((!(left%_xSize==0)) && gameBoard[left].readOpenBox()!='*' && gameBoard[index].readOpenBox()=='0')
    {
        gameBoard[left].openBox();
        checkLeft(left,gameBoard,_xSize,_maxLength);
        checkTop(left,gameBoard,_xSize,_maxLength);
        checkBtm(left,gameBoard,_xSize,_maxLength);
        checkTopLeft(left,gameBoard,_xSize,_maxLength);
        checkBtmLeft(left,gameBoard,_xSize,_maxLength);
    }
}

void checkRight(int index, GameBox *gameBoard, int _xSize, int _maxLength)
{
    int right;
    right = index - 1;
    
    if((!(right%_xSize==0)) && gameBoard[right].readOpenBox()!='*' && gameBoard[index].readOpenBox()=='0')
    {
        gameBoard[right].openBox();
        checkRight(right,gameBoard,_xSize,_maxLength);
        checkTop(right,gameBoard,_xSize,_maxLength);
        checkBtm(right,gameBoard,_xSize,_maxLength);
        checkTopRight(right,gameBoard,_xSize,_maxLength);
        checkBtmRight(right,gameBoard,_xSize,_maxLength);
    }   
}

void checkBtmLeft(int index, GameBox *gameBoard, int _xSize, int _maxLength)
{
    int btmleft;
    btmleft = index - _xSize + 1;
    
    if((btmleft>0 && !(btmleft%_xSize==0)) && gameBoard[btmleft].readOpenBox()!='*' && gameBoard[index].readOpenBox()=='0')
    {
        gameBoard[btmleft].openBox();
        checkBtmLeft(btmleft,gameBoard,_xSize,_maxLength);
    }
}

void checkBtmRight(int index, GameBox *gameBoard, int _xSize, int _maxLength)
{
    int btmright;
    btmright = index - _xSize - 1;
    
    if((btmright>0 && !(btmright%_xSize==0)) && gameBoard[btmright].readOpenBox()!='*' && gameBoard[index].readOpenBox()=='0')
    {
        gameBoard[btmright].openBox();
        checkBtmRight(btmright,gameBoard,_xSize,_maxLength);
    }
}

void checkTopLeft(int index, GameBox *gameBoard, int _xSize, int _maxLength)
{
    int topleft;
    topleft = index + _xSize +1;
    
    if((topleft<_maxLength && !(topleft%_xSize==0)) && gameBoard[topleft].readOpenBox()!='*' && gameBoard[index].readOpenBox()=='0')
    {
        gameBoard[topleft].openBox();
        checkTopLeft(topleft,gameBoard,_xSize,_maxLength);
    } 
}

void checkTopRight(int index, GameBox *gameBoard, int _xSize, int _maxLength)
{
    int topright;
    topright = index + _xSize - 1;
    
    if((topright<_maxLength && !(topright%_xSize==0)) && gameBoard[topright].readOpenBox()!='*' && gameBoard[index].readOpenBox()=='0')
    {
        gameBoard[topright].openBox();
        checkTopRight(topright,gameBoard,_xSize,_maxLength);
    }
}

void printBoard(GameBox *gameBoard, int _xSize, int _maxLength)
{
	int printFlag=0;
	for(int j=_maxLength-1;j>=0;j--)
	{
		cout << gameBoard[j].readBox() << " ";
	
		if(!((j)%(_xSize)) && printFlag!=0)
              	 {
               		cout << endl;
               	}
               printFlag++;

	}
}