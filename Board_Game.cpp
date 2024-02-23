#include "Board_Game.h"


enum  ARROW { LEFT = 52, UP = 56, RIGHT = 54, DOWN = 53 };
enum class MOVE : int { STOP, UP, DOWN, LEFT, RIGHT, AR_UP, AR_DOWN, AR_LEFT, AR_RIGHT };
MOVE dir;

namespace gct
{
	using namespace std;
	static const vector<pair<int, int>> table[]{

		//tank
	 vector{pair{game_prop::board_width + 19,9},pair{game_prop::board_width + 19,7},pair{game_prop::board_width + 21,7},pair{game_prop::board_width + 23,7},pair{game_prop::board_width + 25,7}
		,pair{game_prop::board_width + 27,7},pair{game_prop::board_width + 27,8},pair{game_prop::board_width + 27,9},pair{game_prop::board_width + 19,8},pair{game_prop::board_width + 23,6}},
		//pyramid
	vector{pair{game_prop::board_width + 19,9},pair{game_prop::board_width + 21,9},pair{game_prop::board_width + 23,9},pair{game_prop::board_width + 25,9},pair{game_prop::board_width + 20,8}
		,pair{game_prop::board_width + 22,8},pair{game_prop::board_width + 24,8},pair{game_prop::board_width + 21,7},pair{game_prop::board_width + 23,7},pair{game_prop::board_width + 22,6}},
		//heart
	vector{pair{game_prop::board_width + 21,9},pair{game_prop::board_width + 19,8},pair{game_prop::board_width + 23,8},pair{game_prop::board_width + 17,7},pair{game_prop::board_width + 25,7}
		,pair{game_prop::board_width + 17,6},pair{game_prop::board_width + 21,6},pair{game_prop::board_width + 25,6},pair{game_prop::board_width + 19,5},pair{game_prop::board_width + 23,5}},
		//pickaxe
	vector{pair{game_prop::board_width + 17,9},pair{game_prop::board_width + 25,9},pair{game_prop::board_width + 17,8},pair{game_prop::board_width + 23,8},pair{game_prop::board_width + 19,7}
		,pair{game_prop::board_width + 21,7},pair{game_prop::board_width + 19,6},pair{game_prop::board_width + 21,6},pair{game_prop::board_width + 22,5},pair{game_prop::board_width + 24,5}},
		//tick
		vector{pair{game_prop::board_width + 19,9},pair{game_prop::board_width + 17,8},pair{game_prop::board_width + 21,8},pair{game_prop::board_width + 15,7},pair{game_prop::board_width + 23,7}
		,pair{game_prop::board_width + 13,6},pair{game_prop::board_width + 25,6},pair{game_prop::board_width + 27,5},pair{game_prop::board_width + 29,4},pair{game_prop::board_width + 31,3}}
	};
	static const vector<int> xcd_tb[]
	{
		{8, 8, 8, 4, 0},
		{6, 4, 2, 2, 0},
		{8, 8, 4, 4, 0},
		{8, 7, 4, 3, 0},
		{18, 14, 10, 6, 2},
	};
	static const vector<int> ycd_tb[]
	{
		{3, 2, 1, 1, 0},
		{3, 2, 2, 1, 0},
		{4, 3, 2, 1, 1},
		{4, 4, 2, 2, 0},
		{6, 4, 3, 1, 1},
	};
}
bool crd_control(const std::vector<Box>& boxes, int table_idx)
{
	std::vector<int> x_crd;
	std::vector<int> y_crd;

	for (const auto& elem : boxes)
	{
		x_crd.push_back(elem.x);
		y_crd.push_back(elem.y);
	}

	std::sort(x_crd.begin(), x_crd.end());
	std::sort(y_crd.begin(), y_crd.end());

	for (std::size_t i = 0; i < boxes.size() / 2; i++)
	{
		int temp_x = x_crd[boxes.size() - i - 1] - x_crd[i];
		int temp_y = y_crd[boxes.size() - i - 1] - y_crd[i];

		if (temp_x != gct::xcd_tb[table_idx][i] || temp_y != gct::ycd_tb[table_idx][i])
			return false;
	}

	return true;
}
bool is_table_crd(int x_crd, int y_crd, int idx)
{
	for (const auto& elem : gct::table[idx])
		if (elem.first == x_crd && elem.second == y_crd)
			return true;

	return false;
}
void rule_implementer(Player& player, std::vector<Box>& boxes, int mod)
{
	switch (mod)
	{
	case 0:
		game_prop::score -= 100;
		randomize(player, boxes);
		break;
	case 1:
	case 2:
		game_prop::game_over = true;
		break;
	}
}
int rule_checker(const Player& player, const std::vector<Box>& boxes)
{
	if (std::set<Box> crd_table(boxes.begin(), boxes.end()); crd_table.size() != 10)
		return 0;

	if (std::any_of(boxes.begin(), boxes.end(), [](auto& box) {return box.x == 0 || box.y == -1 || box.x == game_prop::board_width - 1 || box.y == game_prop::board_height; }))
		return 1;

	if (player.x == 0 || player.y == -1 || player.x == game_prop::board_width - 1 || player.y == game_prop::board_height)
		return 2;

	return -1;
}
void set_up(Player& ply, std::vector<Box>& boxes)
{
	ply.x = game_prop::board_width / 2;
	ply.y = game_prop::board_height / 2;
	randomize(ply, boxes);
}
bool is_uniqe_vec(const std::vector<Box>& boxes, int x_crd, int y_crd)
{
	if (boxes.size() == 0)
		return true;

	for (const auto& elem : boxes)
		if (elem.x == x_crd && elem.y == y_crd)
			return false;

	return true;
}
void randomize(Player& player, std::vector<Box>& boxes)
{
	boxes.clear();

	while (boxes.size() < 10)
	{
		int x_cordinate = rand() % (game_prop::board_width - 6) + 3;
		int y_cordinate = rand() % (game_prop::board_height - 6) + 3;

		if (x_cordinate != player.x && y_cordinate != player.y && is_uniqe_vec(boxes, x_cordinate, y_cordinate))
			boxes.push_back(Box{ x_cordinate, y_cordinate });
	}

}

void logic(Player& ply, std::vector<Box>& boxes)
{
	switch (dir)
	{
	case MOVE::UP:
		--ply.y;

		if (auto both_crd = check_crd(ply, boxes); both_crd.second)
			boxes[both_crd.first].y = ply.y - 1;
		break;

	case MOVE::DOWN:
		++ply.y;

		if (auto both_crd = check_crd(ply, boxes); both_crd.second)
			boxes[both_crd.first].y = ply.y + 1;
		break;

	case MOVE::LEFT:
		--ply.x;

		if (auto both_crd = check_crd(ply, boxes); both_crd.second)
			boxes[both_crd.first].x = ply.x - 1;
		break;

	case MOVE::RIGHT:
		++ply.x;

		if (auto both_crd = check_crd(ply, boxes); both_crd.second)
			boxes[both_crd.first].x = ply.x + 1;
		break;

	case MOVE::STOP:
		break;

	case MOVE::AR_UP:
		--ply.y;
		dir = MOVE::STOP;

		if (auto both_crd = check_crd(ply, boxes); both_crd.second)
			boxes[both_crd.first].y = ply.y - 1;
		break;

	case MOVE::AR_DOWN:
		++ply.y;
		dir = MOVE::STOP;

		if (auto both_crd = check_crd(ply, boxes); both_crd.second)
			boxes[both_crd.first].y = ply.y + 1;
		break;

	case MOVE::AR_RIGHT:
		++ply.x;
		dir = MOVE::STOP;

		if (auto both_crd = check_crd(ply, boxes); both_crd.second)
			boxes[both_crd.first].x = ply.x + 1;
		break;

	case MOVE::AR_LEFT:
		--ply.x;
		dir = MOVE::STOP;

		if (auto both_crd = check_crd(ply, boxes); both_crd.second)
			boxes[both_crd.first].x = ply.x - 1;
		break;
	}
}
std::pair<int, bool> check_crd(Player& ply, std::vector<Box>& boxes)
{
	for (std::size_t i = 0; i < boxes.size(); i++)
	{
		if (ply.x == boxes[i].x && ply.y == boxes[i].y)
			return std::pair<int, bool>{i, true};
	}

	return std::pair<int, bool>{0, false};
}
void input(Player& ply)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':

			dir = MOVE::UP;
			game_prop::score -= 10;
			break;

		case 's':

			dir = MOVE::DOWN;
			game_prop::score -= 10;
			break;

		case 'a':

			dir = MOVE::LEFT;
			game_prop::score -= 10;
			break;

		case 'd':

			dir = MOVE::RIGHT;
			game_prop::score -= 10;
			break;

		case ' ':

			dir = MOVE::STOP;
			game_prop::score -= 20;
			break;

		case ARROW::UP:

			dir = MOVE::AR_UP;
			game_prop::score -= 30;
			break;

		case ARROW::DOWN:

			dir = MOVE::AR_DOWN;
			game_prop::score -= 30;
			break;

		case ARROW::LEFT:

			dir = MOVE::AR_LEFT;
			game_prop::score -= 30;
			break;

		case ARROW::RIGHT:

			dir = MOVE::AR_RIGHT;
			game_prop::score -= 30;
			break;
		}
	}
}
bool is_it_box(const std::vector<Box>& boxes, int x_crd, int y_crd)
{
	for (const auto& elem : boxes)
		if (elem.x == x_crd && elem.y == y_crd)
			return true;

	return false;
}
void game_board(const Player& player, const std::vector<Box>& boxes)
{
	system("CLS");
	for (std::size_t i = 0; i < game_prop::board_width; i++)
		std::cout << '#';
	std::cout << '\n';

	for (std::size_t i = 0; i < game_prop::board_height; i++)
	{
		for (std::size_t j = 0; j < game_prop::board_width + 30; j++)
		{
			if (j == game_prop::board_width - 1 || j == 0)
				std::cout << "#";
			else if (j > game_prop::board_width && is_table_crd(j, i, game_prop::game_mode))
				std::cout << "O";
			else if (player.x == j && player.y == i)
				std::cout << 'P';
			else if (is_it_box(boxes, j, i))
				std::cout << 'O';
			else
				std::cout << ' ';
		}
		std::cout << '\n';
	}

	for (std::size_t i = 0; i < game_prop::board_width; i++)
		std::cout << '#';
	std::cout << '\n';
}

bool Box::operator<(const Box& other)const noexcept
{
	if (x != other.x)
		return x < other.x;

	return y < other.y;

}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}