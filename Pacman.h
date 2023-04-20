#ifndef _Pacman_H_
#define _Pacman_H_

#include <cstring>
#include "Point.h"

class ThePacmanGame;

class Pacman {	
	enum { SIZE = 5 };
	Point body;
	bool stay = false;
	int direction = 4;
	char arrowKeys[5];
	//Color color;
	ThePacmanGame* theGame;
public:
	Point initalPosition;
	Point getPosition() {
		return body;
	}
	void setGame(ThePacmanGame* _theGame) {
		theGame = _theGame;
	}
	void setPosition(int y, int x);
	void setPosition(Point pos);
	void setArrowKeys(const char* keys) {
		arrowKeys[0] = keys[0];
		arrowKeys[1] = keys[1];
		arrowKeys[2] = keys[2];
		arrowKeys[3] = keys[3];
		arrowKeys[4] = keys[4];
	}
	//void setColor(Color c) {
	//	color = c;
	//}
	void move();
	int getDirection(char key);
	void setDirection(int dir) {
		direction = dir;
	}
};

#endif