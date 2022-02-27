#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include "Game1.h"
using namespace std;

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Red = 4,
	Magenta = 5,
	LightBlue = 9,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

struct position_of_character
{
	int x;
	int y;
};

bool GameOver, PlayerWin, Ghosts_patrol, patrol1, patrol2, patrol3, patrol4, start_ghosts, escape_ghosts, start;
int score, small_ghosts_patrol_step1, big_ghosts_patrol_step1, small_ghosts_patrol_step2, big_ghosts_patrol_step2, path_of_the_patrol1_steps, path_of_the_patrol2_steps, path_of_the_patrol3_steps, path_of_the_patrol4_steps, change_color_for_escape, time_of_escape_ghosts, bread_counter;
position_of_character PacMan, start_pos_ghosts_left, start_pos_ghosts_right;
vector<position_of_character> Ghosts(4);
char dir;
vector<vector<char>> Map = {
	{char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219)},
	{char(219), '*', '*', '*', '*', '*', '*', '*', '*', char(219), '*', '*', '*', '*', '*', '*', '*', '*', char(219)},
	{char(219), 'O', char(219), char(219), '*', char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), '*', char(219), char(219), 'O',  char(219)},
	{char(219), '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', char(219)},
	{char(219), '*', char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), '*',  char(219)},
	{char(219), '*', '*', '*', '*', char(219), '*', '*', '*', char(219), '*', '*', '*', char(219),'*', '*', '*', '*',  char(219)},
	{char(219), char(219), char(219), char(219), '*', char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), '*', char(219), char(219), char(219), char(219)},
	{' ', ' ', ' ', char(219), '*', char(219), '*', '*', '*', '*', '*', '*', '*', char(219), '*', char(219), ' ', ' ', ' '},
	{char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), ' ', char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219)},
	{' ', ' ', ' ', ' ', '*', '*', '*', char(219), ' ', ' ', ' ', char(219), '*', '*', '*', ' ', ' ', ' ', ' '},
	{char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219)},
	{' ', ' ', ' ', char(219), '*', char(219), '*', '*', '*', '*', '*', '*', '*', char(219), '*', char(219), ' ', ' ', ' '},
	{char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219)},
	{char(219), '*', '*', '*', '*', '*', '*', '*', '*', char(219), '*', '*', '*', '*', '*', '*', '*', '*', char(219)},
	{char(219), '*', char(219), char(219), '*', char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), '*', char(219), char(219), '*',  char(219)},
	{char(219), 'O', '*', char(219), '*', '*', '*', '*', '*', ' ', '*', '*', '*', '*', '*', char(219), '*', 'O', char(219)},
	{char(219), char(219), '*', char(219), '*', char(219), '*', char(219), char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), '*', char(219),  char(219)},
	{char(219), '*', '*', '*', '*', char(219), '*', '*', '*', char(219), '*', '*', '*', char(219),'*', '*', '*', '*',  char(219)},
	{char(219), '*', char(219), char(219), char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219), char(219), char(219), '*', char(219)},
	{char(219), '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', char(219)},
	{char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219)}
};


void SetUp()
{
	start_ghosts = true;
	GameOver = false;
	PlayerWin = false;
	Ghosts_patrol = false;
	escape_ghosts = false;
	start = false;
	patrol1 = false, patrol2 = false, patrol3 = false, patrol4 = false;
	PacMan = { 9,15 };
	start_pos_ghosts_left = { 6, 9 };
	start_pos_ghosts_right = { 12, 9 };
	Ghosts[0] = { 9, 8 };
	Ghosts[1] = { 8, 9 };
	Ghosts[2] = { 9, 9 };
	Ghosts[3] = { 10,9 };
	score = 0;
	small_ghosts_patrol_step1 = 0;
	small_ghosts_patrol_step2 = 0;
	big_ghosts_patrol_step1 = 0;
	big_ghosts_patrol_step2 = 0;
	path_of_the_patrol1_steps = 0;
	path_of_the_patrol2_steps = 0;
	path_of_the_patrol3_steps = 0;
	path_of_the_patrol4_steps = 0;
	bread_counter = 0;
}

void Draw()
{
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < Map.size(); i++)
	{
		for (int j = 0; j < Map[i].size(); j++)
		{
			if (i == PacMan.y && j == PacMan.x)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((Yellow << 4) | Black));
				cout << "P";
			}
			else if (i == Ghosts[0].y && j == Ghosts[0].x)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((Red << 4) | White));
				cout << "M";
			}
			else if (i == Ghosts[1].y && j == Ghosts[1].x)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((Blue << 4) | White));
				cout << "M";
			}
			else if (i == Ghosts[2].y && j == Ghosts[2].x)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((Green << 4) | White));
				cout << "M";
			}
			else if (i == Ghosts[3].y && j == Ghosts[3].x)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((Magenta << 4) | White));
				cout << "M";
			}
			else if (Map[i][j] == char(219))
			{
				SetConsoleTextAttribute(hConsole, (WORD)((LightBlue << 4) | LightBlue));
				cout << Map[i][j];
			}
			else if (Map[i][j] == '*')
			{

				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Yellow));
				cout << Map[i][j];
			}
			else if (Map[i][j] == 'O')
			{

				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Yellow));
				cout << Map[i][j];
			}
			else
			{
				SetConsoleTextAttribute(hConsole, (WORD)(Black << 4));
				cout << " ";
			}
		}
		cout << endl;
	}

	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
	cout << "Score = ";
	COORD position;
	position.X = 15;
	position.Y = 21;
	SetConsoleCursorPosition(hConsole, position);
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
	cout << "Lifes: ";
}


void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 75:
			dir = 'L';
			break;
		case 77:
			dir = 'R';
			break;
		case 72:
			dir = 'U';
			break;
		case 80:
			dir = 'D';
			break;
		}
	}
}

void Logic() //фунукция отвечающая за логику поведения Пакмена. Логика основана на данных введённных с клавиатуры с помощью функции Input
{
	int lastX = PacMan.x, lastY = PacMan.y;
	bool change_pos = false;
	switch (dir)
	{
	case 'L':
		if (PacMan.x != 0)
		{
			if (Map[PacMan.y][PacMan.x - 1] != char(219))
			{
				PacMan.x -= 1;
				change_pos = true;
			}
		}
		else
		{
			PacMan.x = 18;
			change_pos = true;
		}
		break;
	case 'R':
		if (PacMan.x != 18)
		{
			if (Map[PacMan.y][PacMan.x + 1] != char(219))
			{
				PacMan.x += 1;
				change_pos = true;
			}
		}
		else
		{
			PacMan.x = 0;
			change_pos = true;
		}
		break;
	case 'U':
		if (Map[PacMan.y - 1][PacMan.x] != char(219))
		{
			PacMan.y -= 1;
			change_pos = true;
		}
		break;
	case 'D':
		if (Map[PacMan.y + 1][PacMan.x] != char(219))
		{
			PacMan.y += 1;
			change_pos = true;
		}
		break;
	}

	if (change_pos)
	{
		if (Map[PacMan.y][PacMan.x] == '*')
		{
			Map[PacMan.y][PacMan.x] = ' ';
			score += 1;
			bread_counter += 1;
		}
		else if (Map[PacMan.y][PacMan.x] == 'O')
		{
			Map[PacMan.y][PacMan.x] = ' ';
			escape_ghosts = true;
			time_of_escape_ghosts = 0;
		}
		COORD position;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		position.X = PacMan.x;
		position.Y = PacMan.y;
		SetConsoleCursorPosition(hConsole, position);
		SetConsoleTextAttribute(hConsole, (WORD)((Yellow << 4) | Black));
		cout << "P";
		position.X = lastX;
		position.Y = lastY;
		SetConsoleCursorPosition(hConsole, position);
		SetConsoleTextAttribute(hConsole, (WORD)(Black << 4));
		cout << " ";
	}
}

void Algorithm_of_PacMan()
{
	Input();
	Logic();
}


vector<char> path_of_the_patrol1 = { 'U', 'L', 'L', 'L', 'D', 'D' };
vector<char> path_of_the_patrol2 = { 'R', 'U', 'U', 'R', 'R', 'R', 'D', 'D' };
vector<char> path_of_the_patrol3 = { 'U', 'U', 'L', 'L', 'L', 'D', 'D' };
vector<char> path_of_the_patrol4 = { 'L', 'U', 'U', 'R', 'R', 'R', 'D', 'D' };
vector<char> patrol_route1 = { 'L', 'L', 'U', 'U', 'U', 'U', 'L', 'L', 'L', 'U', 'U', 'U', 'U', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'D', 'D', 'R', 'R', 'R', 'R', 'D', 'D', 'L', 'L', 'D', 'D', 'L', 'L', 'L', 'L', 'D', 'D' };
vector<char> patrol_route2 = { 'R', 'R', 'U', 'U', 'U', 'U', 'R', 'R', 'R', 'U', 'U', 'U', 'U', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'D', 'D', 'L', 'L', 'L', 'L', 'D', 'D', 'R', 'R', 'D', 'D', 'R', 'R', 'R', 'R', 'D', 'D' };
vector<char> patrol_route3 = { 'L', 'L', 'D', 'D', 'D', 'D', 'L', 'L', 'L', 'D', 'D', 'R', 'D', 'D', 'L', 'D', 'D', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'U', 'U', 'R', 'R', 'U', 'U', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'U', 'U', 'R', 'R', 'U', 'U', 'R', 'R', 'R', 'R', 'R', 'R', 'U', 'U', 'U', 'U', 'L', 'L', 'L', 'L', 'L', 'L', 'D', 'D' };
vector<char> patrol_route4 = { 'R', 'R', 'D', 'D', 'D', 'D', 'R', 'R', 'R', 'D', 'D', 'L', 'D', 'D', 'R', 'D', 'D', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'U', 'U', 'L', 'L', 'U', 'U', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'U', 'U', 'L', 'L', 'U', 'U', 'L', 'L', 'L', 'L', 'L', 'L', 'U', 'U', 'U', 'U', 'R', 'R', 'R', 'R', 'R', 'R', 'D', 'D' };

void patrol(vector<char> patrol_route, int step, int g) // функция отвечающая за поведение призраков. Их маршрут записан выше
{
	int lastX = Ghosts[g].x, lastY = Ghosts[g].y;
	bool change_pos = false;
	switch (patrol_route[step])
	{
	case 'L':
		if (Map[Ghosts[g].y][Ghosts[g].x - 1] != char(219))
		{
			Ghosts[g].x -= 1;
			change_pos = true;
		}
		break;
	case 'R':
		if (Map[Ghosts[g].y][Ghosts[g].x + 1] != char(219))
		{
			Ghosts[g].x += 1;
			change_pos = true;
		}
		break;
	case 'U':
		if (Map[Ghosts[g].y - 1][Ghosts[g].x] != char(219))
		{
			Ghosts[g].y -= 1;
			change_pos = true;
		}
		break;
	case 'D':
		if (Map[Ghosts[g].y + 1][Ghosts[g].x] != char(219))
		{
			Ghosts[g].y += 1;
			change_pos = true;
		}
		break;
	}

	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = Ghosts[g].x;
	position.Y = Ghosts[g].y;
	SetConsoleCursorPosition(hConsole, position);
	if (change_pos)
	{
		switch (g)
		{
		case 0:
			if (!escape_ghosts)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((Red << 4) | White));
				cout << "M";
			}
			else
			{
				if (change_color_for_escape == 0)
				{
					SetConsoleTextAttribute(hConsole, (WORD)((LightMagenta << 4) | White));
					cout << "M";
				}
				else
				{
					SetConsoleTextAttribute(hConsole, (WORD)((Red << 4) | White));
					cout << "M";
				}
			}
			break;
		case 1:
			if (!escape_ghosts)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((Blue << 4) | White));
				cout << "M";
			}
			else
			{
				if (change_color_for_escape == 0)
				{
					SetConsoleTextAttribute(hConsole, (WORD)((LightMagenta << 4) | White));
					cout << "M";
				}
				else
				{
					SetConsoleTextAttribute(hConsole, (WORD)((Blue << 4) | White));
					cout << "M";
				}
			}
			break;
		case 2:
			if (!escape_ghosts)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((Green << 4) | White));
				cout << "M";
			}
			else
			{
				if (change_color_for_escape == 0)
				{
					SetConsoleTextAttribute(hConsole, (WORD)((LightMagenta << 4) | White));
					cout << "M";
				}
				else
				{
					SetConsoleTextAttribute(hConsole, (WORD)((Green << 4) | White));
					cout << "M";
				}
			}
			break;
		case 3:
			if (!escape_ghosts)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((Magenta << 4) | White));
				cout << "M";
			}
			else
			{
				if (change_color_for_escape == 0)
				{
					SetConsoleTextAttribute(hConsole, (WORD)((LightMagenta << 4) | White));
					cout << "M";
				}
				else
				{
					SetConsoleTextAttribute(hConsole, (WORD)((Magenta << 4) | White));
					cout << "M";
				}
			}
			break;
		}
	}
	position.X = lastX;
	position.Y = lastY;
	SetConsoleCursorPosition(hConsole, position);
	if ((PacMan.x == Ghosts[g].x && PacMan.y == Ghosts[g].y) || (PacMan.x == lastX && PacMan.y == lastY))
	{
		if (escape_ghosts)
		{
			switch (g)
			{
			case 0:
				patrol1 = false;
				path_of_the_patrol1_steps = 0;
				small_ghosts_patrol_step1 = 0;
				Ghosts[0] = { 9, 8 };
				score += 100;
				break;
			case 1:
				patrol2 = false;
				path_of_the_patrol2_steps = 0;
				small_ghosts_patrol_step2 = 0;
				Ghosts[1] = { 8, 9 };
				score += 100;
				break;
			case 2:
				patrol3 = false;
				path_of_the_patrol3_steps = 0;
				big_ghosts_patrol_step1 = 0;
				Ghosts[2] = { 9, 9 };
				score += 100;
				break;
			case 3:
				patrol4 = false;
				path_of_the_patrol4_steps = 0;
				big_ghosts_patrol_step2 = 0;
				Ghosts[3] = { 10, 9 };
				score += 100;
				break;
			}
		}
		else
		{
			GameOver = true;
		}
	}
	if (Map[lastY][lastX] == ' ')
	{
		SetConsoleTextAttribute(hConsole, (WORD)(Black << 4));
		cout << ' ';
	}
	else if (Map[lastY][lastX] == '*')
	{
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Yellow));
		cout << '*';
	}
	else if (Map[lastY][lastX] == 'O')
	{
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Yellow));
		cout << 'O';
	}
}

void Algorithm_of_Ghosts()
{
	if (patrol1)
	{
		if (patrol_route1.size() <= small_ghosts_patrol_step1)
		{
			small_ghosts_patrol_step1 = 0;
		}
		patrol(patrol_route1, small_ghosts_patrol_step1, 0);
		small_ghosts_patrol_step1 += 1;
	}
	else
	{
		patrol(path_of_the_patrol1, path_of_the_patrol1_steps, 0);
		path_of_the_patrol1_steps += 1;
		if (Ghosts[0].x == start_pos_ghosts_left.x && Ghosts[0].y == start_pos_ghosts_left.y)
		{
			patrol1 = true;
		}
	}

	if (patrol2)
	{
		if (patrol_route2.size() <= small_ghosts_patrol_step2)
		{
			small_ghosts_patrol_step2 = 0;
		}
		patrol(patrol_route2, small_ghosts_patrol_step2, 1);
		small_ghosts_patrol_step2 += 1;
	}
	else
	{
		if (path_of_the_patrol3_steps > 2)
		{
			patrol(path_of_the_patrol2, path_of_the_patrol2_steps, 1);
			path_of_the_patrol2_steps += 1;
			if (Ghosts[1].x == start_pos_ghosts_right.x && Ghosts[1].y == start_pos_ghosts_right.y)
			{
				patrol2 = true;
			}
		}
	}

	if (patrol3)
	{
		if (patrol_route3.size() <= big_ghosts_patrol_step1)
		{
			big_ghosts_patrol_step1 = 0;
		}
		patrol(patrol_route3, big_ghosts_patrol_step1, 2);
		big_ghosts_patrol_step1 += 1;
	}
	else
	{
		if (path_of_the_patrol1_steps > 2)
		{
			patrol(path_of_the_patrol3, path_of_the_patrol3_steps, 2);
			path_of_the_patrol3_steps += 1;
			if (Ghosts[2].x == start_pos_ghosts_left.x && Ghosts[2].y == start_pos_ghosts_left.y)
			{
				patrol3 = true;
			}
		}
	}

	if (patrol4)
	{
		if (patrol_route3.size() <= big_ghosts_patrol_step2)
		{
			big_ghosts_patrol_step2 = 0;
		}
		patrol(patrol_route4, big_ghosts_patrol_step2, 3);
		big_ghosts_patrol_step2 += 1;
	}
	else
	{
		if (path_of_the_patrol2_steps > 2)
		{
			patrol(path_of_the_patrol4, path_of_the_patrol4_steps, 3);
			path_of_the_patrol4_steps += 1;
			if (Ghosts[3].x == start_pos_ghosts_right.x && Ghosts[3].y == start_pos_ghosts_right.y)
			{
				patrol4 = true;
			}
		}
	}
}



int Game1()
{
	int rounds = 0;
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (rounds < 3 && !PlayerWin)
	{
		SetUp();
		Draw();
		for (int i = 0; i < 3 - rounds; i++)
		{
			position.X = 21 + i * 2;
			position.Y = 21;
			SetConsoleCursorPosition(hConsole, position);
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Yellow));
			cout << char(219) << " ";
		}
		position.X = 0;
		position.Y = 22;
		SetConsoleCursorPosition(hConsole, position);
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
		cout << endl << "Press 'S' to start"  << endl;
		while (!start)
		{
			if (_kbhit)
			{
				if (_getch() == 's')
				{
					start = true;
				}
			}
		}
		Draw();
		for (int i = 0; i < 3 - rounds; i++)
		{
			position.X = 21 + i * 2;
			position.Y = 21;
			SetConsoleCursorPosition(hConsole, position);
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Yellow));
			cout << char(219) << " ";
		}
		while (!GameOver && !PlayerWin)
		{
			if (bread_counter < 176)
			{
				Sleep(300);
				Algorithm_of_PacMan();
				Algorithm_of_Ghosts();
				if (time_of_escape_ghosts == 20)
				{
					escape_ghosts = false;
				}
				if (escape_ghosts)
				{
					time_of_escape_ghosts += 1;
				}
				if (change_color_for_escape == 0)
				{
					change_color_for_escape += 1;
				}
				else
				{
					change_color_for_escape = 0;
				}
				position.X = 8;
				position.Y = 21;
				SetConsoleCursorPosition(hConsole, position);
				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
				cout << score;
			}
			else
			{
				PlayerWin = true;
			}
		}
		rounds += 1;
	}

	if (PlayerWin)
	{
		SetConsoleTextAttribute(hConsole, (WORD)((Yellow << 4) | Black));
		cout << endl << "YOU WIN!!!" << endl;

		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
		vector<string>table_of_records;
		string path = "Records.txt";
		fstream fs;
		fs.open(path, fstream::in | fstream::out);
		string msg;
		while (!fs.eof())
		{
			msg = "";
			fs >> msg;
			if (msg != "")
			{
				table_of_records.push_back(msg);
			}
		}
		fs.close();
		ofstream fout;
		fs.open(path);
		if (table_of_records.size() == 0)
		{
			cout << "Please enter your name (The name must not contain more than 25 characters). This is for the high score table:" << endl;
			string name;
			cin >> name;
			fout.open(path);
			fout << name << " " << score << endl;
		}
		else if (table_of_records.size() < 20)
		{
			cout << "Please enter your name (The name must not contain more than 25 characters). This is for the high score table:" << endl;
			string name;
			cin >> name;
			fout.open(path);
			int i = 0;
			bool ns_in_t = false;
			while (i + 1 != table_of_records.size())
			{
				if (i + 1 < score)
				{
					if (!ns_in_t)
					{
						fout << name << " " << score << endl;
						ns_in_t = true;
					}
					else
					{
						fout << table_of_records[i] << " " << table_of_records[i + 1] << endl;
						i += 2;
					}
				}
				else
				{
					fout << table_of_records[i] << " " << table_of_records[i + 1] << endl;
					i += 2;
				}
			}
			fout.close();
		}
		else if (table_of_records.size() == 20)
		{
			cout << "Please enter your name (The name must not contain more than 25 characters). This is for the high score table:" << endl;
			string name;
			cin >> name;
			fout.open(path);
			int i = 0;
			bool ns_in_t = false;
			while (i + 1 != 20)
			{
				if (i + 1 < score)
				{
					if (!ns_in_t)
					{
						fout << name << " " << score << endl;
						ns_in_t = true;
					}
					else
					{
						fout << table_of_records[i] << " " << table_of_records[i + 1] << endl;
						i += 2;
					}
				}
				else
				{
					fout << table_of_records[i] << " " << table_of_records[i + 1] << endl;
					i += 2;
				}
			}
			fout.close();
		}
	}
	else if (GameOver)
	{
		position.X = 21;
		position.Y = 21;
		SetConsoleCursorPosition(hConsole, position);
		SetConsoleTextAttribute(hConsole, (WORD)(Black << 4));
		cout << " ";
		SetConsoleTextAttribute(hConsole, (WORD)((Red << 4) | Black));
		cout << endl << "GAME OVER" << endl;
	}
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
	Map = {
		{char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219)},
		{char(219), '*', '*', '*', '*', '*', '*', '*', '*', char(219), '*', '*', '*', '*', '*', '*', '*', '*', char(219)},
		{char(219), 'O', char(219), char(219), '*', char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), '*', char(219), char(219), 'O',  char(219)},
		{char(219), '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', char(219)},
		{char(219), '*', char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), '*',  char(219)},
		{char(219), '*', '*', '*', '*', char(219), '*', '*', '*', char(219), '*', '*', '*', char(219),'*', '*', '*', '*',  char(219)},
		{char(219), char(219), char(219), char(219), '*', char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), '*', char(219), char(219), char(219), char(219)},
		{' ', ' ', ' ', char(219), '*', char(219), '*', '*', '*', '*', '*', '*', '*', char(219), '*', char(219), ' ', ' ', ' '},
		{char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), ' ', char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219)},
		{' ', ' ', ' ', ' ', '*', '*', '*', char(219), ' ', ' ', ' ', char(219), '*', '*', '*', ' ', ' ', ' ', ' '},
		{char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219)},
		{' ', ' ', ' ', char(219), '*', char(219), '*', '*', '*', '*', '*', '*', '*', char(219), '*', char(219), ' ', ' ', ' '},
		{char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219)},
		{char(219), '*', '*', '*', '*', '*', '*', '*', '*', char(219), '*', '*', '*', '*', '*', '*', '*', '*', char(219)},
		{char(219), '*', char(219), char(219), '*', char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), '*', char(219), char(219), '*',  char(219)},
		{char(219), 'O', '*', char(219), '*', '*', '*', '*', '*', ' ', '*', '*', '*', '*', '*', char(219), '*', 'O', char(219)},
		{char(219), char(219), '*', char(219), '*', char(219), '*', char(219), char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), '*', char(219),  char(219)},
		{char(219), '*', '*', '*', '*', char(219), '*', '*', '*', char(219), '*', '*', '*', char(219),'*', '*', '*', '*',  char(219)},
		{char(219), '*', char(219), char(219), char(219), char(219), char(219), char(219), '*', char(219), '*', char(219), char(219), char(219), char(219), char(219), char(219), '*', char(219)},
		{char(219), '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', char(219)},
		{char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219), char(219)}
	};
	return 0;
}