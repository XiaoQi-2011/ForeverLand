#ifndef FOREVERLAND_PRODUCER_H
#define FOREVERLAND_PRODUCER_H

#include <utility>
#include <vector>

#include "../Lib/Library.h"
#include "../Lib/Item.h"

/*
 * ==合成所需材料数量==
   头盔: 10
   护甲: 20
   剑: 8
   镐: 12
   --回收价值减半--
*/

struct Producer
{
    int id = 0;
    std::vector<std::pair<int, int>> table;
    Item items;

    Producer() = default;

    explicit Producer(int id, const std::vector<std::pair<int, int>>& table)
    {
        this->id = id;
        this->table = table;
        items.init(init_item);
        for (auto obj : table)
        {
            items[obj.first]->count = obj.second;
        }
    }

    bool produce(Player& player)
    {
        for (auto obj : table)
        {
            if (player.getItem(obj.first) < obj.second)
            {
                return false;
            }
        }
        for (auto obj : table)
        {
            player.items[obj.first]->count -= obj.second;
        }
        player.items[id]->count++;
        return true;
    }
};

inline std::vector<Producer> producers;

inline void initProducers()
{
    producers = {
        //石装备
        Producer(9, {{0, 8}}),
        Producer(10, {{0, 12}}),
        //神秘装备
        Producer(39, {{8, 10}}),
        Producer(40, {{8, 20}}),
        Producer(41, {{8, 8}}),
        Producer(42, {{8, 12}}),
        //战神之刃
        Producer(83, {{6, 24}, {68, 48}}),
        Producer(84, {{83, 1}, {91, 1}}),
        //天顶剑
        Producer(85, {{9, 1}, {13, 1}, {17, 1}, {21, 1}, {25, 1}, {29, 1}, {33, 1}, {37, 1}, {41, 1}}),
        //七宗罪
        Producer(88, {{79, 70}}),
        // 魔刀千刃
        Producer(89, {{80, 100}})
    };
}

const int kinds = 7;
const std::string NumColors[]{
    "\033[1;32m", "\033[0;31m"
};
const int mineralCount[]{
    10, 20, 8, 12
};
const int captureCount[]{
    20, 40, 16, 24
};

inline std::vector<int> indexs;

// 函数声明
void initProducers();
void printValues(bool showId = false);
void producerInit();
void Produce(Player& player);

#endif //FOREVERLAND_PRODUCER_H
