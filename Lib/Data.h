#ifndef DATA_H
#define DATA_H

#define DATA_NUM 27
#define STRDATA_NUM 3

#include <string>
#include <iomanip>
#include <utility>

#include "StrData.h"

static int dayPeriod = 1;

struct Data
{
    struct data
    {
        std::string name;
        std::string type;
        int value = 0;
        data() = default;

        data(std::string name, int value, std::string type)
        {
            this->name = std::move(name);
            this->value = value;
            this->type = std::move(type);
        }
    } datas[DATA_NUM];

    Data() = default;

    data* operator[](int index)
    {
        return &datas[index];
    }

    void init(const data data[], bool initValue = false)
    {
        for (int i = 0; i < DATA_NUM; i++)
        {
            if (initValue)
            {
                datas[i].value = data[i].value;
            }
            datas[i].name = data[i].name;
            datas[i].type = data[i].type;
        }
    }
};

//use: \033color - 30 light: +8
const int colors[] = {
    8, 4, 2, 6, 1, 5, 3, 7
};

inline Data::data (&getInitData())[DATA_NUM]
{
    static Data::data initData[] =
    {
        Data::data("等级", 0, "basic"),
        Data::data("经验值", 0, "basic"),
        Data::data("金币", 100, "basic"),
        Data::data("钻石", 10, "basic"),
        Data::data("攻击力", 0, "shuxing"),
        Data::data("防御力", 0, "shuxing"),
        Data::data("生命值", 20, "shuxing"),
        Data::data("生命上限", 20, "shuxing"),
        Data::data("伤害加成%", 0, "shuxing"),
        Data::data("伤害减免%", 0, "shuxing"),
        Data::data("闪避概率%", 0, "shuxing"),
        Data::data("吸血概率%", 0, "shuxing"),
        Data::data("吸血比率%", 0, "shuxing"),
        Data::data("暴击比率%", 0, "shuxing"),
        Data::data("攻击速度", 10, "shuxing"),
        Data::data("挖掘速度", 0, "shuxing"),
        Data::data("挖掘等级", 0, "shuxing"),
        Data::data("头盔装备", -1, "slot"),
        Data::data("护甲装备", -1, "slot"),
        Data::data("武器装备", -1, "slot"),
        Data::data("副手装备", -1, "slot"),
        Data::data("镐子装备", -1, "slot"),
        Data::data("饰品装备1", -1, "slot"),
        Data::data("饰品装备2", -1, "slot"),
        Data::data("饰品装备3", -1, "slot"),
        Data::data("饰品装备4", -1, "slot"),
        Data::data("神级", 0, "basic")
    };

    return initData;
}

std::pair<int, int> getRealDamage(Data data);
std::string getInitString(const std::string& password);

#endif //DATA_H
