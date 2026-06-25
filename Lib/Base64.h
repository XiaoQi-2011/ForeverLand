#ifndef BASE64_H
#define BASE64_H

#include <algorithm>
#include <iostream>
#include <string>
#include <functional>
#include <cstdint>
#include <random>

inline size_t Base64Key;
// 自定义随机数生成器 Base64 表
inline std::string generate_base64_table(const size_t seed)
{
    // 标准 Base64 字符表
    std::string table =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    std::mt19937 gen(seed);
    std::shuffle(table.begin(), table.end(), gen);

    return table;
}

// 判断是否为 Base64 字符
inline bool is_base64(char c, const std::string& table)
{
    return table.find(c) != std::string::npos;
}

// ===================== 自定义 Base64 编码函数 =====================
inline std::string encode(const std::string& data)
{
    const std::string table = generate_base64_table(Base64Key);
    std::string ret;
    int i = 0;
    uint8_t buf3[3];
    uint8_t buf4[4];
    size_t len = data.size();
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(data.c_str());

    for (size_t k = 0; k < len; ++k)
    {
        buf3[i++] = bytes[k];
        if (i == 3)
        {
            buf4[0] = (buf3[0] & 0xfc) >> 2;
            buf4[1] = ((buf3[0] & 0x03) << 4) + ((buf3[1] & 0xf0) >> 4);
            buf4[2] = ((buf3[1] & 0x0f) << 2) + ((buf3[2] & 0xc0) >> 6);
            buf4[3] = buf3[2] & 0x3f;

            for (i = 0; i < 4; ++i) ret += table[buf4[i]];
            i = 0;
        }
    }

    if (i > 0)
    {
        for (int j = i; j < 3; ++j) buf3[j] = 0;
        buf4[0] = (buf3[0] & 0xfc) >> 2;
        buf4[1] = ((buf3[0] & 0x03) << 4) + ((buf3[1] & 0xf0) >> 4);
        buf4[2] = ((buf3[1] & 0x0f) << 2) + ((buf3[2] & 0xc0) >> 6);
        buf4[3] = buf3[2] & 0x3f;

        for (int j = 0; j < i + 1; ++j) ret += table[buf4[j]];
        while (i++ < 3) ret += '=';
    }
    return ret;
}

// ===================== 自定义 Base64 解码函数 =====================
inline std::string decode(const std::string& encoded)
{
    const std::string table = generate_base64_table(Base64Key);
    std::string ret;
    int i = 0;
    uint8_t buf4[4], buf3[3];
    const size_t len = encoded.size();

    for (size_t k = 0; k < len && encoded[k] != '='; ++k)
    {
        if (!is_base64(encoded[k], table)) continue;
        buf4[i++] = encoded[k];
        if (i == 4)
        {
            for (i = 0; i < 4; ++i) buf4[i] = table.find(buf4[i]);
            buf3[0] = (buf4[0] << 2) | ((buf4[1] & 0x30) >> 4);
            buf3[1] = ((buf4[1] & 0x0f) << 4) | ((buf4[2] & 0x3c) >> 2);
            buf3[2] = ((buf4[2] & 0x03) << 6) | buf4[3];
            for (i = 0; i < 3; ++i) ret += buf3[i];
            i = 0;
        }
    }

    if (i > 0)
    {
        for (int j = i; j < 4; ++j) buf4[j] = 0;
        for (int j = 0; j < i; ++j) buf4[j] = table.find(buf4[j]);
        buf3[0] = (buf4[0] << 2) | ((buf4[1] & 0x30) >> 4);
        buf3[1] = ((buf4[1] & 0x0f) << 4) | ((buf4[2] & 0x3c) >> 2);
        if (i > 2) buf3[2] = ((buf4[2] & 0x03) << 6) | buf4[3];
        for (int j = 0; j < i - 1; ++j) ret += buf3[j];
    }
    return ret;
}

const char verificationTable[]{
    'F', 'O', 'R', '1', '7', '>', '*', '=', '#', '%'
};

inline std::string getVerificationCode(const std::string& str)
{
    unsigned long long add = 0;
    std::string code;
    for (int i = 0; i < str.size(); i++)
    {
        add += static_cast<int>(str[i]) * (i + 1);
    }
    std::string addStr = std::to_string(add);
    for (auto& c : addStr)
    {
        code += verificationTable[c - '0'];
    }
    return code;
}

constexpr char timeTable[]{
    '#', ']', 'h', '=', '[', 'O', '*', '_', '$', 'S'
};

inline long long decodeTime(const std::string& str)
{
    long long time = 0;
    for (char i : str)
    {
        for (int j = 0; j <= 9; j++)
        {
            if (i == timeTable[j])
            {
                time = time * 10 + j;
                break;
            }
        }
    }
    return time;
}

inline std::string encodeTime(long long time)
{
    std::string str, str2 = std::to_string(time);
    for (char i : str2)
    {
        str += timeTable[i - '0'];
    }
    return str;
}

#endif //BASE64_H
