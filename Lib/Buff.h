#ifndef FOREVERLAND_BUFF_H
#define FOREVERLAND_BUFF_H

#include <iostream>
#include <thread>
#include <windows.h>
#include "Player.h"

struct Buff
{
    std::string name;
    int dataID = 0, value = 0;
    int time = 0, speed = -1;
    bool debuff = false;

    Buff() = default;
    Buff(std::string name, int dataID, int value, int time, bool debuff, int speed = -1) {
        this->name = std::move(name);
        this->dataID = dataID;
        this->value = value;
        this->time = time;
        this->debuff = debuff;
        this->speed = speed;
    }

    void addBuff(Player& player) {
        std::string color = debuff ? getColor({"#e60000"}) : getColor({"#00e600"});
        std::string text = debuff ? "负面" : "正面";
        printf("%s你获得了%sBuff %s 持续%d秒\n", color.c_str(), text.c_str(), name.c_str(), time);
        if (time == 0) {
            player.data[dataID]->value += value;
        } else {
            if (speed == -1) {
                std::thread([&player, this]() {
                    player.data[dataID]->value += value;
                    Sleep(time * 1000);
                    player.data[dataID]->value -= value;
                }).detach();
            }
        }
    }
};


#endif //FOREVERLAND_BUFF_H
