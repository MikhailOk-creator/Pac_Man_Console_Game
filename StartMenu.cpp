#include <iostream>
#include "Game1.h"
#include "Records.h"
#include <vector>
#include <Windows.h>
#include <conio.h>
using namespace std;

enum ConsoleColor {
	Black = 0,
	Red = 4,
	Yellow = 14,
	White = 15
};

vector<vector<char>> logo = {
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', char(219), char(219), char(219), ' ', ' ', ' ', char(219), char(219), ' ', ' ', ' ', char(219), char(219), char(219), ' ', ' ', ' ', ' ', ' ', ' ', ' ', char(219), ' ', ' ', ' ', char(219), ' ', ' ', char(219), char(219), ' ', ' ', char(219), ' ', ' ', ' ', char(219), ' ', },
	{' ', char(219), ' ', ' ', char(219), ' ', char(219), ' ', ' ', char(219), ' ', char(219), ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', char(219), char(219), ' ', char(219), char(219), ' ', char(219), ' ', ' ', char(219), ' ', char(219), char(219), ' ', ' ', char(219), ' '},
	{' ', char(219), ' ', ' ', char(219), ' ', char(219), ' ', ' ', char(219), ' ', char(219), ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', char(219), ' ', char(219), ' ', char(219), ' ', char(219), ' ', ' ', char(219), ' ', char(219), ' ', char(219), ' ', char(219), ' '},
	{' ', char(219), char(219), char(219), ' ', ' ', char(219), char(219), char(219), char(219), ' ' , char(219), ' ', ' ', ' ', ' ', ' ', char(219), char(219), char(219), ' ', ' ', char(219), ' ', ' ', ' ', char(219), ' ', char(219), char(219), char(219), char(219), ' ', char(219), ' ', ' ', char(219), char(219), ' '},
	{' ', char(219), ' ', ' ', ' ', ' ', char(219), ' ', ' ', char(219), ' ', char(219), ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', char(219), ' ', ' ', ' ', char(219), ' ', char(219), ' ', ' ', char(219), ' ', char(219), ' ', ' ', ' ', char(219), ' '},
	{' ', char(219), ' ', ' ', ' ', ' ', char(219), ' ', ' ', char(219), ' ', char(219), ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', char(219), ' ', ' ', ' ', char(219), ' ', char(219), ' ', ' ', char(219), ' ', char(219), ' ', ' ', ' ', char(219), ' '},
	{' ', char(219), ' ', ' ', ' ', ' ', char(219), ' ', ' ', char(219), ' ', ' ', char(219), char(219), char(219), ' ', ' ', ' ', ' ', ' ', ' ', ' ', char(219), ' ', ' ', ' ', char(219), ' ', char(219), ' ', ' ', char(219), ' ', char(219), ' ', ' ', ' ', char(219), ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
}; // логотип игры

int main()
{
	bool exit_game = false;
	while (!exit_game)
	{
		cout << "                                       " <<  "For exit press '0'" << endl;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i < logo.size(); i++)
		{
			for (int j = 0; j < logo[i].size(); j++)
			{
				if (logo[i][j] == ' ')
				{
					SetConsoleTextAttribute(hConsole, (WORD)((Yellow << 4) | Yellow));
					cout << logo[i][j];
				}
				else if (logo[i][j] == char(219))
				{
					SetConsoleTextAttribute(hConsole, (WORD)((Red << 4) | Red));
					cout << logo[i][j];
				}
			}
			cout << endl;
		}
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White)); // Главное меню игры
		cout << endl << "Use your keyboard to control all the game menus:" << endl << "1) Start" << endl << "2) Records" << endl;
		bool play_again = true;
		if (_kbhit)
		{
			switch (_getch())
			{
			case '1':
				while (play_again)
				{
					Game1();
					cout << endl << "Do you want to play again (Y/N)?" << endl;
					bool press_need_button = false;
					while (!press_need_button)
					{
						if (_kbhit)
						{
							switch (_getch())
							{
							case 'N':
								play_again = false;
								press_need_button = true;
								break;
							case 'n':
								play_again = false;
								press_need_button = true;
								break;
							case 'Y':
								press_need_button = true;
								break;
							case 'y':
								press_need_button = true;
								break;
							default:
								break;
							}
						}
					}
				}
				system("cls");
				break;
			case '2':
				Records();
				system("cls");
				break;
			case '0':
				exit_game = true;
				break;
			default:
				system("cls");
				break;
			}
		}
	}
	cout << endl << "Bye! Have a nice day!" << endl;
	Sleep(1000);
	return 0;
}