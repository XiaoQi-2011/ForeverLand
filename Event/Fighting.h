#ifndef FOREVERLAND_FIGHTING_H
#define FOREVERLAND_FIGHTING_H

#include <iostream>

#include "../Lib/Library.h"
#include "../Lib/Entity.h"

#define meHealth fPlayer->data[6]->value
#define enemyHealth fEntity->data[6]->value

inline Player* fPlayer;
inline Entity* fEntity;
inline Player* realPlayer;

inline int win = 0;

inline long long times = 0;

inline int healthCD = -1, health = 0;
inline int strengthCD = -1, strength = 0;
inline int resistanceCD = -1, resistance = 0;
inline int attackCD = -1;

inline char attackKey = 'e';
inline char potionKey = 'r';
inline char potionKeys[]{
    '1', '2', '3', '4', '5', '6'
};

constexpr std::string healthColors[]{
    "\033[0;31m",
    "\033[0;31m",
    "\033[0;33m",
    "\033[1;33m",
    "\033[1;32m",
    "\033[1;32m",
};

// 函数声明
void initKeys(Player& player);
int getRealDamage(Data me, Data enemy);
int judgmentWin();
void MainLoop();
void entityAttack();
void specialEvent();
bool fight(Player& player, Entity& entity, Player& real_player, bool isContinue = false);
void createFightArea(Player& player, const std::string& str);

#endif //FOREVERLAND_FIGHTING_H
