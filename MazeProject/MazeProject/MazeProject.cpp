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

int main()
{

}