#include "io_utils.h"
#include "MainMenu.h"
#include "menuBoard.h"
#include "settingsBoard.h"

void MainMenu::printPage(const char* boardToCopy[ROWS])
{
    for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
            gotoxy(j, i);
			std::cout << boardToCopy[i][j];
		}
	}
}

void MainMenu::runMenu()
{
    printPage(main_menu_board);
    char key;
    while(true)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
            { 
            case '1':
                return;
                break;
            case '8':
                printPage(settings_board);
                	do
                    {
                        if (_kbhit())
                            key = _getch();
                    } while (key != ESC);
                break;
            case '9':
                exit(1);
                break;
            default:
                break;
            }
		}
	}
}