#ifndef FOREVERLAND_SECRETREALM_H
#define FOREVERLAND_SECRETREALM_H

#include <iostream>
#include <vector>
#include <map>

#include "../Lib/Library.h"
#include "../Lib/Item.h"
#include "../Lib/Entity.h"

const int srNumber = 1;
inline char secretRealmKey = 'e';

inline std::string secretRealmNames [srNumber]{
    "青蘅灵境"
};
inline std::string secretRealmDesc [srNumber]{
    "漫山蘅草古木，林间流淌灵雾，盛产凡阶仙草"
};

inline Lottery<int> secretRealms[srNumber] {
    Lottery<int>({{107, 10}, {108, 10}, {109, 10}, {110, 10}, {-1, 10}}),
};

inline std::map<int, Entity> srEntity;
inline void initSecretRealm()
{
    srEntity[1] = Entity(createMonster("青蘅兽", 5, false));
}

void SecretRealmMenu(Player& player);

#endif //FOREVERLAND_SECRETREALM_H
