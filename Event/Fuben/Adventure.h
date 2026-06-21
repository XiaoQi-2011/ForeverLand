#ifndef FOREVERLAND_ADVENTURE_H
#define FOREVERLAND_ADVENTURE_H

#include <iostream>
#include <vector>
using namespace std;

struct AdventureMst {
    string name1, name2;
    string bossName;
    string world;
    int jie = 0;
    int bossItemPercent = 0;

    AdventureMst() = default;
    AdventureMst(string world, string name1, string name2, string bossName, int jie, int bossItemPercent) {
        this->world = std::move(world);
        this->name1 = std::move(name1);
        this->name2 = std::move(name2);
        this->bossName = std::move(bossName);
        this->jie = jie;
        this->bossItemPercent = bossItemPercent;
    }

    Entity createAMonster(bool boss) const {
        float override = boss ? 1.5 : 1;
        string name;
        int level, rnd = Random(1, 9);
        if (boss) {
            level = jie * 10;
            name = bossName;
        } else {
            level =(jie - 1) * 10 + rnd;
            name = rnd <= 5 ? name1 : name2;
        }
        Entity entity = createMonster(name, level, true, override);
        int count = boss ? Random(2, 4) : Random(1, 2);
        entity.capture[jie + 62]->count = count;
        if (boss && Random(1, 100) <= bossItemPercent) {
            entity.capture[jie + 72]->count = 1;
        }
        return entity;
    }
};
const vector<AdventureMst> adventureMsts{
        {"史莱姆森林", "绿色史莱姆", "蓝色史莱姆", "史莱姆之王", 1, 25},
        {"哥布林洞穴", "野生哥布林", "狂暴哥布林", "哥布林领主", 2, 25},
        {"金字塔", "木乃伊", "风化骷髅", "法老王图特摩斯", 3, 25},
        {"中世纪古堡", "白银骑士", "黄金骑士", "吸血鬼伯爵", 4, 25},
        {"天空之城", "石巨人", "天使石像", "堕落天使", 5, 25},
        {"亚特兰蒂斯", "巨型乌贼", "深海巨齿鲨", "远古巨鲸利维坦", 6, 25},
        {"尼伯龙根", "龙侍(三代种)", "龙侍(次代种)", "龙王", 7, 40},
        {"玄武国", "玄武侍卫", "暗影侍卫", "恶灵", 8, 40}
};

inline void adventure(Player& player) {
    adventure:
    system("cls");
    cout << "-冒险世界-" << endl << endl;
    for (int i = 0; i < adventureMsts.size(); i++) {
        if (player.getData(0) < i * 10) {
            printf("\033[1;30m-[下一个副本将在达到 Lv.%d 后解锁]-\033[0m\n\n", i * 10);
            break;
        }
        printf("%d.%s(Lv.%d+)\n", i + 1, adventureMsts[i].world.c_str(), i*10);
        printf("[小怪] %s Lv.%d~%d %s Lv.%d~%d\n", adventureMsts[i].name1.c_str(), i*10+1, i*10+5, adventureMsts[i].name2.c_str(), i*10+6, i*10+9);
        printf("[Boss] %s Lv.%d\n", adventureMsts[i].bossName.c_str(), (i+1)*10);
        printf("[掉落物] %s \n", init_item[i + 63].name.c_str());
        cout << endl;
    }
    cout << "请输入序号:" << endl;
    int choice = getChoice(1, 8);
    if (choice == -1) goto adventure;
    if (choice == -2) return;
    int n = 0;
    choice --;
    system("cls");
    createFightArea(player, "你来到了 " + adventureMsts[choice].world);
    //printf("你来到了 [%s]\n\n", adventureMsts[choice].world.c_str());
    Player fakePlayer = player;
    bool flag = false;
    while (true) {
        Entity entity;
        if (n == 10) {
            n = 0;
            entity = adventureMsts[choice].createAMonster(true);
            printf("\033[1;31m你遇到了Boss: \033[0m%s\n\n", entity.name.c_str());
        } else {
            entity = adventureMsts[choice].createAMonster(false);
            printf("你遇到了新的小怪: %s\n\n", entity.name.c_str());
        }
        bool wins = fight(fakePlayer, entity, player, flag);
        if (!flag) flag = true;
        if (!wins) goto adventure;
        n ++;
    }
}


#endif //FOREVERLAND_ADVENTURE_H
