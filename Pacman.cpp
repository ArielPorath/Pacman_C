#include "ThePacmanGame.h"
#include "Pacman.h"
void Pacman::setPosition(int y, int x)
{
	if (initalPosition.getX() == -1)
		initalPosition.set(x, y);
	body.set(x, y);
}
void Pacman::setPosition(Point pos)
{
	if (initalPosition.getX() == -1)
		initalPosition.set(pos);
	body.set(pos);
}
void Pacman::move()
{
	if (stay || theGame->isWall(body.next(direction)))
		return;

	body.draw(' ');
	body.move(direction);

	if (theGame->isBreadcrumb(body))
		theGame->updateScore();

	//setTextColor(color);
	body.draw('@');

}
int Pacman::getDirection(char key)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}