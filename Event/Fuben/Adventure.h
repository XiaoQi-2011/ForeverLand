#ifndef FOREVERLAND_ADVENTURE_H
#define FOREVERLAND_ADVENTURE_H

#include <vector>

#include "../../Lib/Player.h"
#include "../../Lib/Entity.h"
#include "../../Lib/Library.h"

struct AdventureMst
{
    std::string name1, name2;
    std::string bossName;
    std::string world;
    int jie = 0;
    int bossItemPercent = 0;

    AdventureMst() = default;

    AdventureMst(std::string world, std::string name1, std::string name2, std::string bossName, int jie, int bossItemPercent)
    {
        this->world = std::move(world);
        this->name1 = std::move(name1);
        this->name2 = std::move(name2);
        this->bossName = std::move(bossName);
        this->jie = jie;
        this->bossItemPercent = bossItemPercent;
    }

    Entity createAMonster(bool boss) const
    {
        float override = boss ? 1.5 : 1;
        std::string name;
        int level, rnd = Random(1, 9);
        if (boss)
        {
            level = jie * 10;
            name = bossName;
        }
        else
        {
            level = (jie - 1) * 10 + rnd;
            name = rnd <= 5 ? name1 : name2;
        }
        Entity entity = createMonster(name, level, true, override);
        int count = boss ? Random(2, 4) : Random(1, 2);
        entity.capture[jie + 62]->count = count;
        if (boss && Random(1, 100) <= bossItemPercent)
        {
            entity.capture[jie + 72]->count = 1;
        }
        return entity;
    }
};

const std::vector<AdventureMst> adventureMsts{
    {"史莱姆森林", "绿色史莱姆", "蓝色史莱姆", "史莱姆之王", 1, 25},
    {"哥布林洞穴", "野生哥布林", "狂暴哥布林", "哥布林领主", 2, 25},
    {"金字塔", "木乃伊", "风化骷髅", "法老王图特摩斯", 3, 25},
    {"中世纪古堡", "白银骑士", "黄金骑士", "吸血鬼伯爵", 4, 25},
    {"天空之城", "石巨人", "天使石像", "堕落天使", 5, 25},
    {"亚特兰蒂斯", "巨型乌贼", "深海巨齿鲨", "远古巨鲸利维坦", 6, 25},
    {"尼伯龙根", "龙侍(三代种)", "龙侍(次代种)", "龙王", 7, 40},
    {"玄武国", "玄武侍卫", "暗影侍卫", "恶灵", 8, 40}
};

// 函数声明
void adventure(Player& player);


#endif //FOREVERLAND_ADVENTURE_H
