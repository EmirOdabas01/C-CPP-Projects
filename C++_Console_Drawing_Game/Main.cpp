#define _CRT_SECURE_NO_WARNINGS
#include "Board_Game.h"

int main()
{
	Player player;
	std::vector<Box> boxes;

	set_up(player, boxes);
	ShowConsoleCursor(false);

	std::cout << "\n\tHow to Play?\n\n" << "\tUse W, A, S, D for contigously movement. 10 points penalty for press\n\n"
		<< "\tUse numeric keybad for 1 block movement, 8 = up, 4 = left, 6 = right, 5 = back. 30 points penalty for press\n\n"
		<< "\tpress space for stop. 20 points penaliy for press\n\n"
		<< "\tFinishing one picture reward is 100 points\n\n"
		<< "\tPress enter to continiue" << std::endl;

	(void)getchar();

	while (!game_prop::game_over)
	{
		game_board(player, boxes);
		std::cout << "YOUR SCORE : " << '[' << game_prop::score << "]\n";

		input(player);
		logic(player, boxes);

		rule_implementer(player, boxes, rule_checker(player, boxes));

		if (crd_control(boxes, game_prop::game_mode))
		{
			if (game_prop::game_mode != 5)
				++game_prop::game_mode;
			else
				break;
			game_prop::score += 100;
			randomize(player, boxes);
		}
		Sleep(25);
	}
	if (game_prop::game_over)
		std::cout << "GAME OVER\n";
	else
	{
		game_board(player, boxes);
		std::cout << "WELL DONE\n";
		std::cout << "YOUR SCORE : " << '[' << game_prop::score << "]\n";
	}
}