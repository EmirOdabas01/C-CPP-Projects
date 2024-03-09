
#ifndef BLOCKS_H
#define BLOCKS_H

#include <iostream>
#include <array>
#include <set>

enum class POSMOD {ONE, TWO, THREE, FOUR};
using x_y = std::pair<int, int>;
using cordinate = std::array<x_y, 4>;

struct game_prop
{
	static inline std::size_t board_width{ 40u };
	static inline std::size_t board_height{ 25u };
	static inline std::size_t lft_spc{ 20u };
	static inline long long score{};
	static inline bool game_over{};
};

struct Map {
	Map();
	std::set<x_y> map;
};
struct row_checker {
	row_checker();
	std::set<x_y> last_index;
};
struct Block {
	static inline bool is_exist{ false };
	POSMOD rel_pos;
	cordinate crd_tb;
	virtual void do_nothing();
};

struct O : Block {
	O();
};

struct I : Block {
	I();
};

struct S : Block {
	S();
};

struct Z : Block {
	Z();
};

struct L : Block {
	L();
};

struct J : Block {
	J();
};

struct T : Block {
	T();
};





#endif // !BLOCKS_H