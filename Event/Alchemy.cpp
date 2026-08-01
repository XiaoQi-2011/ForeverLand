#include <iostream>

#include "Alchemy.h"

void initElixirItem() {
    for (const AMaterial& am : alchemyMaterials) {
        int id = am.itemID;
        std::vector<std::pair<int, int>> values = am.values;
        int jb_value = 0, zs_value = 0;
        for (const std::pair<int, int>& p : values) {
            jb_value += init_item[p.first].JB_value * p.second;
            zs_value += init_item[p.first].ZS_value * p.second;
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
                if (AvalueLoc[i] == 7 || AvalueLoc[i] == 28 || AvalueLoc[i] == 30) {
                    player.data[AvalueLoc[i] - 1]->value += values[i];
                }
            }
            break;
        }
    }
    return true;
}

void Alchemy(Player& player) {
    Alchemy:
    system("cls");
    printf("--炼丹区--\n");
    printf("炼丹等级：%d\n\n", player.getData(32));

    for (int i = 0; i < alchemy_num; i++) {
        printf("%d.%s炼丹区\033[0m\n", i + 1, alchemyNames[i].c_str());
        printf(">需求:Lv.%d+ 炼丹等级%d+\n", playerLevels[i], alchemyLevels[i]);
        printf(">可炼制%s丹药\033[0m\n", alchemyNames[i].c_str());
        printf("\n");
    }
    printf("\n请输入序号：\n");

    int choice = getChoice(1, alchemy_num);
    if (choice == -1) goto Alchemy;
    if (choice == -2) return;
    if (player.getData(32) < alchemyLevels[choice - 1] || player.getData(0) < playerLevels[choice - 1]) {
        printf("未满足等级条件！\n");
        system("pause");
        goto Alchemy;
    }

    choice ++;
    Alchemy2:
    system("cls");
    std::vector<int> itemIDs;
    std::vector<bool> enough;
    for (int i = 0; i < elixir_num; i++) {
        const AMaterial& am = alchemyMaterials[i];
        if (player.items[am.itemID]->quality == choice) {
            itemIDs.push_back(i);
            bool m_enough = true;
            printf("%zu.炼制 %s\033[0m\n", itemIDs.size(), player.items[am.itemID]->name.c_str());
            printf("%s\n", player.items[am.itemID]->introduce.c_str());
            printf("\033[0;32m>所需材料：\033[0m\n");
            for (const std::pair<int, int>& p : am.values) {
                std::string color = player.getItem(p.first) >= p.second
                                   ? ANumColors[0]
                                   : ANumColors[1];
                if (player.getItem(p.first) < p.second) {
                    m_enough = false;
                }
                printf("%s×%d (你有%s%d\033[0m个)\n", player.items[p.first]->name.c_str(), p.second, color.c_str(), player.getItem(p.first));
            }
            float successRate = (7 - choice) * 10 + (player.getData(32) - alchemyLevels[choice - 2]) / 10;
            successRate = std::min(successRate, 100.0f);
            successRate = std::max(successRate, 0.0f);
            printf("\033[1;33m成功率：%.1f%%\033[0m\n", successRate);
            printf("\n");
            enough.push_back(m_enough);
        }
    }
    printf("\n请输入序号：\n");

    int choice2 = getChoice(1, itemIDs.size());
    if (choice2 == -1) goto Alchemy2;
    if (choice2 == -2) goto Alchemy;

    if (!enough[choice2 - 1]) {
        printf("材料不足！\n");
        system("pause");
        goto Alchemy2;
    }
    auto &am = alchemyMaterials[itemIDs[choice2 - 1]];
    for (const std::pair<int, int>& p : am.values) {
        player.items[p.first]->count -= p.second;
    }
    int successRate = (7 - choice) * 100 + (player.getData(32) - alchemyLevels[choice - 2]);
    Lottery<int> lottery({{1, successRate}}, 1000);
    // 动画
    SetConsoleCursorVisible(false);
    printf("%s炼制中...\033[0m\n", getColor({"#FEF686"}).c_str());
    for (int i = 1; i <= 10; i++) {
        printf("进度：");
        for (int j = 1; j <= i; j++) {
            printf("\033[1;32m▮");
        }
        for (int j = i + 1; j <= 10; j++) {
            printf("\033[0m▮");
        }
        printf("\033[0m\r");
        Sleep(100);
    }
    printf("\n");
    SetConsoleCursorVisible(true);

    if (lottery.lottery() == 1) {
        printf("炼制成功！\n");
        printf("获得：%s×1\n", player.items[am.itemID]->name.c_str());
        printf("\033[1;33m炼丹等级+%d\033[0m\n", choice - 1);
        player.items[am.itemID]->count++;
        player.data[32]->value += choice - 1;
    } else {
        printf("炼制失败！\n");
        printf("获得：%s×1\n", player.items[127]->name.c_str());
        player.items[127]->count++;
    }
    system("pause");
    goto Alchemy2;
}