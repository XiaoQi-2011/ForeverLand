#include <iostream>

#include "Alchemy.h"

void initElixirItem() {
    for (const AMaterial& am : alchemyMaterials) {
        int id = am.itemID;
        std::vector<std::pair<int, int>> values = am.values;
        int jb_value = 0, zs_value = 0;
        for (const std::pair<int, int>& p : values) {
            jb_value = init_item[id].JB_value * p.second;
            zs_value = init_item[id].ZS_value * p.second;
        }
        init_item[id].JB_value = jb_value;
        init_item[id].ZS_value = zs_value;
    }
}

bool useElixir(Player& player, int itemID) {
    if (player.getItem(itemID) <= 0) return false;
    player.items[itemID]->count--;
    for (const AData& ad : alchemyData) {
        if (ad.itemID == itemID) {
            std::vector<int> values = ad.values;
            for (int i = 0; i < values.size(); i++) {
                player.data[AvalueLoc[i]]->value += values[i];
            }
            break;
        }
    }
    return true;
}

void Alchemy(Player& player) {
    Alchemy:
    system("cls");
    printf("--炼丹区--\n\n");

    for (int i = 0; i < alchemy_num; i++) {
        printf("%d.%s炼丹区\033[0m\n", i + 1, alchemyNames[i].c_str());
        printf(">需求：Lv.%d+ 炼丹等级%d+\n", playerLevels[i], alchemyLevels[i]);
        printf(">可炼制%s丹药\033[0m\n", alchemyNames[i].c_str());
        printf("\n");
    }
    printf("\n请输入序号：\n");

    int choice = getChoice(1, alchemy_num);
    if (choice == -1) goto Alchemy;
    if (choice == -2) return;

    choice ++;
    std::vector<int> itemIDs;
    for (const AMaterial& am : alchemyMaterials) {
        if (player.items[am.itemID]->quality == choice) {
            itemIDs.push_back(am.itemID);
            printf("%zu.炼制 %s\n", itemIDs.size(), player.items[am.itemID]->name.c_str());
            printf("\033[0;32m>所需材料：\033[0m\n");
            for (const std::pair<int, int>& p : am.values) {
                std::string color = player.getItem(p.first) >= p.second
                                   ? ANumColors[0]
                                   : ANumColors[1];
                printf("%s (你有%s%d\033[0m个)\n", player.items[p.first]->name.c_str(), color.c_str(), player.getItem(p.first));
            }
            float successRate = (7 - choice) * 10 + (player.getData(32) - alchemyLevels[choice - 2]) / 10;
            printf("\033[1;33m成功率：%.1f%%\n", successRate);
            printf("\n");
        }
    }
    printf("\n请输入序号：\n");

    choice = getChoice(1, itemIDs.size());
    if (choice == -1) goto Alchemy;
    if (choice == -2) return;
}