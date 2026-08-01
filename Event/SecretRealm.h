#ifndef FOREVERLAND_SECRETREALM_H
#define FOREVERLAND_SECRETREALM_H

#include <iostream>
#include <vector>
#include <map>

#include "../Lib/Library.h"
#include "../Lib/Item.h"
#include "../Lib/Entity.h"

const int srNumber = 5;
inline bool sr_canGo = true;

const int srMinLevel [srNumber]{
    0, 20, 40, 60, 80
};

inline std::string secretRealmColor [srNumber]{
    "#15E523", "#15E595", "#6815E5", "#FF75B8", "#783DA9"
};
const std::string secretRealmNames [srNumber]{
    "青蘅灵境", "青鸾峰上", "玄元古墟", "涂山", "混沌神域"
};
const std::string secretRealmDesc [srNumber]{
    "漫山蘅草古木，林间流淌灵雾，盛产凡阶仙草",
    "常年云海笼罩，生长大量灵草，多灵禽，曾有大能于峰顶修炼剑道，因此峰顶剑气环绕千年未散",
    "上古仙尊陨落之地，布满破碎道纹，其残留的庞大灵力滋养了很多仙草和凶兽",
    "依山环湖而立，从远处就可看见一棵百米巨树屹立于中央，\n立于树下，便可见漫天粉色花瓣飘落，恍若人间仙境，\n树下一碑刻有其名，为：苦情巨树",
    "空间扭曲，残留神念于其中，生长顶级仙草"

};

const Lottery<int> secretRealms[srNumber] {
    Lottery<int>({{107, 10}, {108, 10}, {109, 10}, {110, 10}, {-1, 10}}),
    Lottery<int>({{111, 8}, {112, 8}, {113, 8}, {114, 8}, {-2, 6}, {-3, 4}}),
    Lottery<int>({{115, 6}, {116, 6}, {117, 6}, {118, 6}, {-4, 6}, {-5, 4}}),
    Lottery<int>({{119, 4}, {120, 4}, {121, 4}, {122, 4}, {-6, 8}}),
    Lottery<int>({{123, 2}, {124, 2}, {125, 2}, {126, 2}, {-7, 8}})
};

inline std::map<int, Entity> srEntity;
inline void initSecretRealm()
{
    for (auto & srColor : secretRealmColor) {
        srColor = getColor({srColor});
    }
    srEntity[1] = Entity(createMonster("[凡阶]青蘅兽", 5, false));
    srEntity[2] = Entity(createMonster("[灵阶]青岚剑灵", 20, false));
    srEntity[3] = Entity(createMonster("[灵阶]青鸾", 30, false));
    srEntity[4] = Entity(createMonster("[玄阶]苍溟玄兽", 40, false));
    srEntity[5] = Entity(createMonster("[玄阶]仙尊残魂", 50, false));
    srEntity[6] = Entity(createMonster("狐妖守卫", 60, false));
    srEntity[7] = Entity(createMonster("混沌神念", 90, false));
}

void sr_Loop();

void SecretRealm(Player& player, int choice);

void SecretRealmMenu(Player& player);

#endif //FOREVERLAND_SECRETREALM_H
