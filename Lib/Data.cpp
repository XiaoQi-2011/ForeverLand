#include "Data.h"
#include "Base64.h"
#include "WorldData.h"
#include "Item.h"

std::pair<int, int> getRealDamage(Data data)
{
    int damage = data[4]->value * (100 + data[8]->value) / 100;
    int max_damage = damage * (100 + data[13]->value) / 100;
    return std::make_pair(damage, max_damage);
}

std::string getInitString(const std::string& password)
{
    long long createTime = time(nullptr);
    Base64Key = createTime / 7;
    std::string vtime = encodeTime(createTime);
    std::string vpassword = encode(password);

    std::stringstream vdata;
    for (auto& data : getInitData())
    {
        vdata << data.value << " ";
    }
    std::stringstream vdata2;
    for (auto& data2 : getInitWorldData())
    {
        vdata2 << data2.value << " ";
    }
    std::stringstream vdata3;
    for (auto& data3 : getInitStrData())
    {
        vdata3 << data3.value << " ";
    }
    std::stringstream vitem;
    for (auto& item : getInitItem())
    {
        vitem << item.count << " ";
    }

    std::string code = encode(vdata.str());
    std::string code2 = encode(vdata2.str());
    std::string code3 = encode(vdata3.str());
    std::string code4 = encode(vitem.str());
    std::string verCode = getVerificationCode(vtime + vpassword + code + code2 + code3 + code4);
    std::string res = vtime + "\n"
        + vpassword + "\n"
        + code + "\n"
        + code2 + "\n"
        + code3 + "\n"
        + code4 + "\n"
        + verCode;
    return res;
}
