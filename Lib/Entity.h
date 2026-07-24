#ifndef ENTITY_H
#define ENTITY_H

#include "Data.h"

struct Entity
{
    std::string name;
    std::string introduce;
    Data data;
    Item capture;

    Entity() = default;

    Entity(std::string name, std::string introduce, Data data, Item capture)
    {
        this->name = std::move(name);
        this->introduce = std::move(introduce);
        this->data = std::move(data);
        this->capture = std::move(capture);
    }

    Entity(std::string name, Data data, Item capture)
    {
        this->name = std::move(name);
        this->data = std::move(data);
        this->capture = std::move(capture);
    }

    int getData(const int index)
    {
        return data[index]->value;
    }

    int getCapture(const int index)
    {
        return capture[index]->count;
    }
};

inline Entity createMonster(const std::string& name, int level, bool showLevel, float override = 1)
{
    Entity monster;
    // 特殊
    override += difficulty * 0.2f;
    if (dayPeriod == 3) {
        override += 0.1;
    }
    // 数据
    if (showLevel)
    {
        monster.name = name + "[lv." + std::to_string(level) + "]";
    }
    else
    {
        monster.name = name;
    }
    monster.data.init(getInitData());
    monster.capture.init(init_item);

    monster.data.datas[1].value = level * 10 * override;
    monster.data.datas[2].value = level / 2 * override;
    monster.data.datas[3].value = level / 20 * override;

    monster.data.datas[4].value = level * 3 * override;
    monster.data.datas[5].value = level * override;
    monster.data.datas[6].value = level * 10 * override;
    monster.data.datas[7].value = level * 10 * override;
    monster.data.datas[8].value = level * 0.4 * override;
    monster.data.datas[9].value = level * 0.2 * override;
    monster.data.datas[10].value = level * 0.2 * override;
    monster.data.datas[11].value = level * 0.5 * override;
    monster.data.datas[12].value = level * 0.3 * override;
    monster.data.datas[13].value = level * 0.3 * override;
    monster.data.datas[14].value = 10 + (level / 10) * 3;
    return monster;
}

#endif // ENTITY_H
