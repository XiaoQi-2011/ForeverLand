#ifndef FOREVERLAND_WORLDBOSS_H
#define FOREVERLAND_WORLDBOSS_H

#include <iostream>
#include <utility>
#include <vector>
#include "../Fighting.h"

#define VP vector<pair<int, int>>
using namespace std;

struct BossCapture {
    int id = 0;
    int minCount = 0, maxCount = 0;
    int percent = 0;
    BossCapture(int id, int minCount, int maxCount, int percent) {
        this->id = id;
        this->minCount = minCount;
        this->maxCount = maxCount;
        this->percent = percent;
    }
};
struct WorldBoss {
    Entity boss;
    int level = 0;
    int flashTime = 0;
    int count = 1;
    string color;

    ITEM item_need;
    int jb_need = 0, zs_need = 0;
    string special;

    bool isFlashed = false, needItem = false;
    vector<BossCapture> capture;

    WorldBoss() = default;
    WorldBoss(string name, string introduce, string color, int level, int flashTime, int jb_need, int zs_need, string special,
               const VP& data, vector<BossCapture> capture, const VP& item_need = {}) {
        if (!color.empty()) {
            name = color + name + "\033[0m";
        }
        boss = createMonster(name, level, false, 1.5);
        //boss.name = std::move(name);
        boss.introduce = std::move(introduce);
        this->level = level;

        this->jb_need = jb_need;
        this->zs_need = zs_need;
        this->special = std::move(special);

        this->capture = std::move(capture);
        this->flashTime = flashTime;
        if (flashTime == 0) {
            isFlashed = true;
        }
        if (!item_need.empty()) {
            needItem = true;
        }
        this->color = std::move(color);
        // 初始化Entity数据
        for (auto i: item_need) {
            this->item_need[i.first]->count = i.second;
        }
        for (auto i: data) {
            boss.data[i.first]->value = i.second;
        }
    }
};
void lotteryCapture(Entity& boss, const vector<BossCapture>& capture) {
    for (auto i: capture) {
        int percent = Random(1, 100);
        if (percent <= i.percent) {
            int count = Random(i.minCount, i.maxCount);
            boss.capture[i.id]->count += count;
        }
    }
}

const int bossCount = 7;
WorldBoss worldBosses[bossCount] {
        WorldBoss("白王·伊邪那美", "仅次于黑王的最强龙王之一", "\033[1;37m",
                  100, 900,
                  100, 0, "",
                  {{1, 5000}, {4, 470}, {5, 128}, {6, 10000}, {7, 10000}, {14, 43}},

                  {{86, 1, 1, 40}, {94, 4, 5, 100}, {96, 2, 3, 100}}
        ),
        WorldBoss("诸神之父·奥丁", "北欧神话中的众神之王，诸神之父，手持掌握命运的永恒之枪「昆古尼尔」，在他面前你将无法闪避", "\033[1;32m",
                  103, 900,
                  100, 0, "你无法在此Boss前闪避",
                  {{1, 5000}, {4, 440}, {5, 150}, {6, 12000}, {7, 12000}},

                  {{87, 1, 1, 40}, {94, 4, 5, 100}, {96, 2, 3, 100}}
        ),
        WorldBoss("Herobrine", "\"Tell me, Do gods bleed?\"\n\"No, but you will\"", "\033[0;36m",
                  92, 600,
                  100, 0, "",
                  {{1, 3000}, {4, 405}, {5, 135}, {6, 7000}, {7, 7000}},

                  {{91, 1, 1, 90}, {94, 2, 3, 100}, {96, 1, 2, 100}}
        ),
        WorldBoss("深渊领主", "来自深渊的目光正在凝视着你", "\033[0m",
                  90, 600,
                  100, 0, "",
                  {{1, 3000}, {4, 400}, {5, 130}, {6, 7000}, {7, 7000}},

                  {{90, 1, 1, 80}, {94, 2, 3, 100}, {96, 1, 2, 100}}
        ),
        WorldBoss("神秘人", "???", "\033[1;35m",
                  95, 0,
                  400, 40, "",
                  {{1, 5000}, {6, 9000}, {7, 9000}},

                  {{8, 1, 2, 100}, {52, 1, 2, 100}}
        ),
        WorldBoss("神官", "只有通过了我的考核，你才能飞升成神", "\033[1;34m",
                  120, 0,
                  500, 50, "",
                  {{1, 4000}, {6, 10000}, {7, 10000}},

                  {{103, 1, 1, 100}}
        ),
        WorldBoss("null", "ahw?a*px&ck^#j", "\033[1;30m",
                  200, 0,
                  0, 0, "掉落物为随机物品",
                  {{6, 100000}, {7, 100000}},

                  {{82, 1, 1, 100}}
        ),
};
inline void worldBoss(Player& player) {
    worldBoss:
    system("cls");
    printf("-世界Boss-\n\n");

    for (int i = 1; i <= bossCount; i++) {
        WorldBoss& boss = worldBosses[i-1];
        // Boss描述
        printf("\033[1;31m%d.-------[%s\033[1;31m]-------\033[0m\n", i, boss.boss.name.c_str(), boss.level);
        printf("%s%s\n", boss.color.c_str(), boss.boss.introduce.c_str());
        // Boss属性
        printf("[基础] ");
        for (int j = 4; j <= 6; j++) {
            printf("%s:%d ", init_data[j].name.c_str(), boss.boss.getData(j));
        }
        printf("\n[属性] ");
        for (int j = 8; j <= 14; j++) {
            printf("%s:%d ", init_data[j].name.c_str(), boss.boss.getData(j));
        }
        // 召唤Boss花费(金币/钻石)
        printf("\n召唤花费: %d金币 %d钻石\n", boss.jb_need, boss.zs_need);
        // Boss刷新状态
        if (boss.flashTime != 0) {
            int time = boss.count * boss.flashTime - second;
            string shuaxin = boss.isFlashed ? "\033[0;32m已刷新" : "\033[0;31m未刷新";
            printf("\033[0;32m刷新: 将在 %dmin%ds 后刷新 %s\n", time / 60, time % 60, shuaxin.c_str());
        }
        // 召唤Boss所需物品
        if (boss.needItem) {
            printf("\033[0;36m召唤需要: \033[0m\n");
            vector<pair<string, int>> itemList = boss.item_need.getItemList({"all"}, false);
            for (const auto & j: itemList) {
                printf("%s \n", j.first.c_str());
            }
            printf("\n");
        }
        // Boss掉落物
        printf("\033[1;34m[Boss掉落]: \033[0m\n");
        for (const auto & capture: boss.capture) {
            if (capture.minCount == capture.maxCount) {
                printf("%s: %d (%d%%)\n", init_item[capture.id].name.c_str(), capture.maxCount, capture.percent);
            } else {
                printf("%s: %d~%d (%d%%)\n", init_item[capture.id].name.c_str(), capture.minCount, capture.maxCount, capture.percent);
            }
        }
        //printf("\n");
        // Boss特殊条件
        if (!boss.special.empty()) {
            printf("\033[1;35m特殊: %s\n", boss.special.c_str());
        }
        // end
        printf("\033[1;31m----------------------------\033[0m\n\n");
    }

    printf("请输入Boss序号: \n");
    int choice = getChoice(1, bossCount);
    if (choice == -1) goto worldBoss;
    if (choice == -2) return;
    Player fakePlayer = player;
    WorldBoss boss = worldBosses[choice-1];
    switch (choice - 1) {
        case 1: {
            fakePlayer.data[10]->value = 0;
            goto Default;
        }
        case 6: {
            int item_id = Random(0, ITEM_NUM - 1);
            while (init_item[item_id].type == "op")
                item_id = Random(0, ITEM_NUM - 1);
            boss.capture = {{item_id, 1, 1, 100}};
            goto Default;
        }
        default: {
            Default:
            // 判断刷新
            if (!boss.isFlashed) {
                printf("Boss未刷新\n");
                system("pause");
                break;
            }
            // 判断召唤物
            if (boss.needItem) {
                bool enough = true;
                for (int i = 0; i < ITEM_NUM; i++) {
                    if (player.getItem(i) < boss.item_need[i]->count) {
                        enough = false;
                        break;
                    }
                }
                if (!enough) {
                    printf("召唤物品不足\n");
                    system("pause");
                    break;
                } else {
                    for (int i = 0; i < ITEM_NUM; i++) {
                        player.items[i]->count -= boss.item_need[i]->count;
                    }
                }
            }
            // 判断召唤费用(金币 钻石)
            if (boss.jb_need > 0 || boss.zs_need > 0) {
                if (player.getData(2) < boss.jb_need || player.getData(3) < boss.zs_need) {
                    printf("召唤所需金币或钻石不足\n");
                    system("pause");
                    break;
                } else {
                    player.data[2]->value -= boss.jb_need;
                    player.data[3]->value -= boss.zs_need;
                }
            }
            // 战斗
            lotteryCapture(boss.boss, boss.capture);
            createFightArea(fakePlayer, "\033[1;31m挑战Boss\033[0m [" + boss.boss.name + "]\033[0m");
            bool wins = fight(fakePlayer, boss.boss, player);
            // 战斗结束处理
            if (boss.flashTime != 0 && wins) worldBosses[choice-1].isFlashed = false;
            break;
        }
    }
    goto worldBoss;
}
#endif //FOREVERLAND_WORLDBOSS_H
