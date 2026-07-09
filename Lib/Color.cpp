#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Color.h"
#include "Library.h"

std::string getColor(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}
std::string getColor(color c) {
    return "\033[38;2;" + std::to_string(c.r) + ";" + std::to_string(c.g) + ";" + std::to_string(c.b) + "m";
}
std::string getFakeColor(color c) {
    return "\\033[38;2;" + std::to_string(c.r) + ";" + std::to_string(c.g) + ";" + std::to_string(c.b) + "m";
}

/**
 * @brief Hex颜色字符串转RGB
 * @param hexStr 颜色字符串，支持 #FF00FF / FF00FF
 * @param outRgb 输出RGB结果
 * @return 转换成功返回true，格式错误返回false
 */
color color::hexToRgb(const std::string& hexStr)
{
    color outRgb(0, 0, 0);
    std::string hex;
    // 处理带#前缀
    if (!hexStr.empty() && hexStr[0] == '#')
    {
        hex = hexStr.substr(1);
    }
    else
    {
        hex = hexStr;
    }

    // 必须是6位十六进制字符
    if (hex.size() != 6)
        return outRgb;

    // 转换工具：单个十六进制字符转数字
    auto hexCharToNum = [](char c) -> int
    {
        if (isdigit(c)) return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return -1; // 非法字符
    };

    int r1 = hexCharToNum(hex[0]);
    int r2 = hexCharToNum(hex[1]);
    int g1 = hexCharToNum(hex[2]);
    int g2 = hexCharToNum(hex[3]);
    int b1 = hexCharToNum(hex[4]);
    int b2 = hexCharToNum(hex[5]);

    // 存在非法字符
    if (r1 == -1 || r2 == -1 || g1 == -1 || g2 == -1 || b1 == -1 || b2 == -1)
        return outRgb;

    // 拼接两位十六进制为0~255数值
    outRgb.r = static_cast<int>(r1 * 16 + r2);
    outRgb.g = static_cast<int>(g1 * 16 + g2);
    outRgb.b = static_cast<int>(b1 * 16 + b2);

    return outRgb;
}

color hexToRgb(const std::string& hexStr) {
    return color::hexToRgb(hexStr);
}

std::string getGradientString(color start, color end, const std::string& str) {
    std::string result;
    std::vector<std::string> strArray = split(str, '\n');
    int len = 0;
    std::string maxStr;
    for (std::string s : strArray) {
        Utf8string utf8str(std::move(s));
        if (utf8str.size() > len) {
            len = utf8str.size() - 1;
            maxStr = s;
        }
    }
    for (char c : maxStr) {
        if (c == ' ') {
            len --;
        }
    }
    int rc = (end.r - start.r) / len;
    int gc = (end.g - start.g) / len;
    int bc = (end.b - start.b) / len;

    for (std::string s : strArray) {
        std::string res;
        Utf8string utf8str(std::move(s));
        color cur = start;
        for (int i = 0; i < utf8str.size(); i++) {
            if (utf8str[i] == " " || utf8str[i] == "\n") {
                res += utf8str[i];
                continue;
            }
            res += getColor(cur) + utf8str[i];
            cur.r += rc;
            cur.g += gc;
            cur.b += bc;
        }
        result += res + "\033[0m\n";
    }
    result.pop_back();
    return result;
}