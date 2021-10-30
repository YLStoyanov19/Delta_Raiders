#include<iostream>
#include<windows.h> 
#include<conio.h>
#include<fstream>
#include<time.h>
#include<string>
#include<iomanip>
#include<vector>
using namespace std;

class Maze {
public:
	Maze(short r, short c);
	~Maze();
	void Show(vector<int> health);
	bool Go(size_t &size);
private:
	bool Init();
	short GetKeyCode();
	char** maze;
	unsigned short int rows, cols;
	short int currentRow, currentColumn;
};

Maze::Maze(short r, short c) : rows(r), cols(c), currentRow(0), currentColumn(0), maze(nullptr) 
{ 
	if (!Init())
	{
		cout << "Can't open the .txt file";
		exit(1);
	}
};

bool Maze::Init()
{
	ifstream fi;
	unsigned short r, c;

	fi.open("11-21.txt", ios::in);

	if (fi.fail())
		return false;

	maze = new char* [rows];
	if (!maze)
		return false;

	for (r = 0; r < rows; r++)
	{
		maze[r] = new char[cols];

		if (!maze[r])
			return false;

		for (c = 0; c < cols; maze[r][c] = '#', c++);
	}

	unsigned short n;
	fi >> n;

	for (int i = 0; i < n; i++)
	{
		fi >> r >> c;

		if ((r < rows) && (c < cols))
			maze[r][c] = ' ';
	}

	fi.close();

	maze[0][0] = 'X';

	return true;
} //Maze::Init()

void Maze::Show(vector<int> health)
{
	system("cls");
	for (short i = 0; i < rows; i++)
	{
		for (short j = 0; j < cols; j++)
		{
			cout << maze[i][j];
		}
		cout << endl;
	}

	cout << "\n Health: ";
	for (auto i : health)
		cout << i << " ";
}

Maze::~Maze()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] maze[i];
	}
	delete[] maze;

	maze = nullptr;
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

bool Maze::Go(size_t &size)
{
	short int k, newRow, newColumn;
	vector<int> health = {1, 2, 3, 4, 5, 6, 7};

	do {
		Show(health);

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
			Show(health);
		}
		else
		{
			Beep(500, 250);
			health.pop_back();

			size = health.size();

			if (health.size() == 0)
			{
				Show(health);
				break;
			}
		}
	} while ((currentRow != rows - 1) || (currentColumn != cols - 1));

	return false;
} //Maze::Go()

void randomPicker(int& a, int& b)
{
	string random[11] = { "10-10.txt", "11-11.txt", "12-12.txt","13-13.txt", "14-14.txt", "15-15.txt", "16-16.txt", "17-17.txt", "18-18.txt", "19-19.txt", "20-20.txt" };
	string result, num1, num2;

	srand(time(NULL));
	string finalResult = random[rand() % 11];

	for (size_t i = 0; i < finalResult.size(); i++)
	{
		if (isdigit(finalResult[i]))
			result += finalResult[i];
	}

	for (size_t i = 0; i < 2; i++)
		num1 += result[i];
	for (size_t i = 2; i < 4; i++)
		num2 += result[i];

	a = stoi(num1);
	b = stoi(num2);
}

void gamePlay()
{
	int n = 0, m = 0;
	randomPicker(n, m);

	Maze maze(11, 21);

	size_t hp;
	maze.Go(hp);

	if (hp == 0) {
		cout << endl;
		cout << setw(65) << "You lost the game!" << endl;
	}
	else {
		cout << endl;
		cout << setw(65) << "You won the game!" << endl;
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
	int y = 2, choice = 0, x = 2;

	gotoXY(x + 3, y - 2); cout << "Maze Menu";
	gotoXY(x + 1, y); cout << ">";

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
				flag = false;
			}break;

			case 1: {

			}break;

			case 2: {

			}break;

			case 3: {
				cout << setw(65) << "YOU HAVE SUCCESFULLY QUITED !!!" << endl;
				exit(0);
			}break;
			} //switch
		}
	}

	gamePlay();
}//showMenu

int main()
{
	showMenu();
}