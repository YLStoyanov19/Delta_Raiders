#include<iostream>
#include<windows.h> 
#include<conio.h>
#include<ctime>
#include<cstdlib>
#include<iomanip>

using namespace std;

class Maze
{
public:
	Maze(short r, short c);
	~Maze();
	void Show();
	bool Go();
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
			else // cycles is to big
			{
				// we need to find random ciel in maze, that contains symbol from const label
				do
				{
					//					srand(time(NULL));
					nr = rand() % rows; // now nr contains value between 0 and rows
					nc = rand() % columns; // now nc contains value between 0 and columns
				} while (maze[nr][nc] != label);
				r = nr;
				c = nc;
				cycles = 0;
			}
			//			srand(time(NULL));
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
	Show();

	return true;
} // Maze::Init

Maze::~Maze()
{
	for (unsigned short i = 0; i < rows; i++)
		delete[] maze[i];

	delete[] maze;

	maze = nullptr;
} // Maze::~Maze

void Maze::Show()
{
	system("cls");

	cout << " ";
	for (unsigned short i = 0; i < columns + 2; i++)
		cout << "&";

	cout << endl;

	for (unsigned short i = 0; i < rows; i++)
	{
		for (unsigned short j = 0; j < 1; j++)
			cout << " &";

		for (unsigned short j = 0; j < columns; j++)
			cout << maze[i][j];

		for (unsigned short j = 0; j < 1; j++)
			cout << "&";

		cout << endl;
	}

	cout << " ";
	for (unsigned short i = 0; i < columns + 2; i++)
		cout << "&";

	cout << endl;
} // Maze::Show

short Maze::GetKeyCode()
{
	short KeyCode;
	KeyCode = _getch();
	if ((KeyCode == 0) || (KeyCode == 224)) // функционален клавиш или някоя от стрелките
		KeyCode = _getch();
	return KeyCode;
} // Maze::GetKeyCode

bool Maze::Go()
{
	short k;
	short nr, nc;
	do
	{
		nr = CurrentRow;
		nc = CurrentColumn;
		k = GetKeyCode();
		switch (k)
		{
		case 72:nr--; // стрелка нагоре
			break;
		case 75:nc--; // стрелка наляво
			break;
		case 77:nc++; // стрелка надясно
			break;
		case 80:nr++; // стрелка надолу
			break;
		default:Beep(500, 250);
		} // switch
		if ((nr >= 0) && (nr < rows) && (nc >= 0) && (nc < columns) && (maze[nr][nc] == ' '))
		{
			maze[CurrentRow][CurrentColumn] = ' ';
			CurrentRow = nr;
			CurrentColumn = nc;
			maze[CurrentRow][CurrentColumn] = 'X';
			Show();
		}
		else
			Beep(500, 250);
	} while ((CurrentRow != rows - 1) || (CurrentColumn != columns - 1)); // 27 - код на ESC
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
				
				cout << "Rows: "; cin >> rows;
				cout << "Columns: "; cin >> columns;

				class Maze m(rows, columns);
				m.Go();

				cout << setw(65) << "THE GAME ENDED!" << endl;

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