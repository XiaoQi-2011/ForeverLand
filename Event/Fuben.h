#ifndef FOREVERLAND_FUBEN_H
#define FOREVERLAND_FUBEN_H

#include <iostream>
#include <thread>
#include <utility>
#include <vector>
#include <conio.h>

#include "../library.h"

#include "Fuben/Adventure.h"
#include "Fuben/InfiniteTower.h"
#include "Fuben/InfiniteTrials.h"
#include "Fuben/WorldBoss.h"
#include "Fuben/TrainingBot.h"

using namespace std;

inline void fuben(Player& player) {
    fuben:
    system("cls");
    cout << "-副本-" << endl << endl;
    cout << "1.冒险世界" << endl;
    cout << "2.无尽之塔" << endl;
    cout << "3.无尽试炼 " << endl;
    cout << "4.世界Boss" << endl;
    cout << "5.训练假人" << endl;
    int choice = getChoice(1, 5);
    if (choice == -1) goto fuben;
    if (choice == -2) return;
    switch (choice) {
        case 1: {
            adventure(player);
            goto fuben;
        }
        case 2: {
            infiniteTower(player);
            goto fuben;
        }
        case 3: {
            infiniteTrials(player);
            goto fuben;
        }
        case 4: {
            worldBoss(player);
            goto fuben;
        }
        case 5: {
            trainingBot(player);
            goto fuben;
        }
        default: {
            cout << "此功能暂未开发" << endl;
            system("pause");
            goto fuben;
        }
    }
}
#endif //FOREVERLAND_FUBEN_H
