#include "Display.h"
#include "Game.h"

int main()
{
	MoveWindow(400, 100);
	console_size();
	ShowConsoleCursor(false);

	std::cout << "\n\tHOW TO PLAY\n" <<
		"\n\tW FOR RATATION\n" <<
		"\n\tL TO SCROLL LEFT\n" <<
		"\n\tR TO SCROLL RIGHT\n";
		"\n\tPRESS ENTER TO START";

	(void)getchar();

	Block* object{ nullptr };
	Map* map{ new Map };
	
	while (!game_prop::game_over)
	{
		if (!Block::is_exist)
		{
		   object = new_blck();
		   object->rel_pos = POSMOD::ONE;
		}

		print_board(object, map);
		drop_blck(object, map);
		input();
		logic(object, map);
		fix_crd(object);

		auto f = is_row_full(map);

		if(f >= 0)
		delete_row(map, f);
	
		if (!Block::is_exist)
			delete_blck(object);

		Sleep(50);
	}

	delete map;
}
