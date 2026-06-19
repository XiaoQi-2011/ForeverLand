#ifndef FOREVERLAND_PRODUCER_H
#define FOREVERLAND_PRODUCER_H

#include <iostream>
#include <utility>
#include <vector>

#include "../library.h"
using namespace std;
/*
 * ==合成所需材料数量==
   头盔: 10
   护甲: 20
   剑: 8
   镐: 12
   --回收价值减半--
*/

struct Producer {
    int id = 0;
    vector<pair<int, int>> table;
    ITEM items;

    Producer() = default;
    explicit Producer(int id, const vector<pair<int, int>>& table) {
        this->id = id;
        this->table = table;
        items.init(init_item);
        for (auto obj : table) {
            items[obj.first]->count = obj.second;
        }
    }

    bool produce(Player& player) {
        for (auto obj : table) {
            if (player.getItem(obj.first) < obj.second) {
                return false;
            }
        }
        for (auto obj : table) {
            player.items[obj.first]->count -= obj.second;
        }
        player.items[id]->count ++;
        return true;
    }
};
vector<Producer> producers {
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

const int kinds = 7;
const string NumColors[] {
    "\033[1;32m", "\033[0;31m"
};
const int mineralCount[] {
    10, 20, 8, 12
};
const int captureCount[] {
    20, 40, 16, 24
};
vector<int> indexs;

inline void printValues(bool showId = false) {
    ofstream out("values.txt");
    for (Producer &producer : producers) {
        int jb = 0, zs = 0;
        for (auto obj : producer.table) {
            jb += producer.items[obj.first]->JB_value * obj.second;
            zs += producer.items[obj.first]->ZS_value * obj.second;
        }
        out << jb << " " << zs ;
        if (showId) {
            out << " " << producer.id << endl;
        } else out << endl;
    }
}
inline void producerInit() {
    for (int i = 0; i < kinds; i++) {
        int id = i * 4 + 11;
        int mineral = i + 1;
        int capture = i + 63;
        for (int j = 0; j < 4; j++) {
            producers.push_back(Producer(id, {{mineral, mineralCount[j]},
                                              {capture, captureCount[j]}}));
            if (i == 6) {
                producers.back().table.emplace_back(id - 4, 1);
            }
            id ++;
        }
    }
}
inline void Produce(Player& player) {
    Produce:
    system("cls");
    printf("-合成区-\n\n");

    indexs.clear();
    int n = 0;
    for (int i = 0; i < producers.size(); i++) {
        bool show = false;
        for (auto obj : producers[i].table) {
            if (player.getItem(obj.first) > 0) {
                show = true;
                break;
            }
        }
        if (show) {
            n ++;
            printf("%d.制作 %s\n", n, player.items[producers[i].id]->name.c_str());
            printf("%s\n\033[0;32m>所需材料：\033[0m\n", player.items[producers[i].id]->introduce.c_str());
            vector<pair<string, int>> itemList = producers[i].items.getItemList({"all"}, false);
            //printf("需要：");
            for (const auto& obj : itemList) {
                string color = player.getItem(obj.second) >= producers[i].items[obj.second]->count ?
                        NumColors[0] : NumColors[1];
                printf("%s (你有%s%d\033[0m个)\n", obj.first.c_str(), color.c_str(), player.getItem(obj.second));
            }
            printf("\n");
            indexs.push_back(i);
        }
    }

    printf("\n请输入你要合成的物品序号：\n");
    int choice = getChoice(1, n);
    if (choice == -1) goto Produce;
    if (choice == -2) return;
    if (producers[indexs[choice - 1]].produce(player)) {
        printf("合成成功！\n");
    } else {
        printf("合成失败，材料不足\n");
    }
    system("pause");
    goto Produce;
}

#endif //FOREVERLAND_PRODUCER_H
