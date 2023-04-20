#include "ThePacmanGame.h"
#include "winBoard.h"
#include "gameOverBoard.h"

char ThePacmanGame::handleObjectCreationFromBoard(int row, int col)
{
	char ch = originalBoard[row][col];
	if (ch == '@') {
		p.setPosition(row, col);
		return ' ';
	}
	if (ch == '$') {
		if (g[0].getPosition().getX() == -1)
			g[0].setPosition(row, col);
		else
			g[1].setPosition(row, col);
		return ' ';
	}
	return ch;
}
void ThePacmanGame::setBoard(const char* boardToCopy[ROWS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			originalBoard[i][j] = boardToCopy[i][j];
		}
		originalBoard[i][COLS] = '\0';
	}
}
void ThePacmanGame::init()
{
	srand(time(0));
	char currentChar;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			cout << originalBoard[i][j];
			cout.flush();
			currentChar = handleObjectCreationFromBoard(i, j);
			board[i][j] = currentChar;
		}
		board[i][COLS] = '\0';
	}
	printScoreLives();

	p.setGame(this);
	g[0].setGame(this);
	g[1].setGame(this);
	//s[0].setColor(YELLOW);
	p.setArrowKeys("wxads");
}

void ThePacmanGame::run()
{
	char key = 0;
	bool moveGhost = true;
	int dir;
	do
	{
		if (_kbhit())
		{
			key = _getch();
			if ((dir = p.getDirection(key)) != -1)
				p.setDirection(dir);
		}
	} while (key == 0);
	do
	{
		if (moveGhost)
		{
			g[0].move();
			g[1].move();
			moveGhost = false;
		}
		else
			moveGhost = true;

		if (_kbhit())
		{
			key = _getch();
			if (key == ESC) {
				gotoxy(0, 24);
				cout << "Game paused, press ESC again to continue";
				key = -1;
				do {
					if (_kbhit())
					{
						key = _getch();
					}
				} while (key != ESC);
				printScoreLives();
			}
			if ((dir = p.getDirection(key)) != -1)
				p.setDirection(dir);
		}
		handleCollision();
		p.move();
		handleCollision();
		Sleep(300);
	} while (true);
}
char ThePacmanGame::getCharByPoint(const Point& loc) {
	return board[loc.getY()][loc.getX()];
}
bool ThePacmanGame::isWall(const Point& loc) {
	char ch = getCharByPoint(loc);
	if (ch == '+')
		return true;
	return false;
}
bool ThePacmanGame::isBreadcrumb(const Point& p) {
	char ch = getCharByPoint(p);
	if (ch == '*') {
		board[p.getY()][p.getX()] = ' ';
		return true;
	}
	return false;
}
bool ThePacmanGame::isOnBorder(const Point& p) {
	int x = p.getX();
	int y = p.getY();
	return (x == 0 || x == 80 || y == 0 || y == 24);
}
void ThePacmanGame::printScoreLives() {
	gotoxy(0, 24);
	cout << "score: " << score << " lives: " << lives << "                        ";
}
void ThePacmanGame::handleCollision() {
	Point g1Pos = g[0].getPosition();
	Point g2Pos = g[1].getPosition();
	Point pacPos = p.getPosition();
	if ((g1Pos.getX() == pacPos.getX() && g1Pos.getY() == pacPos.getY()) ||
		(g2Pos.getX() == pacPos.getX() && g2Pos.getY() == pacPos.getY())) {
		updateLife();
		resetLocations();
	}
}
void ThePacmanGame::updateLife() {
	lives--;
	printScoreLives();
	if (lives == 0)
		gameOver();
	
}
void ThePacmanGame::updateScore() {
	score++;
	printScoreLives();
	if (score == NUMOFBREADCRUMBS)
		winGame();
}
void ThePacmanGame::winGame() {
	setWinBoard();
	char key = 0;
	do
	{
		if (_kbhit())
		{
			key = _getch();
		}
	} while (key == 0);
	//SetMainMenuPage();
}
void ThePacmanGame::gameOver() {
	setGameOverBoard();
	char key = 0;
	do
	{
		if (_kbhit())
		{
			key = _getch();
		}
	} while (key == 0);
	//SetMainMenuPage();
}
void ThePacmanGame::setWinBoard() {
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			cout << winBoard[i][j];
			cout.flush();
		}
	}
}
void ThePacmanGame::setGameOverBoard() {
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			cout << gameOverBoard[i][j];
			cout.flush();
		}
	}
}
void ThePacmanGame::resetLocations() {
	Point pos;
	pos = p.getPosition();
	pos.draw(' ');
	p.setPosition(p.initalPosition);
	pos = p.getPosition();
	p.setDirection(4);
	pos.draw('@');
	for (int i = 0; i < 2; i++) {
		pos = g[i].getPosition();
		pos.draw(' ');
		g[i].setPosition(g[i].initalPosition);
		pos = g[i].getPosition();
		pos.draw('$');
	}
}
