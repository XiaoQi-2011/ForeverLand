#ifndef FOREVERLAND_TRADE_H
#define FOREVERLAND_TRADE_H

#include <vector>

#include "../Lib/Library.h"

struct TradeChoice
{
    int index = 0;
    int itemIndex = 0;
    int mode = 0;
    TradeChoice() = default;

    TradeChoice(int index, int itemIndex)
    {
        this->index = index;
        this->itemIndex = itemIndex;
    }

    explicit TradeChoice(int mode)
    {
        this->mode = mode;
    }
};

const int shenmiFlashTime = 600;
inline int shenmiFlash = 0;
inline int shenmiProduct[6];

const int zahuoFlashTime = 600;
inline int zahuoFlash = 0;
inline int zahuoProduct[5];

const int tradeRange = 6;
const int itemRange[tradeRange]{
    6, 9, 7, 4, 5, 6
};
const std::string sellColor = "\033[1;34m";
const std::string buyColor = "\033[1;32m";

// 函数声明
void reflashShenmi(Player& player);
void initShenmi(Player& player);
void reflashZahuo(Player& player);
void initZahuo(Player& player);
TradeChoice getTradeChoice();
bool trade(Player& player, int itemId, int count, bool isBuy, float override = 1.0);
int getAllCount(Player& player, int itemId, bool isBuy, float override = 1.0);
void TradeMenu(Player& player);

#endif //FOREVERLAND_TRADE_H
