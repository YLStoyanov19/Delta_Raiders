#include<iostream>
#include<windows.h> 
#include<conio.h>
using namespace std;

class Maze {
public:
	Maze(short r, short c) : rows(r), cols(c), currentRow(0), currentColumn(0), maze(nullptr) { Init(); };
	~Maze();
	void Show();
private:
	bool Init();
	char** maze;
	unsigned short rows, cols;
	short currentRow, currentColumn;
};

void Maze::Show()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << maze[i][j];
		}
		cout << "\n";
	}
}

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

	gotoXY(5, 0); cout << "Maze Menu";
	gotoXY(5, 2); cout << "->";

	while (flag)
	{
		gotoXY(7, 2); cout << "Game";
		gotoXY(7, 3); cout << "Options";
		gotoXY(7, 4); cout << "Quit";

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
	showMenu();
}