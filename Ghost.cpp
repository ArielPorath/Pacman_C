#include "ThePacmanGame.h"
#include "Ghost.h"
void Ghost::setPosition(int y, int x)
{
	if (initalPosition.getX() == -1)
		initalPosition.set(x, y);
	body.set(x, y);
}
void Ghost::setPosition(Point pos)
{
	if (initalPosition.getX() == -1)
		initalPosition.set(pos);
	body.set(pos);
}
void Ghost::move()
{
	int direction;
	Point next;
	do {
		direction = rand() % 4;
		next = body.next(direction);
	} while (theGame->isWall(next) || theGame->isOnBorder(next));
	body.draw(previousChar);
	previousChar = theGame->getCharByPoint(next);
	body.move(direction);
	//setTextColor(color);
	body.draw('$');
}
int Ghost::getDirection(char key)
{
	for (int i = 0; i < SIZE - 1; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}