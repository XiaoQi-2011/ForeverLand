#ifndef FOREVERLAND_INVENTORYEVENT_H
#define FOREVERLAND_INVENTORYEVENT_H

#include "../Lib/Library.h"

const std::string ignore_types[]{
    "slot", "fuben"
};

const std::string onlyOnceTypes[]{
    "equipment", "consumables_more"
};

// 函数声明
void showPlayerData(Player& player);
void showPlayerItems(Player& player);

#endif //FOREVERLAND_INVENTORYEVENT_H
