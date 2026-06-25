#ifndef CONSTDATAS_H
#define CONSTDATAS_H

#include <utility>

#include "Data.h"

const int DStart = 4;

struct EData
{
    int itemID = 0;
    std::vector<int> values;

    explicit EData(int itemID, std::vector<int> values)
    {
        this->itemID = itemID;
        this->values = std::move(values);
    }
};

const EData EquipmentData[]{
    EData(9, {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0}),
    EData(10, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 1}),
    EData(11, {0, 5, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    EData(12, {0, 10, 20, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    EData(13, {11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 12, 0, 0}),
    EData(14, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 2}),
    EData(15, {0, 7, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    EData(16, {0, 13, 25, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    EData(17, {16, 0, 0, 0, 1, 0, 0, 0, 0, 2, 15, 0, 0}),
    EData(18, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 2}),
    EData(19, {0, 10, 19, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    EData(20, {0, 17, 31, 31, 0, 1, 1, 0, 0, 0, 0, 0, 0}),
    EData(21, {22, 0, 0, 0, 2, 0, 0, 0, 0, 3, 17, 0, 0}),
    EData(22, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 3}),
    EData(23, {0, 14, 25, 25, 0, 1, 1, 0, 0, 0, 0, 0, 0}),
    EData(24, {0, 22, 38, 38, 0, 2, 2, 0, 0, 0, 0, 0, 0}),
    EData(25, {29, 0, 0, 0, 3, 0, 0, 2, 0, 4, 21, 0, 0}),
    EData(26, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 4}),
    EData(27, {0, 19, 32, 32, 0, 2, 2, 1, 0, 0, 0, 0, 0}),
    EData(28, {0, 28, 46, 46, 0, 3, 3, 2, 1, 0, 0, 0, 0}),
    EData(29, {37, 0, 0, 0, 4, 0, 0, 3, 1, 5, 25, 0, 0}),
    EData(30, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 4}),
    EData(31, {0, 25, 40, 40, 0, 3, 2, 2, 1, 0, 0, 0, 0}),
    EData(32, {0, 35, 55, 55, 0, 5, 4, 4, 2, 0, 0, 0, 0}),
    EData(33, {46, 0, 0, 0, 6, 0, 0, 5, 2, 7, 30, 0, 0}),
    EData(34, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 5}),
    EData(35, {0, 32, 49, 49, 0, 4, 3, 3, 2, 0, 0, 0, 0}),
    EData(36, {0, 43, 65, 65, 0, 7, 6, 6, 3, 0, 0, 0, 0}),
    EData(37, {56, 0, 0, 0, 7, 0, 0, 7, 4, 10, 35, 0, 0}),
    EData(38, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45, 6}),
    EData(39, {0, 39, 59, 59, 0, 5, 4, 4, 2, 0, 0, 0, 0}),
    EData(40, {0, 52, 76, 76, 0, 9, 8, 8, 4, 0, 0, 0, 0}),
    EData(41, {67, 0, 0, 0, 10, 0, 0, 10, 5, 12, 40, 0, 0}),
    EData(42, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 7}),

    EData(73, {0, 5, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0}),
    EData(74, {7, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0}),
    EData(75, {15, 0, 0, 0, 3, 0, 0, 0, 0, 2, 0, 0, 0}),
    EData(76, {0, 5, 20, 20, 0, 0, 0, 3, 3, 0, 0, 0, 0}),
    EData(77, {0, 10, 30, 30, 0, 2, 2, 0, 0, 0, 0, 0, 0}),
    EData(78, {20, 10, 40, 40, 4, 3, 0, 0, 0, 5, 0, 0, 0}),

    EData(83, {52, 0, 0, 0, 6, 0, 0, 6, 3, 9, 25, 0, 0}),
    EData(84, {87, 0, 0, 0, 13, 0, 0, 13, 8, 14, 35, 0, 0}),
    EData(85, {90, 0, 0, 0, 14, 0, 0, 13, 10, 14, 45, 0, 0}),

    EData(86, {110, 0, 0, 0, 20, 0, 0, 15, 10, 15, 54, 0, 0}),
    EData(87, {112, 0, 0, 0, 15, 0, 0, 15, 10, 15, 50, 0, 0}),
    EData(88, {127, 0, 0, 0, 20, 0, 0, 18, 20, 18, 55, 0, 0}),
    EData(89, {132, 0, 0, 0, 22, 0, 0, 17, 19, 17, 55, 0, 0}),

    EData(90, {40, 20, 80, 80, 10, 8, 0, 5, 5, 10, 0, 0, 0}),
};

inline EData getEquipmentData(int itemID)
{
    for (const EData& data : EquipmentData)
    {
        if (data.itemID == itemID)
        {
            return data;
        }
    }
    return EData(0, {});
}

constexpr int basicLocs[]{
    4, 5, 6, 14, 15, 16
};

inline void initEquipmentItem()
{
    bool Etong[DATA_NUM] = {false};
    for (const EData& data : EquipmentData)
    {
        const int id = data.itemID;
        std::vector<int> values = data.values;
        std::stringstream ss;
        memset(Etong, false, sizeof(Etong));
        Etong[7] = true;
        bool flag = false;
        for (const int i : basicLocs)
        {
            if (values[i - DStart] != 0)
            {
                if (!flag)
                {
                    if (!init_item[id].introduce.empty()) ss << "\n";
                    ss << "[基础] ";
                    flag = true;
                }
                ss << getInitData()[i].name << "+" << values[i - DStart] << " ";
                Etong[i] = true;
            }
        }
        flag = false;
        for (int i = 0; i < values.size(); i++)
        {
            if (values[i] != 0 && !Etong[i + DStart])
            {
                if (!flag)
                {
                    ss << "\n[属性] ";
                    flag = true;
                }
                ss << getInitData()[i + DStart].name << "+" << values[i] << " ";
            }
        }
        if (init_item[id].quality == 7)
        {
            int colour = init_item[id].back_ground < 50
                             ? init_item[id].back_ground + 50
                             : init_item[id].back_ground - 70;
            std::string color = "\033[" + std::to_string(colour) + "m";
            init_item[id].introduce += color + ss.str() + "\033[0m";
        }
        else
        {
            init_item[id].introduce += ss.str();
        }
    }
}

inline void takeOffEquipment(Player& player, int slot_id)
{
    if (player.getData(slot_id) != -1)
    {
        int item_id = player.getData(slot_id);
        std::vector<int> values = getEquipmentData(item_id).values;
        for (int i = 0; i < values.size(); i++)
        {
            player.data[i + DStart]->value -= values[i];
        }
        player.items[item_id]->count++;
        player.data[slot_id]->value = -1;
    }
}

inline void putOnEquipment(Player& player, int item_id, int slot_id)
{
    if (player.getData(slot_id) != -1)
    {
        takeOffEquipment(player, slot_id);
    }
    std::vector<int> values = getEquipmentData(item_id).values;
    for (int i = 0; i < values.size(); i++)
    {
        player.data[i + DStart]->value += values[i];
    }
    player.items[item_id]->count--;
    player.data[slot_id]->value = item_id;
}


#endif //CONSTDATAS_H
