#include "Display.h"
#include "Game.h"


void print_board(const Block* block, const Map* map)
{
	std::system("CLS");

	for (std::size_t i = 0; i <= game_prop::board_height; i++)
	{
		for (std::size_t j = 0; j < game_prop::board_width +2; j++)
		{
			if (i > 2 && (j == game_prop::board_width - 1 || j == 20) )
				std::cout << "#";
			else if (chk_crd(block, j, i))
				std::cout << '#';
			else if (j == game_prop::board_width && i == game_prop::board_height / 2)
				std::cout << "  Your score is ";
			else if (j == game_prop::board_width + 1 && i == game_prop::board_height / 2 + 1)
				std::cout << "  " << game_prop::score;
			else if (map->map.contains(std::pair(j, i)))
				std::cout << '#';
			else
				std::cout << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}
void MoveWindow(int posx, int posy)
{
	RECT rectClient, rectWindow;
	HWND hWnd = GetConsoleWindow();
	GetClientRect(hWnd, &rectClient);
	GetWindowRect(hWnd, &rectWindow);
	MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void MoveCenter()
{
	RECT rectClient, rectWindow;
	HWND hWnd = GetConsoleWindow();
	GetClientRect(hWnd, &rectClient);
	GetWindowRect(hWnd, &rectWindow);
	int posx, posy;
	posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectWindow.right - rectWindow.left) / 2,
		posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectWindow.bottom - rectWindow.top) / 2,

		MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void console_size()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	// 600 500
	MoveWindow(console, r.left, r.top, 600, 600, TRUE);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}