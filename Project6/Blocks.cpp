#include "Blocks.h"
#include <iostream>

const static std::array<cordinate, 7> start_pst {
   {{x_y(29,0),x_y(30,0),x_y(29,1),x_y(30,1)},      // O
   {x_y(30,0),x_y(30,1),x_y(30,2),x_y(30,3)},      // I
   {x_y(30,0),x_y(31,0),x_y(30,1),x_y(29,1)},     // S
   {x_y(28,0),x_y(29,0),x_y(29,1),x_y(30,1)},    // Z
   {x_y(29,0),x_y(29,1),x_y(29,2),x_y(30,2)},   // L
   {x_y(29,0),x_y(29,1),x_y(29,2),x_y(28,2)},  // J
   {x_y(29,0),x_y(30,0),x_y(31,0),x_y(30,1)}} // T
};

O::O()
{
	crd_tb = start_pst[0];
}

I::I()
{
	crd_tb = start_pst[1];
}

S::S()
{
	crd_tb = start_pst[2];
}

Z::Z()
{
	crd_tb = start_pst[3];
}

L::L()
{
	crd_tb = start_pst[4];
}

J::J()
{
	crd_tb = start_pst[5];
}

T::T()
{
	crd_tb = start_pst[6];
}

void Block::do_nothing()
{
}

Map::Map()
{
	for (int i = game_prop::lft_spc + 1; i < game_prop::board_width -1; i++)
		map.emplace(i,game_prop::board_height);
}


