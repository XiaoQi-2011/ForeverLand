#ifndef FOREVERLAND_MINE_H
#define FOREVERLAND_MINE_H


#include <iostream>
#include <thread>
#include <vector>
#include <conio.h>

#include "Fighting.h"
#include "../library.h"
using namespace std;

const int mineNumber = 6;
const Lottery<int> mines[mineNumber] {
    Lottery<int>({{0, 79}, {1, 8}, {2, 6}, {53, 2}, {43, 5}}),
    Lottery<int>({{0, 58}, {1, 15}, {2, 8}, {3, 5}, {53, 3}, {54, 2}, {44, 5}, {45, 4}}),
    Lottery<int>({{0, 38}, {1, 20}, {2, 14}, {3, 7}, {4, 5}, {5, 4}, {54, 3}, {55, 2}, {46, 4}, {47, 3}}),
    Lottery<int>({{0, 47}, {2, 19}, {3, 13}, {4, 6}, {5, 4}, {6, 3}, {55, 2}, {56, 1}, {48, 3}, {49, 2}}),
    Lottery<int>({{0, 57}, {3, 15}, {4, 8}, {5, 6}, {6, 3}, {7, 2}, {55, 4}, {56, 2}, {50, 2}, {51, 1}}),
    Lottery<int>({{0, 98}, {8, 1}, {52, 1}}),
};
const int levels[mineNumber] = {0, 10, 30, 50, 70, 90};
const int mineLevels[mineNumber] = { 1, 2, 3, 4, 5, 6};
const string mineNames[mineNumber] = {"表层矿区", "浅层矿区", "中层矿区", "深层矿区", "远古秘境", "?神秘之地?"};

bool canMine = true;
int stamina = 100;
int mineSpeed = 10;
void MineLoop() {
    while (true) {
        if (!canMine) {
            Sleep(9990 / mineSpeed);
            canMine = true;
        }
        Sleep(1);
    }
}
int tong[ITEM_NUM];
char mineKey = 'e';

inline void Mine(Player& player, int choice) {
    mineKey = player.getStrData(2)[0];
    mineSpeed = player.getData(15);
    escKeyPushEnable = false;

    system("cls");
    printf("--%s--\n", mineNames[choice].c_str());
    printf(">按%c键挖掘，按esc键返回\n\n", mineKey);
    Lottery<int> mine = mines[choice];
    while (true) {
        int key = _getch();
        if (key == mineKey) {
            if (!canMine) continue;
            if (stamina <= 0) {
                printf("你的体力已耗尽!\n\n");
                canMine = false;
                continue;
            }
            int object = mine.lottery();
            string item = player.items[object]->name;
            player.items[object]->count ++;
            printf("你挖到了 %s×1 (当前拥有 %d 个)\n\n", item.c_str(), player.items[object]->count);
            canMine = false;
            stamina --;
        }
        if (escDown) {
            Sleep(120);
            escKeyPushEnable = true;
            return;
        }
    }
}
inline void MineMenu(Player& player) {
    Mine:
    system("cls");
    printf("--矿区--\n\n");
    for (int i = 0; i < mineNumber; i++) {
        memset(tong, 0, sizeof(tong));
        if (player.getData(0) < levels[i]) {
            printf("\033[1;30m-[下一个矿区将在达到 Lv.%d 后解锁]-\033[0m\n\n", levels[i]);
            break;
        }
        for (auto obj : mines[i].objects) {
            tong[obj.object] = obj.percent;
        }
        printf("%d.%s(Lv.%d+ 挖掘等级 %d+)\n", i + 1, mineNames[i].c_str(), levels[i], mineLevels[i]);
        printf("[矿产] ");
        for (int j = 0; j < ITEM_NUM; j++) {
            if (tong[j] == 0) continue;
            if (init_item[j].type == "mineral" || init_item[j].type == "lingshi") {
                printf("%s(%d%%) ", player.items[j]->name.c_str(), tong[j]);
            }
        }
        printf("\n");
        printf("[特殊] ");
        for (int j = 0; j < ITEM_NUM; j++) {
            if (tong[j] == 0) continue;
            if (init_item[j].type == "chest") {
                printf("%s(%d%%) ", player.items[j]->name.c_str(), tong[j]);
            }
        }
        printf("\n\n");
    }

    cout << "请输入序号:" << endl;
    int choice = getChoice(1, mineNumber);
    if (choice == -1) goto Mine;
    if (choice == -2) return;
    choice --;

    if (player.getData(16) < mineLevels[choice]) {
        cout << "挖掘等级不足!" << endl;
        system("pause");
        goto Mine;
    }
    if (player.getData(0) < levels[choice]) {
        cout << "等级不足!" << endl;
        system("pause");
        goto Mine;
    }
    Mine(player, choice);
    goto Mine;
}

#endif //FOREVERLAND_MINE_H
