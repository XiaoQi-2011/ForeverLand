#ifndef FOREVERLAND_INFINITETRIALS_H
#define FOREVERLAND_INFINITETRIALS_H

#include <iostream>
#include <vector>
using namespace std;

void infiniteTrials(Player& player) {
    system("cls");
    createFightArea(player, "-无尽试炼-");
    int level = 0;
    Player fakePlayer = player;
    while (++level) {
        printf("\n\033[1;32m>你到达了第%d层\033[0m\n", level);
        printf("\033[1;34m你当前血量:\033[1;31m%d/%d ", fakePlayer.getData(6), fakePlayer.getData(7));
        int healthP = fakePlayer.getData(6) * 100 / fakePlayer.getData(7);
        cout << healthColors[healthP / 20] << healthP << "%\033[0m\n" << endl;

        Entity entity = createMonster("试炼守卫", level, true);
        bool isContinue = level != 1;
        bool wins = fight(fakePlayer, entity, player, isContinue);
        if (!wins) break;
    }
    level --;
    printf("\n\033[1;32m-----试炼结束-----\033[0m\n");
    int jb = pow(level/10, 2) * 20 + (level % 10) * 5;
    int zs = pow(level/10, 2) * 1.5 + (level % 10) / 2;
    printf("\033[1;32m[结算]\033[0m +%d金币 +%d钻石\n", jb, zs);
    player.data[2]->value += jb;
    player.data[3]->value += zs;
    system("pause");
}

#endif //FOREVERLAND_INFINITETRIALS_H
