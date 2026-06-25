#ifndef FOREVERLAND_FUBEN_H
#define FOREVERLAND_FUBEN_H

#include <iostream>

#include "../Lib/Library.h"

#include "Fuben/Adventure.h"
#include "Fuben/InfiniteTower.h"
#include "Fuben/InfiniteTrials.h"
#include "Fuben/WorldBoss.h"
#include "Fuben/TrainingBot.h"

inline void fuben(Player& player)
{
fuben:
    system("cls");
    std::cout << "-副本-" << std::endl << std::endl;
    std::cout << "1.冒险世界" << std::endl;
    std::cout << "2.无尽之塔" << std::endl;
    std::cout << "3.无尽试炼 " << std::endl;
    std::cout << "4.世界Boss" << std::endl;
    std::cout << "5.训练假人" << std::endl;
    int choice = getChoice(1, 5);
    if (choice == -1) goto fuben;
    if (choice == -2) return;
    switch (choice)
    {
    case 1:
        {
            adventure(player);
            goto fuben;
        }
    case 2:
        {
            infiniteTower(player);
            goto fuben;
        }
    case 3:
        {
            infiniteTrials(player);
            goto fuben;
        }
    case 4:
        {
            worldBoss(player);
            goto fuben;
        }
    case 5:
        {
            trainingBot(player);
            goto fuben;
        }
    default:
        {
            std::cout << "此功能暂未开发" << std::endl;
            system("pause");
            goto fuben;
        }
    }
}
#endif //FOREVERLAND_FUBEN_H
