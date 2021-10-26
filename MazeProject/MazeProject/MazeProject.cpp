#include<iostream>
#include<windows.h> 
#include<conio.h>
#include<fstream>

using namespace std;

class Maze {
public:
	Maze(short r, short c) : rows(r), cols(c), currentRow(0), currentColumn(0), maze(nullptr) { Init(); };
	~Maze();
	void Show();
	bool Go();
private:
	bool Init();
	short GetKeyCode();
	char** maze;
	unsigned short int rows, cols;
	short int currentRow, currentColumn;
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
} //Maze::Init()

void Maze::Show()
{
	for (short i = 0; i < rows; i++)
	{
		for (short j = 0; j < cols; j++)
		{
			cout << maze[i][j];
		}
		cout << endl;
	}
}

Maze::~Maze()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] maze[i];
	}
	delete[] maze;

	maze = nullptr;
	system("cls");
}

short Maze::GetKeyCode()
{
	short keyCode;
	keyCode = _getch();

	if ((keyCode == 0) || (keyCode == 224))
	{
		keyCode = _getch();
	}

	return keyCode;
}

bool Maze::Go()
{
	short int k, newRow, newColumn;

	do {
		newRow = currentRow;
		newColumn = currentColumn;

		k = GetKeyCode();

		switch (k)
		{
		case 72:{
			newRow--;
		}break;

		case 80: {
			newRow++;
		}break;

		case 77: {
			newColumn++;
		}break;

		case 75: {
			newColumn--;
		}break;

		default: Beep(500, 250);

		} //switch

		if ((newRow >= 0) && (newRow < rows) && (currentRow >= 0) && (currentRow < cols) && (maze[newRow][newColumn] == ' '))
		{
			maze[currentRow][currentColumn] = ' ';
			currentRow = newRow;
			currentColumn = newColumn;
			maze[currentRow][currentColumn] = 'X';
		}
		else
			Beep(500, 250);
	} while ((currentRow != rows - 1) || (currentColumn != cols - 1));

	return false;
} //Maze::Go()

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
	cout << setw(9) << "///" << setw(9) << "///" << setw(20) << "/////////" << setw(15) << "////////" << setw(20) << "////////" << endl;
	cout << setw(7) << "//" << setw(3) << "//" << setw(6) << "//" << setw(3) << "///" << setw(11) << "//" << setw(7) << "//" << setw(15) << "//" << setw(14) << "//" << endl;
	cout << setw(6) << "//" << setw(4) << "//" << setw(5) << "//" << setw(4) << "//" << setw(10) << "//" << setw(7) << "//" << setw(15) << "//" << setw(14) << "//" << endl;
	cout << setw(5) << "//" << setw(5) << "//" << setw(4) << "//" << setw(5) << "//" << setw(9) << "//" << "///////" << setw(15) << "//" << setw(14) << "//" << "//////" << endl;
	cout << setw(4) << "//" << setw(9) << "/////" << setw(6) << "//" << setw(8) << "//" << setw(7) << "//" << setw(15) << "//" << setw(14) << "//" << endl;
	cout << setw(3) << "//" << setw(16) << "//" << setw(7) << "//" << setw(7) << "//" << setw(15) << "//" << setw(14) << "//" << endl;
	cout << setw(2) << "//" << setw(16) << "//" << setw(7) << "//" << setw(7) << "//" << setw(15) << "//" << "//////" << setw(8) << "//" << "//////" << endl;

	cout << endl;

	cout << setw(9) << "///" << setw(9) << "///" << setw(17) << "////////" << setw(8) << "//" << "//" << setw(8) << "//" << setw(7) << "//" << setw(8) << "//" << "//" << endl;
	cout << setw(7) << "//" << setw(3) << "//" << setw(6) << "//" << setw(3) << "///" << setw(9) << "//" << setw(14) << "//" << setw(3) << "//" << setw(7) << "//" << setw(7) << "//" << setw(7) << "//" << setw(3) << "//" << endl;
	cout << setw(6) << "//" << setw(4) << "//" << setw(5) << "//" << setw(4) << "//" << setw(8) << "//" << setw(14) << "//" << setw(4) << "//" << setw(6) << "//" << setw(7) << "//" << setw(6) << "//" << setw(4) << "//" << endl;
	cout << setw(5) << "//" << setw(5) << "//" << setw(4) << "//" << setw(5) << "//" << setw(7) << "//" << "//////" << setw(8) << "//" << setw(5) << "//" << setw(5) << "//" << setw(7) << "//" << setw(5) << "//" << setw(5) << "//" << endl;
	cout << setw(4) << "//" << setw(9) << "/////" << setw(6) << "//" << setw(6) << "//" << setw(14) << "//" << setw(6) << "//" << setw(4) << "//" << setw(7) << "//" << setw(4) << "//" << setw(6) << "//" << endl;
	cout << setw(3) << "//" << setw(16) << "//" << setw(5) << "//" << setw(14) << "//" << setw(7) << "//" << setw(3) << "//" << setw(7) << "//" << setw(3) << "//" << setw(7) << "//" << setw(3) << "//" << endl;
	cout << setw(2) << "//" << setw(16) << "//" << setw(5) << "//" << "//////" << setw(8) << "//" << setw(8) << "//" << "//" << setw(7) << "//" << "//" << setw(8) << "//" << "//" << endl;

	bool flag = true;
	int y = 2, choice = 0, x = 2;

	gotoXY(x + 3, y - 2); cout << "Maze Menu";
	gotoXY(x + 1, y); cout << "->";

	while (flag)
	{
		x = 2;

		gotoXY(5, x); cout << "Maze game";
		x++;
		gotoXY(5, x); cout << "Random Map";
		x++;
		gotoXY(5, x); cout << "Options";
		x++;
		gotoXY(5, x); cout << "Quit\n";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 5)
		{
			gotoXY(3, y); cout << "  ";
			y++;
			gotoXY(3, y); cout << ">";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 2)
		{
			gotoXY(3, y); cout << "  ";
			y--;
			gotoXY(3, y); cout << ">";
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
					if (a == 'Y' || a == 'y')
					{
						system("cls");
						cout << "You have successfully quited ..." << endl;
						exit(0);
					}
					else if (a == 'N' || a == 'y')
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