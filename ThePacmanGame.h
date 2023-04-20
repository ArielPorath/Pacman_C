#ifndef _THEPacmanGAME_H_
#define _THEPacmanGAME_H_

#include "io_utils.h"
#include "Pacman.h"
#include "Ghost.h"

enum { ROWS = 24, COLS = 80 , NUMOFBREADCRUMBS = 7};

class ThePacmanGame {
	enum { ESC = 27 };
	int score = 0;
	int lives = 3;
	Pacman p;
	Ghost g[2];
	char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char handleObjectCreationFromBoard(int row, int col); // '@' , '#' are the start points of the Snakes
public:
	void setBoard(const char* boardToCopy[ROWS]); //copy board sent to us into originalBoard, setArrowKeys, setColor
	void init(); //copy original board to actual board and set Snakes Start point
	bool isWall(const Point& p);
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e. changes on board are done here
	bool isBreadcrumb(const Point& p);
	bool isOnBorder(const Point& p);
	void handleCollision();
	void printScoreLives();
	void updateLife();
	void updateScore();
	void winGame();
	void gameOver();
	void setWinBoard();
	void setGameOverBoard();
	char getCharByPoint(const Point& loc);
	void resetLocations();
	void run(); // run 2 Snakes with Keyboard
};

#endif