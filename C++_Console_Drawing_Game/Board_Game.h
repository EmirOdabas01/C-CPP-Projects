#ifndef BOARD_GAME_H
#define BOARD_GAME_H

#include <vector>
#include <conio.h>
#include <algorithm>
#include <set>
#include <iostream>
#include <windows.h>


struct game_prop {
	static const int board_width{ 50 };
	static const int board_height{ 20 };
	static inline int game_mode{};
	static inline bool game_over{};
	static inline long score{ 100'000 };
};

class Player {
public:
	int x;
	int y;
};
class Box {
public:
	Box();
	Box(int x, int y) : x(x), y(y) {}
	bool operator<(const Box& other)const noexcept;
	int x;
	int y;
};
bool crd_control(const std::vector<Box>& boxes, int table_idx);
bool is_table_crd(int x_crd, int y_crd, int idx);
bool is_it_box(const std::vector<Box>& boxes, int x_crd, int y_crd);
bool is_uniqe_vec(const std::vector<Box>& boxes, int x_crd, int y_crd);
void randomize(Player& player, std::vector<Box>& boxes);
std::pair<int, bool> check_crd(Player& ply, std::vector<Box>& boxes);
void logic(Player& ply, std::vector<Box>& boxes);
void input(Player& ply);
void set_up(Player& ply, std::vector<Box>& boxes);
void game_board(const Player& player, const std::vector<Box>& boxes);
int rule_checker(const Player& player, const std::vector<Box>& boxes);
void rule_implementer(Player& player, std::vector<Box>& boxes, int mod);
void ShowConsoleCursor(bool showFlag);



#endif // !BOARD_GAME_H