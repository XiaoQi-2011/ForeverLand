#ifndef FOREVERLAND_INVENTORYEVENT_H
#define FOREVERLAND_INVENTORYEVENT_H

#include <iostream>
#include <vector>

#include "../library.h"
#include "../ConstDatas.h"
#include "Trade.h"
#include "Fuben/WorldBoss.h"
#include "Mine.h"

using namespace std;

const string ignore_types[] {
    "slot", "fuben"
};
inline void showPlayerData(Player& player) {
    system("cls");
    printf("-个人信息-\n");
    printf("名称: %s\n", player.name.c_str());
    printf("创建于: %s\n", getFormatSystemTime(player.createTime).c_str());
    printf("游玩天数: %d\n", player.getWorldData(2));
    for (int i = 0; i < DATA_NUM; i++) {
        bool flag = false;
        for (const string& type : ignore_types) {
            if (start_with(init_data[i].type, type)) {
                flag = true;
                break;
            }
        }
        if (flag) continue;
        if (i == 7) {
            printf("/%d", player.getData(i));
            continue;
        }
        printf("\n%s: %d", init_data[i].name.c_str(), player.getData(i));
        if (i == 1) {
            int exp_max = (player.getData(0)/10+1)*(player.getData(0)/10+1)*100+10*player.getData(0);
            printf("/%d", exp_max);
        }
        if (i == 3) {
            printf("\n");
        }
        if (i == 4) {
            pair<int, int> damage = getRealDamage(player.data);
            printf(" (最终伤害: %d~%d)", damage.first, damage.second);
        }
    }
    printf("\n\n");
    system("pause");
}
const string onlyOnceTypes[] {
    "equipment", "consumables_more"
};
inline void showPlayerItems(Player& player) {
    showPlayerItems:
    system("cls");
    printf("-物品栏-\n\n");
    printf("[装备]\n");
    for (int i = 0; i < DATA_NUM; i++) {
        if (init_data[i].type == "slot") {
            string item_name;
            if (player.getData(i) != -1 && player.getData(i) < ITEM_NUM) {
                item_name = init_item[player.getData(i)].name;
            }
            printf("a%d.%s: %s\n", i-16, init_data[i].name.c_str(), item_name.c_str());
        }
    }
    printf("\n[物品]\n");
    vector<pair<string, int>> items = player.getItemList( {"all"}, true);
    int num = items.size();
    for (int i = 0; i < num; i++) {
        printf("%d.%s\n\n", i+1, items[i].first.c_str());
    }

    cout << "请输入要使用的物品序号:" << endl;
    string input;
    int choice = getChoice(1, num, input, {"a%d%"});
    if (choice == -1) goto showPlayerItems;
    if (choice == -2) return;

    // 卸下装备
    if (choice == -3) {
        int slot_id = input[1] - '1' + 17;
        if (slot_id < 17 || slot_id > 25) goto showPlayerItems;
        if (player.getData(slot_id) != -1) {
            takeOffEquipment(player, slot_id);
            cout << "已卸下装备" << endl;
            system("pause");
        } else {
            cout << "该槽位为空" << endl;
            system("pause");
        }
        goto showPlayerItems;
    }

    // 使用物品
    bool success = false;
    int item_id = items[choice-1].second;
    string item_type = init_item[item_id].type;

    int count = 1;
    bool useFlag = true;
    for (const string& type : onlyOnceTypes) {
        if (start_with(item_type, type)) {
            useFlag = false;
            break;
        }
    }
    if (useFlag) {
        cout << "请输入使用数量(默认为1，all为全部):" << endl;
        string input2;
        count = getChoice(1, player.items[item_id]->count, input2, {"all"});
        if (count == -1) count = 1;
        if (count == -2) goto showPlayerItems;
        if (count == -3) count = player.items[item_id]->count;
    }

    for (int cnt = 1; cnt <= count; cnt++) {
        Sleep(10);
        // 灵石
        if (item_type == "lingshi") {
            int level = item_id - 42;
            int exp = level * 100;
            player.data[1]->value += exp;
            player.items[item_id]->count--;
            printf("使用成功！+\033[1;32m%d\033[0m经验\n", exp);
            success = true;
        }

        // 装备
        if (start_with(item_type, "equipment")) {
            int slot_id = 0;
            if (item_type == "equipment_helmet") {
                slot_id = 17;
            }
            if (item_type == "equipment_armor") {
                slot_id = 18;
            }
            if (item_type == "equipment_sword") {
                slot_id = 19;
            }
            if (item_type == "equipment_offhand") {
                slot_id = 20;
            }
            if (item_type == "equipment_pickaxe") {
                slot_id = 21;
            }
            if (item_type == "equipment_accessory") {
                bool flag = false, isOn = false;
                for (int i = 22; i <= 25; i++) {
                    if (player.getData(i) == item_id) {
                        isOn = true;
                    }
                    if (player.getData(i) == -1 && !flag) {
                        slot_id = i;
                        flag = true;
                    }
                }
                if (isOn) {
                    cout << "每种饰品只能装备1个！" << endl;
                    system("pause");
                    goto showPlayerItems;
                }
                if (!flag) {
                    cout << "饰品槽位已满" << endl;
                    system("pause");
                    goto showPlayerItems;
                }
            }

            putOnEquipment(player, item_id, slot_id);
            cout << "已装备物品" << endl;
            success = true;
        }

        // 宝箱
        if (item_type == "chest") {
            int id = Random(0, ITEM_NUM);
            int quality = item_id - 53 + 2;
            while (init_item[id].quality != quality) {
                id = Random(0, ITEM_NUM);
            }
            player.items[id]->count++;
            player.items[item_id]->count--;
            cout << "使用成功！你获得了：" << endl;
            cout << init_item[id].name << " ×1" << endl;
            success = true;
        }

        // 福袋
        if (start_with(item_type, "fudai")) {
            int index = item_id - 92 + 1;
            if (item_type == "fudai_jb") {
                int jb = 0;
                if (index == 1) jb = Random(5, 15);
                if (index == 2) jb = Random(40, 60);
                if (index == 3) jb = Random(90, 110);
                player.data[2]->value += jb;
                printf("使用成功！你获得了 %d 金币\n", jb);
            }
            if (item_type == "fudai_zs") {
                int zs = 0;
                if (index == 4) zs = Random(1, 5);
                if (index == 5) zs = Random(5, 15);
                if (index == 6) zs = Random(40, 60);
                player.data[3]->value += zs;
                printf("使用成功！你获得了 %d 钻石\n", zs);
            }
            player.items[item_id]->count--;
            success = true;
        }

        // 刷新券
        if (start_with(item_type, "shuaxin")) {
            if(item_id == 98) {
                reflashZahuo(player);
            }
            if(item_id == 99) {
                reflashShenmi(player);
            }
            if (item_id == 100) {
                printf("请输入世界Boss序号: \n");
                int choice = getChoice(1, bossCount);
                if (choice == -1 || choice == -2) goto showPlayerItems;
                worldBosses[choice-1].isFlashed = true;
            }
            printf("使用成功！\n");
            player.items[item_id]->count--;
            success = true;
        }

        // 消耗品
        if (start_with(item_type, "consumables")) {
            // 补充体力
            if (item_id == 101) {
                if (stamina == 100) {
                    printf("体力已满！\n");
                    system("pause");
                    goto showPlayerItems;
                }
                stamina = 100;
                printf("使用成功！体力已补充至100\n");
                player.items[item_id]->count--;
                success = true;
            }
            // 化神石
            if (item_id == 103) {
                int level = player.getData(0);
                if (level < 99 || (level + 1) % 10 != 0) {
                    printf("你未到达神级瓶颈! \n");
                    system("pause");
                    goto showPlayerItems;
                }
                int ping = (level + 1 - 100) / 10 + 1;
                if (player.getItem(item_id) < ping) {
                    printf("化神石数量不足(需要%d个)! \n", ping);
                    system("pause");
                    goto showPlayerItems;
                }
                printf("使用成功！\n");
                player.items[item_id]->count -= ping;
                player.data[26]->value ++;
                player.data[1]->value += 100;
                success = true;
            }
        }
    }

    if (!success) cout << "该物品无法使用或使用失败" << endl;
    system("pause");
    goto showPlayerItems;
}

#endif //FOREVERLAND_INVENTORYEVENT_H
