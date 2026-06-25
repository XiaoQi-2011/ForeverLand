#ifndef FOREVERLAND_MINE_H
#define FOREVERLAND_MINE_H

#include <iostream>
#include <vector>

#include "../Lib/Library.h"
#include "../Lib/Item.h"

constexpr int mineNumber = 6;
inline Lottery<int> mines[mineNumber];

inline void initMines()
{
    mines[0] = Lottery<int>({{0, 79}, {1, 8}, {2, 6}, {53, 2}, {43, 5}});
    mines[1] = Lottery<int>({{0, 58}, {1, 15}, {2, 8}, {3, 5}, {53, 3}, {54, 2}, {44, 5}, {45, 4}});
    mines[2] = Lottery<int>({{0, 38}, {1, 20}, {2, 14}, {3, 7}, {4, 5}, {5, 4}, {54, 3}, {55, 2}, {46, 4}, {47, 3}});
    mines[3] = Lottery<int>({{0, 47}, {2, 19}, {3, 13}, {4, 6}, {5, 4}, {6, 3}, {55, 2}, {56, 1}, {48, 3}, {49, 2}});
    mines[4] = Lottery<int>({{0, 57}, {3, 15}, {4, 8}, {5, 6}, {6, 3}, {7, 2}, {55, 4}, {56, 2}, {50, 2}, {51, 1}});
    mines[5] = Lottery<int>({{0, 98}, {8, 1}, {52, 1}});
}
const int levels[mineNumber] = {0, 10, 30, 50, 70, 90};
const int mineLevels[mineNumber] = {1, 2, 3, 4, 5, 6};
const std::string mineNames[mineNumber] = {"表层矿区", "浅层矿区", "中层矿区", "深层矿区", "远古秘境", "?神秘之地?"};

inline bool canMine = true;
inline int stamina = 100;
inline int mineSpeed = 10;

inline int tong[ITEM_NUM];
inline char mineKey = 'e';

// 函数声明
void initMines();
void MineLoop();
void Mine(Player& player, int choice);
void MineMenu(Player& player);

#endif //FOREVERLAND_MINE_H
