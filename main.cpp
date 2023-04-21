#include <windows.h>
#include <iostream>
#include "ThePacmanGame.h"
#include "_board.h"
#include "MainMenu.h"
using namespace std;

int main() {
	MainMenu menu;
	menu.runMenu();
	ThePacmanGame game;
	game.setBoard(pacman_board);
	game.init();
	game.run();
}