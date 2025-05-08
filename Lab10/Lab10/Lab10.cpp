#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Red = 4,
	Brown = 6,
	White = 15,
	Gray = 8
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
}

void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}
using namespace std;
int CountOfCoins = 0;
int posX = 2;
int posY = 3;
int lustPosX = 0;
int lustPosY = 0;

int q[48] = { 1, 1, 1, 1, 1, -1, 1, -1, 1, -1, -1, 1, -1, 1, 1 , 1 , 1, 1, 1, 1, 1, -1, 1, 1, -1, -1, 1, -1, 1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1, 1, -1, -1, 1, 1, -1, -1, -1, 1 };

int Map[30][50]{
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 991, 99, 993, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, -1, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, -1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 4, 0, 4, 0, 0, 0, 4, 4, 4, 4, 4, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 10, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 3,
	3, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 9, 0, 0, 0, 4, 4, 0, 0, 3, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 4, 0, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 4, 4, 0, 0, 13, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0, 4, 0, 4, 0, 0, 4, 0, 4, 0, 4, 4, 4, 0, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, -1, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 4, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 3,
	3, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 26, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0, 4, 4, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 19, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 22, 0, 0, 4, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 20, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 15, 0, 0, 3, 3, 3, 0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 3, 3, 3, 0, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 35, 0, 0, 3, 0, 0, 0, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 3, 0, 0, 27, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 34, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 46, 0, 0, 0, 3,
	3, 0, 0, 0, 3, -1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 33, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 3,
	3, 4, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 39, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 31, 0, 0, 0, 4, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};
void Render()
{
	system("cls");
	for (int y = 0; y != 30; y++)
	{
		for (int x = 0; x != 50; x++)
		{
			if (Map[y][x] == -1) { SetColor(Blue, Blue); cout << " 0"; }
			else if (Map[y][x] == 1) { SetColor(White, White); cout << " @"; }
			else if (Map[y][x] == 3) { SetColor(Gray, Gray); cout << " ="; }
			else if (Map[y][x] == 4) { SetColor(Red, Black); cout << " ,"; }
			else if (Map[y][x] == 991) { SetColor(Blue, White); cout << " " + to_string(CountOfCoins); }
			else if (Map[y][x] == 99) { SetColor(Blue, White); cout << " /"; }
			else if (Map[y][x] == 993) { SetColor(Blue, White); cout << " 5"; }
			else if (Map[y][x] == 0) { SetColor(Green, Black); cout << " ."; }
			else { SetColor(Red, Red); cout << " @"; }
		}
		cout << endl;
	}
}

void Move(int x = 0, int y = 0)
{
	lustPosX = posX;
	lustPosY = posY;
	posX += x;
	posY += y;
}

void Death()
{
	setCursorPosition(lustPosX, lustPosY);
	SetColor(Green, Black); cout << " .";
	posX = lustPosX = 2; posY = lustPosY = 3;
	setCursorPosition(lustPosX, lustPosY);
	SetColor(Green, Black); cout << " .";
	setCursorPosition(posX, posY);
	SetColor(White, White); cout << " @";
	CountOfCoins = 0;
	setCursorPosition(46 * 2, 0);
	SetColor(Blue, White); cout << " " + to_string(CountOfCoins);
	Map[1][35] = -1;
	Map[3][21] = -1;
	Map[11][15] = -1;
	Map[21][5] = -1;
	Map[28][48] = -1;
	for (int y = 0; y != 30; y++) {
		for (int x = 0; x != 50; x++) {
			if (Map[y][x] == -1) {
				setCursorPosition(x * 2, y);
				SetColor(Blue, Blue); cout << " 0";
			}
		}
	}
}

void Rendering()
{
	if (Map[posY][posX / 2] == -1)
	{
		CountOfCoins++;
		setCursorPosition(46 * 2, 0);
		SetColor(Blue, White); cout << " " + to_string(CountOfCoins);
		Map[posY][posX / 2] = 0;
	}
	if (Map[posY][posX / 2] == 3)
	{
		posX = lustPosX;
		posY = lustPosY;
	}
	if (Map[posY][posX / 2] == 0)
	{
		setCursorPosition(lustPosX, lustPosY);
		SetColor(Green, Black); cout << " .";
		setCursorPosition(posX, posY);
		SetColor(White, White); cout << " @";
	}
	if (Map[posY][posX / 2] == 4) { Death(); }

	int i = 47;
	while (i != 4)
	{
		for (int y = 0; y < 30; y++)
		{
			for (int x = 0; x < 50; x++)
			{
				if (Map[y][x] == i)
				{
					if (x == 49 || x == 0 || Map[y][x + q[i]] == 3 || Map[y][x + q[i]] == 4) { q[i] *= -1; }
					Map[y][x] = 0;
					setCursorPosition(x * 2, y);
					SetColor(Green, Black); cout << " .";
					Map[y][x + q[i]] = i;
					setCursorPosition((x + q[i]) * 2, y);
					SetColor(Red, Red); cout << " @";
					break;
				}
			}
			if (Map[posY][posX / 2] == i) { Death(); }
		}
		i--;
	}
	setCursorPosition(100, 30);
}

int main() {

	Render();
	int move;
	while (true)
	{
		move = _getch();
		if (move == 27) { exit(EXIT_SUCCESS); }
		if (move == 100 && posX < 98) { Move(2, 0); }
		else if (move == 97 && posX > 1) { Move(-2, 0); }
		else if (move == 115 && posY < 29) { Move(0, 1); }
		else if (move == 119 && posY > 0) { Move(0, -1); }
		Rendering();
		if (CountOfCoins == 5) { break; }

	}
	SetColor(White, Black);
	setCursorPosition(0, 0);
	system("cls");
	std::cout << "\n\n";
	std::cout << "  C O N G R A T U L A T I O N  \n";
	std::cout << "  C O N G R A T U L A T I O N  \n";
	std::cout << "  C O N G R A T U L A T I O N  \n";
	std::cout << "\n\n";
	SetColor(Black, Black);
}
