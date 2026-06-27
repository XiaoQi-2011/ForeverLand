#ifndef WORLDDATA_H
#define WORLDDATA_H

#define WORLDDATA_NUM 4

#include <string>

struct WorldData
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
    } datas[WORLDDATA_NUM];

    WorldData() = default;

    data* operator[](int index)
    {
        return &datas[index];
    }

    void init(const data data[], bool initValue = false)
    {
        for (int i = 0; i < WORLDDATA_NUM; i++)
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

inline const WorldData::data (&getInitWorldData())[4]
{
    static const WorldData::data init_worldData[]{
        WorldData::data("无尽之塔层数", 1, "fuben_infiniteTower"),
        WorldData::data("游玩时长/s", 420, "time_second"),
        WorldData::data("游玩天数", 0, "time_day"),
        WorldData::data("游戏难度", 0, "difficulty"),
    };
    return init_worldData;
}

#endif // WORLDDATA_H
