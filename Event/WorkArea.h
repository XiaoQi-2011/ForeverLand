#ifndef FOREVERLAND_WORKAREA_H
#define FOREVERLAND_WORKAREA_H

#include <iostream>
#include <vector>
#include <conio.h>

#include "../library.h"

using namespace std;

// 1
vector<pair<int, int>> trash;
void bin(Player& player) {
    bin:
    system("cls");
    printf("-垃圾桶-\n(游戏进程结束时才会消失)\n\n");
    for (int i = 0; i < trash.size(); i++) {
        printf("a%d.%s×%d\n\n", i + 1, player.items[trash[i].first]->name.c_str(), trash[i].second);
    }
    //cout << endl;
    printf("-背包-\n\n");
    vector<pair<string, int>> itemList = player.getItemList({"all"}, false);
    for (int i = 0; i < itemList.size(); i++) {
        printf("%d.%s\n\n", i + 1, itemList[i].first.c_str());
    }
    printf("请输入序号(拿出或放入垃圾桶): \n");
    string input;
    int choice = getChoice(1, itemList.size(), input, {"a%d%"});
    if (choice == -1) goto bin;
    if (choice == -2) return;
    if (choice == -3) {
        int index = stoi(input.substr(1, input.size() - 1));
        int itemId = trash[index - 1].first;
        int itemCount = trash[index - 1].second;
        player.items[itemId]->count += itemCount;
        trash.erase(trash.begin() + index - 1);
        printf("物品已放入背包\n");
        system("pause");
        goto bin;
    }
    int itemId = itemList[choice - 1].second;
    int itemCount = player.items[itemId]->count;
    bool hasItem = false;
    for (auto & i : trash) {
        if (i.first == itemId) {
            i.second += itemCount;
            hasItem = true;
            break;
        }
    }
    if (!hasItem) {
        trash.emplace_back(itemId, itemCount);
    }
    player.items[itemId]->count = 0;
    printf("物品已放入垃圾桶\n");
    system("pause");
    goto bin;
}

//2
void decompose(Player& player) {
    decompose:
    system("cls");
    printf("-分解区-\n\n");
    vector<pair<string, int>> itemList = player.getItemList({"equipment"}, false);
    for (int i = 0; i < itemList.size(); i++) {
        printf("%d.%s ", i + 1, itemList[i].first.c_str());
        int id = itemList[i].second;
        string type = init_item[id].type;
        if (start_with(type, "equipment")) {
            printf("(分解后获得%s×%d)", init_item[102].name.c_str(), init_item[id].quality - 1);
        }
        printf("\n\n");
    }

    printf("请输入要分解物品的序号: \n");
    int choice = getChoice(1, itemList.size());
    if (choice == -1) goto decompose;
    if (choice == -2) return;
    int itemId = itemList[choice - 1].second;

    printf("请输入分解数量(默认为全部分解): \n");
    int count = getChoice(1, player.items[itemId]->count);
    if (count == -1) count = player.items[itemId]->count;
    if (count == -2) goto decompose;

    string type = init_item[itemId].type;
    if (start_with(type, "equipment")) {
        int get = (init_item[itemId].quality - 1) * count;
        player.items[itemId]->count -= count;
        player.items[102]->count += get;
        printf("分解成功！你获得: \n");
        printf("%s×%d\n", init_item[102].name.c_str(), get);
    }
    system("pause");
    goto decompose;
}

void workArea(Player& player) {
    workArea:
    system("cls");
    printf("-功能区-\n\n");
    printf("1.垃圾桶\n");
    printf("2.分解区\n");
    cout << endl;
    printf("请输入序号: \n");
    int choice = getChoice(1, 2);
    if (choice == -1) goto workArea;
    if (choice == -2) return;
    switch (choice) {
        case 1: {
            bin(player);
            break;
        }
        case 2: {
            decompose(player);
            break;
        }
        default:
            break;
    }
    goto workArea;
}

#endif //FOREVERLAND_WORKAREA_H
