#ifndef STRDATA_H
#define STRDATA_H

#define DATA_NUM 27
#define STRDATA_NUM 3

#include <string>

struct StrData
{
    struct data
    {
        std::string name, type;
        std::string value;
        data() = default;

        data(std::string name, std::string value, std::string type)
        {
            this->name = std::move(name);
            this->value = std::move(value);
            this->type = std::move(type);
        }
    } datas[STRDATA_NUM];

    StrData() = default;

    data* operator[](int index)
    {
        return &datas[index];
    }

    void init(const data data[], bool initValue = false)
    {
        for (int i = 0; i < STRDATA_NUM; i++)
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

inline const StrData::data (&getInitStrData())[STRDATA_NUM]
{
    static const StrData::data init_strData[]{
        StrData::data("杂货铺商品", "empty", "trade_zahuo"),
        StrData::data("神秘人商品", "empty", "trade_shenmi"),
        StrData::data("按键配置", "e$r$1$2$3$4$5$6$", "key")
    };
    return init_strData;
}

#endif // STRDATA_H
