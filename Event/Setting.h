#ifndef FOREVERLAND_SETTING_H
#define FOREVERLAND_SETTING_H

#include <iostream>
#include <utility>

#include "../Lib/Library.h"

struct Control {
    std::string name;
    std::string value;
    const std::string boolColors[2] {
        "\033[1;32m", // 绿色
        "\033[1;31m"  // 红色
    };

    enum Type {
        Int,
        Long,
        Char,
        String,
        Bool,
        Float,
        Double
    } type;

    bool judgmentValue(const std::string& value) const {
        try {
            switch (type) {
                case Int:
                    std::stoi(value);
                    break;
                case Long:
                    std::stoll(value);
                    break;
                case Char:
                    return value.size() == 1;
                case String:
                    break;
                case Bool:
                    return value == "true" || value == "false";
                case Float:
                    std::stof(value);
                    break;
                case Double:
                    std::stod(value);
                    break;
            }
            return true;
        } catch (...) {
            return false;
        }
    }

    Control(std::string name, std::string value, Type type) {
        this->name = name;
        this->value = value;
        this->type = type;
        if (!judgmentValue(this->value)) {
            if (type == Int || type == Long)
                this->value = "0";
            else if (type == Float || type == Double)
                this->value = "0.0";
            else if (type == Char)
                this->value = " ";
            else if (type == Bool)
                this->value = "false";
        }
    }

    bool input(std::string& input) {
        if (judgmentValue(input)) {
            value = input;
            return true;
        } else {
            return false;
        }
    }
};
inline const int controlsNum = 2;
inline Control controls[controlsNum] = {
        Control("右上角血条显示(实验性功能)", "true", Control::Bool),
        Control("测试", "test", Control::String),
};

// 函数声明
void changePassword(Player& player);
void setKey(Player& player);
void getGift(Player& player);
void control(Player& player);
void about();

void setting(Player& player);

void loadControls(Player& player);
void saveControls(Player& player);
std::string getControls(int index);

#endif //FOREVERLAND_SETTING_H
