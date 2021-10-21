#include<iostream>
#include<windows.h> 
#include<conio.h>
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD position;

void gotoXY(int x, int y)
{
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(console, position);
}

void showMenu()
{
	bool flag = true;
	int y = 2, choice = 0;

	gotoXY(5, y - 2); cout << "Maze Menu";
	gotoXY(5, y); cout << "->";

	while (flag)
	{
		gotoXY(7, y); cout << "Game";
		gotoXY(7, y + 1); cout << "Options";
		gotoXY(7, y + 2); cout << "Quit";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 4)
		{
			gotoXY(5, y); cout << "  ";
			y++;
			gotoXY(5, y); cout << "->";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 2)
		{
			gotoXY(5, y); cout << "  ";
			y--;
			gotoXY(5, y); cout << "->";
			choice--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{
			system("cls");

			switch (choice)
			{
			case 0: {

			}break;

			case 1: {

			}break;

			case 2: {
				exit(1);
			}break;
			}
		}
	}
}//showMenu

int main()
{

}