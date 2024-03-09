#include "Game.h"
#include <random>
#include <conio.h>
#include <algorithm>
enum ROTATE {STOP, DOWN, LEFT, RIGHT, TURN};
ROTATE dir;

bool already_setted{};

bool chk_crd(const Block* block, int x, int y)
{
	for (const auto& elem : block->crd_tb)
	{
		if (elem.first == x && elem.second == y)
			return true;
	}

	return false;
}
void fix_crd(Block* block)
{
	std::array<int, 4> x_crds{};
	std::transform(block->crd_tb.begin(), block->crd_tb.end(), x_crds.begin(), [](const auto& elem) { return elem.first; });
	std::sort(x_crds.begin(), x_crds.end());

	if (x_crds.front() - (int)game_prop::lft_spc <= 0)
	{
		fix_x_crd(block, 0);
	}
	else if (x_crds.back() - (int)(game_prop::board_width - 1) >= 0)
	{
		fix_x_crd(block, 1);
	}
}
void fix_x_crd(Block* block, int mod)
{
	for (auto& elem : block->crd_tb)
	{
		elem.first += (mod ? -1 : 1);
	}
}
Block* new_blck()
{
	Block::is_exist = true;

	/*std::random_device r_val;
	std::uniform_int_distribution<int> dist(0, 6);*/

	static std::mt19937 eng{ std::random_device{}() };
	static std::uniform_int_distribution dist{ 0, 6 };

	switch (dist(eng))
	{
	case 0:
		return new O;
	case 1:
		return new I;
	case 2:
		return new S;
	case 3:
		return new Z;
	case 4:
		return new L;
	case 5:
		return new J;
	case 6:
		return new T;
	}
	return nullptr;
}

void delete_blck(Block* block)
{
	delete block;

	Block::is_exist = false;
	already_setted = false;
}

void drop_blck(Block* block, Map* map)
{
	static int count{};
	static int i{ 3 };
	if (count == SHRT_MAX)
	{
		count = 0;
		i = 2;
	}
	if(++count % i == 0)
	for (auto& elem : block->crd_tb)
		 ++elem.second;		

	if (is_conflict(block, map))
	{
		fix_blck_map_crd(block, map, cordinate{}, 0);
		already_setted = true;
	}
}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'd':
			dir = RIGHT;
			break;
		case 'a' :
			dir = LEFT;
			break;
		case 's' :
			dir = DOWN;
			break;
		case 'w' :
			dir = TURN;
			break;
		}
	}
}

void logic(Block* block, Map* map)
{
	int mod{};
	static cordinate prev{};

	switch (dir)
	{
	case DOWN:
		move_down(block);
		mod = 1;
		break;
	case LEFT:
		move_left(block);
		mod = 2;
		break;
	case RIGHT:
		move_right(block);
		mod = 3;
		break;
	case TURN:
	     prev = block->crd_tb;
		rotate(block);
		mod = 4;
		break;
	}
	dir = STOP;
	
	if (!already_setted && is_conflict(block, map))
		fix_blck_map_crd(block, map, prev, mod);
}

void move_right(Block* block)
{
	for (auto& elem : block->crd_tb)
		++elem.first;
}
void move_left(Block* block)
{
	for (auto& elem : block->crd_tb)
		--elem.first;
}
void move_down(Block* block)
{
	for (auto& elem : block->crd_tb)
		++elem.second;
}
void rotate(Block* block)
{
	 if (dynamic_cast<I*>(block))
		rotate_I(block);

	else if (dynamic_cast<S*>(block))
		rotate_S(block);
	
	else if (dynamic_cast<Z*>(block))
		rotate_Z(block);

	else if (dynamic_cast<J*>(block))
		rotate_J(block);

	else if (dynamic_cast<L*>(block))
		rotate_L(block);

	else if (dynamic_cast<T*>(block))
		rotate_T(block);
}
void rotate_I(Block* block)
{
	if (block->rel_pos == POSMOD::ONE)
	{
		--block->crd_tb[0].first;
		++block->crd_tb[0].second;
		++block->crd_tb[2].first;
		--block->crd_tb[2].second;
		block->crd_tb[3].first += 2;
		block->crd_tb[3].second -= 2;
		block->rel_pos = POSMOD::TWO;
	}
	else if(block->rel_pos == POSMOD::TWO)
	{
		++block->crd_tb[0].first;
		--block->crd_tb[0].second;
		--block->crd_tb[2].first;
		++block->crd_tb[2].second;
		block->crd_tb[3].first -= 2;
		block->crd_tb[3].second += 2;
		block->rel_pos = POSMOD::ONE;
	}
}
void rotate_S(Block* block)
{
	if (block->rel_pos == POSMOD::ONE)
	{
		
		++block->crd_tb[1].second;
		++block->crd_tb[3].second;
		block->crd_tb[3].first += 2;
		block->rel_pos = POSMOD::TWO;
	}
	else if (block->rel_pos == POSMOD::TWO)
	{
		--block->crd_tb[1].second;
		--block->crd_tb[3].second;
		block->crd_tb[3].first -= 2;
		block->rel_pos = POSMOD::ONE;
	}
}
void rotate_Z(Block* block)
{
	if (block->rel_pos == POSMOD::ONE)
	{
		++block->crd_tb[0].second;
		block->crd_tb[3].first -= 2;
		++block->crd_tb[3].second;
		block->rel_pos = POSMOD::TWO;
	}
	else if (block->rel_pos == POSMOD::TWO)
	{
		--block->crd_tb[0].second;
		block->crd_tb[3].first += 2;
		--block->crd_tb[3].second;
		block->rel_pos = POSMOD::ONE;
	}
}
void rotate_J(Block* block)
{
	if (block->rel_pos == POSMOD::ONE)
	{
		block->crd_tb[0].first -= 2;
		block->crd_tb[0].second += 2;
		block->crd_tb[1].first -= 2;
		block->rel_pos = POSMOD::TWO;
	}
	else if (block->rel_pos == POSMOD::TWO)
	{
		block->crd_tb[2].first -= 2;
		block->crd_tb[2].second -= 2;
		block->crd_tb[3].second -= 2;
		block->rel_pos = POSMOD::THREE;
	}
	else if (block->rel_pos == POSMOD::THREE)
	{
		block->crd_tb[0].first += 2;
		block->crd_tb[0].second -= 2;
		block->crd_tb[1].first += 2;
		block->rel_pos = POSMOD::FOUR;
	}
	else if (block->rel_pos == POSMOD::FOUR)
	{
		block->crd_tb[2].first += 2;
		block->crd_tb[2].second += 2;
		block->crd_tb[3].second += 2;
		block->rel_pos = POSMOD::ONE;
	}
}
void rotate_L(Block* block)
{
	if (block->rel_pos == POSMOD::ONE)
	{
		block->crd_tb[2].first += 2;
		block->crd_tb[2].second -= 2;
		block->crd_tb[3].second -= 2;
		block->rel_pos = POSMOD::TWO;
	}
	else if (block->rel_pos == POSMOD::TWO)
	{
		block->crd_tb[0].first += 2;
		block->crd_tb[0].second += 2;
		block->crd_tb[1].first += 2;
		block->rel_pos = POSMOD::THREE;
	}
	else if (block->rel_pos == POSMOD::THREE)
	{
		block->crd_tb[2].first -= 2;
		block->crd_tb[2].second += 2;
		block->crd_tb[3].second += 2;
		block->rel_pos = POSMOD::FOUR;
	}
	else if (block->rel_pos == POSMOD::FOUR)
	{
		block->crd_tb[0].first -= 2;
		block->crd_tb[0].second -= 2;
		block->crd_tb[1].first -= 2;
		block->rel_pos = POSMOD::ONE;
	}
}
void rotate_T(Block* block)
{
	if (block->rel_pos == POSMOD::ONE)
	{
		block->crd_tb[0].first += 2;
		++block->crd_tb[0].second;
		++block->crd_tb[1].first;
		block->crd_tb[1].second += 2;
		block->rel_pos = POSMOD::TWO;
	}
	else if (block->rel_pos == POSMOD::TWO)
	{
		--block->crd_tb[0].first;
		++block->crd_tb[0].second;
		block->crd_tb[2].first -= 2;
		block->crd_tb[2].second += 2;
		block->rel_pos = POSMOD::THREE;
	}
	else if (block->rel_pos == POSMOD::THREE)
	{
		--block->crd_tb[0].first;
		block->crd_tb[0].second -= 2;
		block->crd_tb[1].first -= 2;
		--block->crd_tb[1].second;
		block->rel_pos = POSMOD::FOUR;
	}
	else if (block->rel_pos == POSMOD::FOUR)
	{
		++block->crd_tb[1].first;
		--block->crd_tb[1].second;
		block->crd_tb[2].first += 2;
		block->crd_tb[2].second -= 2;
		block->rel_pos = POSMOD::ONE;
	}
}

void place_blck(Block* block, Map* map)
{
	for (const auto& elem : block->crd_tb)
	{
		map->map.emplace(elem.first, elem.second - 1);

		if (elem.second <=5)
			game_prop::game_over = true;
	}
}

void fix_blck_map_crd(Block* block, Map* map,cordinate prev, int mod)
{
	switch (mod)
	{
	case 0:
		place_blck(block, map);
		block->is_exist = false;
		break;
	case 1:
		std::for_each(block->crd_tb.begin(), block->crd_tb.end(), [](auto& elem) {--elem.second; });
		break;
	case 2:
		std::for_each(block->crd_tb.begin(), block->crd_tb.end(), [](auto& elem) {++elem.first; });
		break;
	case 3:
		std::for_each(block->crd_tb.begin(), block->crd_tb.end(), [](auto& elem) {--elem.first; });
		break;
	case 4:
		block->crd_tb = prev;
		break;
	}
	
}
bool is_conflict(Block* block, Map* map)
{
	for (const auto& elem : block->crd_tb)
	{
		if (map->map.contains(elem))
			return true;
	}

	return false;
}
int is_row_full(const Map* map)
{
	int rows = game_prop::board_height - 1;
	std::array<int, 25> conuter{};
	int a{};

	for (int i{}, j{}; i < rows; rows--, j++)
	{
		conuter[j] = std::count_if(map->map.begin(), map->map.end(), [rows](const auto& x) {return x.second == rows; });
		if (conuter[j] == 18)
		{
			return j;
		}
	}
	 return -1;
}
void delete_row(Map* map, int idx)
{
	int row = game_prop::board_height - 1 - idx;

	for (size_t i = game_prop::lft_spc + 1; i < game_prop::board_width -1;i++)
	{
		if (map->map.contains(x_y(i,row)))
		{
			map->map.erase(x_y(i, row));
		}
	}

	for (auto& elem : map->map)
	{
		if (elem.second < row)
		{
			const_cast<x_y&>(elem).second++;
		}
	}
	game_prop::score += 100;
}