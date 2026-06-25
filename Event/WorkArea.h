#ifndef FOREVERLAND_WORKAREA_H
#define FOREVERLAND_WORKAREA_H

#include <iostream>
#include <vector>

#include "../Lib/Library.h"

// 全局变量
inline std::vector<std::pair<int, int>> trash;

// 函数声明
void bin(Player& player);
void decompose(Player& player);
void workArea(Player& player);

#endif //FOREVERLAND_WORKAREA_H
