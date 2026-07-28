#ifndef FOREVERLAND_ALCHEMY_H
#define FOREVERLAND_ALCHEMY_H

#include <iostream>

#include "../Lib/Library.h"
#include "../Lib/Entity.h"
#include "../Lib/Buff.h"

const int alchemy_num = 5;

int playerLevels[alchemy_num] {
    0, 20, 40, 60, 80
};
int alchemyLevels[alchemy_num] {
    0, 100, 200, 300, 500
};

const std::vector<int> valueLoc {
    4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15, 27, 29, 31
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
    AData(130, {8, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(131, {12, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}),
    AData(132, {16, 0, 0, 3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0}),

    AData(133, {0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(134, {0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(135, {0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(136, {0, 11, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(137, {0, 15, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0}),

    AData(138, {0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(139, {0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    AData(140, {0, 0, 15, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}),
    AData(141, {0, 0, 20, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0}),
    AData(142, {0, 0, 25, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0}),

    AData(143, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0}),
    AData(144, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0}),
    AData(145, {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}),
};

void Alchemy(Player& player);

#endif //FOREVERLAND_ALCHEMY_H
