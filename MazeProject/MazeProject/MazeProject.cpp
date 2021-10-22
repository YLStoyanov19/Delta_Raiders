#include<iostream>
#include<windows.h> 
#include<conio.h>
#include<fstream> // For the dynamic maze path
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

bool Maze::Init()
{
	ifstream fi;
	unsigned short r, c;

	maze = new char* [rows];
	if (!maze) // Checks if the memory is allocated properly
		return false;

	for (r = 0; r < rows; r++)
	{
		maze[r] = new char[cols];

		if (!maze[r]) //Checks if the memory is allocated properly
			return false;

		for (c = 0; c < cols; maze[r][c] = '*', c++);
	}

	fi.open("maze.txt", ios::in);

	if (fi.fail()) // Checks if the file is opened properly
		return false;

	unsigned short n;
	fi >> n;

	for (int i = 0; i < n; i++)
	{
		fi >> r >> c;
		maze[r][c] = ' ';
	}

	fi.close();
	return true;
}

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

Maze::~Maze()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] maze[i];
	}
	delete[] maze;
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

	gotoXY(y + 3, y - 2); cout << "Maze Menu";
	gotoXY(y + 1, y); cout << "->";

	while (flag)
	{
		gotoXY(5, 2); cout << "Maze game";
		gotoXY(5, 3); cout << "Random Map";
		gotoXY(5, 4); cout << "Options";
		gotoXY(5, 5); cout << "Quit";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 5)
		{
			gotoXY(3, y); cout << "  ";
			y++;
			gotoXY(3, y); cout << "->";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 2)
		{
			gotoXY(3, y); cout << "  ";
			y--;
			gotoXY(3, y); cout << "->";
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

			}break;

			case 3: {
				char a; 
				cout << "Do you really want to quit? Y/N: "; cin >> a;

				while (true)
				{
					if (a == 'Y')
					{
						system("cls");
						cout << "You have successfully quited ..." << endl;
						exit(0);
					}
					else if (a == 'N')
					{
						system("cls");
						showMenu();
					}
					else
						cout << "\nYou should type \"Y or N\": "; cin >> a;
				}
			}break;
			}
		}
	}
}//showMenu

int main()
{
	showMenu();
}