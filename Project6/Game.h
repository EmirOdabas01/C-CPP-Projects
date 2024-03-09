#ifndef GAME_H
#define GAME_H
#include "Blocks.h"

bool chk_crd(const Block* block, int x, int y);
Block* new_blck();
void delete_blck(Block* block);
void drop_blck(Block* block, Map* map);
void input();
void logic(Block* block, Map* map);
void fix_crd(Block* block);
void fix_x_crd(Block* block, int mod);
void rotate(Block* block);
void move_right(Block* block);
void move_left(Block* block);
void move_down(Block* block);
void rotate_S(Block* block);
void rotate_J(Block* block);
void rotate_L(Block* block);
void rotate_T(Block* block);
void rotate_Z(Block* block);
void rotate_I(Block* block);
void place_blck(Block* block, Map* map);
void fix_blck_map_crd(Block* block, Map* map, const cordinate prev, int mod);
bool is_conflict(Block* block, Map* map);
int is_row_full(const Map* map);
void delete_row(Map* map, int idx);
#endif