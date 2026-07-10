#ifndef FOREVERLAND_BUFF_H
#define FOREVERLAND_BUFF_H

#include <iostream>
#include <thread>
#include <windows.h>
#include "Player.h"

struct Buff
{
    std::string name, color;
    int dataID = 0, value = 0;
    // 刻
    int time = 0, speed = 0;
    bool debuff = false;
    Player* BPlayer;
    std::thread buffTh;

    void buffRun() {
        Player& player = *BPlayer;
        std::string addtion = debuff ? "" : "+";
        if (speed == 0) {
            player.data[dataID]->value += value;
            Sleep(time);
            player.data[dataID]->value -= value;
        } else {
            int times = time / speed;
            for (int i = 0; i < times; i++) {
                if (!player.isFight) return;
                player.data[dataID]->value += value;
                printf("%s你受到 [%s] 效果 %s%d%s\033[0m\n", color.c_str(), name.c_str(), addtion.c_str(), value, player.data[dataID]->name.c_str());
                Sleep(speed);
            }
        }
    }

    Buff() = default;
    Buff(const std::string& name, const std::string& color, int dataID, bool debuff) {
        this->name = name;
        this->color = getColor({color});
        this->dataID = dataID;
        this->debuff = debuff;
        this->name = getColor({color}) + name;
    }

    Buff(const Buff& buffList, int value, int time, int speed = 0) {
        this->name = buffList.name;
        this->color = buffList.color;
        this->dataID = buffList.dataID;
        this->debuff = buffList.debuff;
        this->setBuff(value, time, speed);
    }

    void setBuff(int value, int time, int speed = 0) {
        this->value = value;
        if (debuff) this->value *= -1;
        this->time = time;
        this->speed = speed;
    }

    void addBuff(Player& player) {
        BPlayer = &player;
        std::string addtion = debuff ? "" : "+";
        if (time == 0) {
            player.data[dataID]->value += value;
            printf("%s你受到 [%s] 效果 %s%d%s\033[0m\n", color.c_str(), name.c_str(), addtion.c_str(), value, player.data[dataID]->name.c_str());
            //if (dataID == 6) printf("\033[1;34m你的血量:\033[1;31m%d/%d ", player.getData(6), player.getData(7));
        } else {
            if (speed == 0) {
                printf("%s你获得了 [%s] Buff，持续%.1f秒，%s%d%s\033[0m\n", color.c_str(), name.c_str(), time / 1000.0,
                       addtion.c_str(), value, player.data[dataID]->name.c_str());
            } else {
                printf("%s你获得了 [%s] Buff，持续%.1f秒\033[0m\n", color.c_str(), name.c_str(), time / 1000.0);
            }
            //std::thread(&Buff::buffRun, this).detach();
            buffTh = std::thread(&Buff::buffRun, this);
        }
    }

    ~Buff() {
        if (buffTh.joinable()) {
            buffTh.join();
        }
    }
};

inline const Buff buffList[] {
        Buff("瞬间治疗", "#ff0000", 6, false),
        Buff("瞬间伤害", "#780000", 6, true),
        Buff("力量", "#edb10c", 8, false),
        Buff("虚弱", "#7a7a7a", 8, true),
        Buff("抗性", "#808080", 9, false),
        Buff("脆弱", "#a8a8a8", 9, true),
        Buff("生命恢复", "#fb81fc", 6, false),
        Buff("流血", "#b30000", 6, true),
        Buff("急迫", "#ffc72e", 14, false),
        Buff("冰冻", "#2af0fe", 14, true),
        Buff("速度", "#1ad1ff", 10, false),
        Buff("缓慢", "#6e6e6e", 10, true),
};


#endif //FOREVERLAND_BUFF_H
