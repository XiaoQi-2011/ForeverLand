#ifndef FOREVERLAND_ALCHEMY_H
#define FOREVERLAND_ALCHEMY_H

#include <iostream>

#include "../Lib/Library.h"
#include "../Lib/Entity.h"
#include "../Lib/Buff.h"

const int alchemy_num = 5;

const int playerLevels[alchemy_num] {
    0, 20, 40, 60, 80
};
const int alchemyLevels[alchemy_num] {
    0, 100, 200, 300, 500
};
const std::string alchemyNames[alchemy_num] {
    "\033[0;37m凡阶", "\033[1;36m灵阶", "\033[1;35m玄阶", "\033[0;33m地阶", "\033[0;31m\033[5;31m天阶"
};

const std::string ANumColors[]{
        "\033[1;32m", "\033[0;31m"
};

const std::vector<int> AvalueLoc {
    4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 28, 30, 31
};

struct AData
{
    int itemID = 0;
    std::vector<int> values;

    explicit AData(int itemID, std::vector<int> values)
    {
        this->itemID = itemID;
        this->values = std::move(values);
    }
};
const AData alchemyData[] {
    AData(128, {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(129, {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(130, {9, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(131, {13, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}),
    AData(132, {17, 0, 0, 3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0}),

    AData(133, {0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(134, {0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(135, {0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(136, {0, 12, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(137, {0, 16, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0}),

    AData(138, {0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(139, {0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(140, {0, 0, 15, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}),
    AData(141, {0, 0, 20, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0}),
    AData(142, {0, 0, 25, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0}),

    AData(143, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0}),
    AData(144, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0}),
    AData(145, {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}),
};

struct AMaterial
{
    int itemID = 0;
    std::vector<std::pair<int, int>> values;

    explicit AMaterial(int itemID, std::vector<std::pair<int, int>> values)
    {
        this->itemID = itemID;
        this->values = std::move(values);
    }
};
const AMaterial alchemyMaterials[] {
    AMaterial(128, {{107, 4}, {108, 3}}),
    AMaterial(129, {{111, 4}, {113, 4}}),
    AMaterial(130, {{115, 5}, {117, 5}}),
    AMaterial(131, {{119, 6}, {120, 6}, {122, 6}}),
    AMaterial(132, {{123, 7}, {124, 5}, {125, 7}}),

    AMaterial(133, {{107, 4}, {109, 3}}),
    AMaterial(134, {{111, 4}, {112, 4}}),
    AMaterial(135, {{115, 5}, {118, 5}}),
    AMaterial(136, {{120, 6}, {121, 6}, {122, 6}}),
    AMaterial(137, {{123, 7}, {124, 5}, {126, 7}}),

    AMaterial(138, {{108, 4}, {110, 3}}),
    AMaterial(139, {{112, 4}, {114, 4}}),
    AMaterial(140, {{117, 5}, {118, 5}}),
    AMaterial(141, {{119, 6}, {120, 6}, {121, 6}}),
    AMaterial(142, {{124, 7}, {125, 5}, {126, 7}}),

    AMaterial(143, {{109, 4}, {110, 3}}),
    AMaterial(144, {{111, 4}, {114, 4}}),
    AMaterial(145, {{115, 5}, {116, 5}}),
};


void initElixirItem();

bool useElixir(Player& player, int itemID);

void Alchemy(Player& player);

#endif //FOREVERLAND_ALCHEMY_H
