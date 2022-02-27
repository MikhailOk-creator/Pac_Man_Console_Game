#include "Records.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int Records()
{
    system("cls");
    bool exit_games_records = false;
    vector<string>table_of_records;
	string path = "Records.txt";
	fstream fs;
	fs.open(path, fstream::in | fstream::out);
	string msg;
	while (!fs.eof()) // Изначально все рекорды храняться в соотвтствующам текстовом файле. Данный cpp файл может читать и редактировать исходный файл
	{
		msg = "";
		fs >> msg;
        if (msg != "")
        {
            table_of_records.push_back(msg);
        }
	}
    while (!exit_games_records)
    {
        cout << "                                       " << "For exit press '0'" << endl;
        if (table_of_records.size() > 0) {
            for (int i = 0; i < table_of_records.size(); i++)
            {
                if (i % 2 == 1)
                {
                    cout << table_of_records[i] << endl;
                }
                else
                {
                    cout << table_of_records[i];
                    for (int j = 0; j < 26 - table_of_records[i].size(); j++)
                    {
                        cout << ".";
                    }
                }
            }
        }
        else
        {
            cout << "There are no records yet :(" << endl;
        }
        if (_kbhit)
        {
            switch (_getch())
            {
            case '0':
                exit_games_records = true;
            default:
                system("cls");
                break;
            }
        }
    }
    return 0;
}