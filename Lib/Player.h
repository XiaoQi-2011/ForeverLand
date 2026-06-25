#ifndef PLAYER_H
#define PLAYER_H

#include <filesystem>
#include <fstream>

#include "Base64.h"
#include "Data.h"
#include "WorldData.h"
#include "Item.h"

struct Player
{
    Data data;
    WorldData worldData;
    StrData strData;
    Item items;
    std::string path;
    std::string name, password;
    long long createTime = 0;

    Player() = default;

    Player(std::string path)
    {
        this->path = std::move(path);
    }

    enum fileType
    {
        SUCCESS, NO_EXISTS, DATA_ERROR
    };

    fileType readFile()
    {
        if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path))
        {
            return NO_EXISTS;
        }
        std::ifstream fin(path);
        std::string s_time, s_password, s_data, s_worldData, s_strData, s_items, verCode;
        fin >> s_time
            >> s_password
            >> s_data
            >> s_worldData
            >> s_strData
            >> s_items
            >> verCode;
        createTime = decodeTime(s_time);
        Base64Key = createTime / 7;
        password = decode(s_password);
        std::string realVerCode = getVerificationCode(s_time + s_password + s_data + s_worldData + s_strData + s_items);
        if (realVerCode != verCode)
        {
            return DATA_ERROR;
        }

        std::stringstream vdata(decode(s_data));
        data.init(getInitData());
        int index = 0;
        for (auto& mdata : data.datas)
        {
            vdata >> mdata.value;
            index++;
        }

        std::stringstream vdata2(decode(s_worldData));
        worldData.init(getInitWorldData());
        index = 0;
        for (auto& mdata2 : worldData.datas)
        {
            vdata2 >> mdata2.value;
            index++;
        }

        std::stringstream vdata3(decode(s_strData));
        strData.init(getInitStrData());
        index = 0;
        for (auto& mdata3 : strData.datas)
        {
            vdata3 >> mdata3.value;
            index++;
        }

        std::stringstream vitem(decode(s_items));
        items.init(init_item);
        index = 0;
        for (auto& mitem : items.items)
        {
            vitem >> mitem.count;
            index++;
        }
        fin.close();
        return SUCCESS;
    }

    bool writeFile()
    {
        std::ofstream fout(path);
        fout << encodeTime(createTime) << std::endl;
        fout << encode(password) << std::endl;

        std::stringstream vdata;
        for (auto& data : data.datas)
        {
            vdata << data.value << " ";
        }

        std::stringstream vdata2;
        for (auto& data2 : worldData.datas)
        {
            vdata2 << data2.value << " ";
        }

        std::stringstream vdata3;
        for (auto& data3 : strData.datas)
        {
            vdata3 << data3.value << " ";
        }

        std::stringstream vitem;
        for (auto& item : items.items)
        {
            vitem << item.count << " ";
        }

        std::string code = encode(vdata.str());
        std::string code2 = encode(vdata2.str());
        std::string code3 = encode(vdata3.str());
        std::string code4 = encode(vitem.str());
        std::string verCode = getVerificationCode(encodeTime(createTime) + encode(password) + code + code2 + code3 + code4);
        fout << code << std::endl
            << code2 << std::endl
            << code3 << std::endl
            << code4 << std::endl
            << verCode << std::endl;
        fout.close();
        return true;
    }

    std::vector<std::pair<std::string, int>> getItemList(std::vector<std::string> types, bool introduce)
    {
        return items.getItemList(std::move(types), introduce);
    }

    int getData(const int index)
    {
        return data[index]->value;
    }

    int getWorldData(const int index)
    {
        return worldData[index]->value;
    }

    std::string getStrData(const int index)
    {
        return strData[index]->value;
    }

    int getItem(const int index)
    {
        return items[index]->count;
    }
};
#endif // PLAYER_H
