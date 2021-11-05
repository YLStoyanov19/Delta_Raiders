#include<iostream>
#include<windows.h> 
#include<conio.h>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<vector>

using namespace std;

class Maze
{
public:
	Maze(short r, short c);
	~Maze();
	void Show(vector<char> health);
	bool Go(size_t &size);
private:
	void GeneratePath();
	bool Init();
	short GetKeyCode();
	char** maze;
	unsigned short rows, columns;
	short CurrentRow, CurrentColumn;
}; // Maze

Maze::Maze(short r, short c) : rows(r), columns(c), CurrentRow(0), CurrentColumn(0), maze(nullptr) {
	if (!Init()) {
		cout << "Failed" << endl;
		system("pause");
		exit(1);
	}
}

void Maze::GeneratePath()
{
	const char label = ' ';
	short nr, nc;
	unsigned short r = 0, c = 0, cycles, nb;
	bool possible;

	maze[0][0] = label;
	srand(time(NULL));
	do
	{
		cycles = 0;
		do
		{
			possible = true;

			if (cycles < rows * columns)
			{
				nr = r;
				nc = c;
				cycles++;
			}
			else
			{
				do
				{
					nr = rand() % rows; // nr contains value between 0 and rows
					nc = rand() % columns; // nc contains value between 0 and columns
				} while (maze[nr][nc] != label);
				r = nr;
				c = nc;
				cycles = 0;
			}

			nb = rand();
			nb = nb % 4;

			switch (nb)
			{
			case 0:nc--;
				break;
			case 1:nc++;
				break;
			case 2:nr--;
				break;
			case 3:nr++;
				break;

			} // switch
			if ((nr < 0) || (nr >= rows) || (nc < 0) || (nc >= columns))
				possible = false;
			else
				if (maze[nr][nc] == label)
					possible = false;
				else
				{
					nb = 0;

					if ((nr > 0) && (maze[nr - 1][nc] == label))

						nb++;
					if ((nr < rows - 1) && (maze[nr + 1][nc] == label))

						nb++;
					if ((nc > 0) && (maze[nr][nc - 1] == label))

						nb++;
					if ((nc < columns - 1) && (maze[nr][nc + 1] == label))

						nb++;
					if (nb > 1)
						possible = false;

				}
		} while (!possible);

		r = nr;
		c = nc;
		maze[r][c] = label;

	} while (!((r == rows - 1) && (c == columns - 1)));
} // Maze::GeneratePath

bool Maze::Init()
{
	unsigned short r, c;

	maze = new char* [rows];
	if (!maze)
		return false;
	for (r = 0; r < rows; r++)
	{
		maze[r] = new char[columns];
		if (!maze[r])
			return false;

		for (c = 0; c < columns; maze[r][c] = '#', c++);
	}

	GeneratePath();
	maze[0][0] = 'X';

	return true;
} // Maze::Init

Maze::~Maze()
{
	for (unsigned short i = 0; i < rows; i++)
		delete[] maze[i];

	delete[] maze;

	maze = nullptr;
} // Maze::~Maze

void Maze::Show(vector<char> health)
{
	system("cls");

	const char sign = '&';

	//Top row
	cout << " ";
	for (unsigned short i = 0; i < columns + 2; i++)
		cout << sign;

	cout << endl;

	//Main part
	for (unsigned short i = 0; i < rows; i++)
	{
		for (unsigned short j = 0; j < 1; j++)
			cout << " " << sign;

		for (unsigned short j = 0; j < columns; j++)
			cout << maze[i][j];

		for (unsigned short j = 0; j < 1; j++)
			cout << sign;

		cout << endl;
	}

	//Bottom row
	cout << " ";
	for (unsigned short i = 0; i < columns + 2; i++)
		cout << sign;

	cout << endl << endl;

	cout << "Health: ";
	for (auto i : health)
		cout << i << " ";
} // Maze::Show

short Maze::GetKeyCode()
{
	short KeyCode;
	KeyCode = _getch();
	if ((KeyCode == 0) || (KeyCode == 224)) // функционален клавиш или някоя от стрелките
		KeyCode = _getch();
	return KeyCode;
} // Maze::GetKeyCode

bool Maze::Go(size_t &size)
{
	short k;
	short nr, nc;

	vector<char> health = { '@', '@', '@', '@', '@', '@'};

	Show(health);

	do
	{

		nr = CurrentRow;
		nc = CurrentColumn;
		k = GetKeyCode();

		switch (k)
		{
		case 72:nr--; // arrow up
			break;
		case 75:nc--; // arrow left
			break;
		case 77:nc++; // arrow right
			break;
		case 80:nr++; // arrow down
			break;
		default:Beep(500, 250);
		} // switch

		if ((nr >= 0) && (nr < rows) && (nc >= 0) && (nc < columns) && (maze[nr][nc] == ' '))
		{
			maze[CurrentRow][CurrentColumn] = ' ';
			CurrentRow = nr;
			CurrentColumn = nc;
			maze[CurrentRow][CurrentColumn] = 'X';
			Show(health);
		}
		else
		{
			Beep(500, 250);
			health.pop_back();

			size = health.size();

			if (size == 0) 
			{
				Show(health);
				break;
			}
		}
	} while ((CurrentRow != rows - 1) || (CurrentColumn != columns - 1)); 
	return false;
} // Maze::Go

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
		gotoXY(5, x); cout << "Guide";
		x++;
		gotoXY(5, x); cout << "Quit\n";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 4)
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
				short rows, columns;
				size_t size;
				
				cout << "Rows: "; cin >> rows;
				cout << "Columns: "; cin >> columns;

				class Maze m(rows, columns);
				m.Go(size);

				if (size != 0)
					cout << endl << setw(65) << "You won!" << endl;
				else
					cout << endl << setw(65) << "You lost!" << endl;

				flag = false;
			}break;

			case 1: {

			}break;

			case 2: {
				cout << setw(65) << "YOU HAVE SUCCESFULLY QUITED !!!" << endl;
				exit(0);
			}break;
			} //switch
		}
	}
}//showMenu

int main()
{
	showMenu();
}