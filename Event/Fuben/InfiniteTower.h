#ifndef FOREVERLAND_INFINITETOWER_H
#define FOREVERLAND_INFINITETOWER_H

#include <iostream>
#include <vector>
using namespace std;
void infiniteTower(Player& player) {
    infiniteTower:
    system("cls");
    printf("-无尽之塔-\n\n");

    int level = player.getWorldData(0);
    printf("当前层数：%d层\n", level);

    Entity entity = createMonster("试炼守卫", level, true);
    printf("当前怪物：%s\n", entity.name.c_str());
    pair<int, int> damage = getRealDamage(entity.data);
    printf("攻击力：%d~%d\n", damage.first, damage.second);
    printf("防御力：%d\n", entity.getData(5));
    printf("生命值：%d\n", entity.getData(6));
    printf("\n是否挑战? (1开始 2返回)\n");

    int choice = getChoice(1, 2);
    if (choice == -1) goto infiniteTower;
    if (choice == 2 || choice == -2) return;
    if (choice == 1) {
        Player fakePlayer = player;
        createFightArea(fakePlayer, "-无尽之塔-");
        bool wins = fight(fakePlayer, entity, player);
        if (wins) {
            player.worldData[0]->value++;
        }
        goto infiniteTower;
    }
    goto infiniteTower;
}

#endif //FOREVERLAND_INFINITETOWER_H
