#ifndef DISPLAY_H
#define DISPLAY_H
#include "Blocks.h"

#include <Windows.h>

void ShowConsoleCursor(bool showFlag);
void MoveCenter();
void MoveWindow(int posx, int posy);
void console_size();
void print_board(const Block* block, const Map* map);

#endif // !DISPLAY_H
