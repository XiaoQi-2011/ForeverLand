#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <windows.h>
#include <random>
#include <fstream>
#include <string>
#include <thread>

#include "Data.h"
#include "Player.h"

constexpr std::string version = "1.0.2";
inline long long second = 0;
inline std::mt19937 gen;
inline std::string difficulties[] = {
        "\033[0;37m简单\033[0m",
        "\033[1;37m普通\033[0m",
        "\033[1;34m中等\033[0m",
        "\033[1;31m困难\033[0m",
        "\033[0;31m噩梦\033[0m"
};

inline std::string getFormatSystemTime(long long time)
{
    // 获取时间戳
    time_t now = time;
    // 转为本地时间结构体
    tm local_tm = *std::localtime(&now);

    char buf[20] = {0}; // 存放格式化时间字符串，yyyy-MM-dd HH:mm:ss 固定19字符
    // 格式化：%Y四位年 %m两位月 %d日 %H24小时制 %M分 %S秒
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local_tm);

    return std::string(buf);
}

inline void ListUsers(const std::filesystem::path& path)
{
    std::vector<Player> users;
    int wide1 = 0, wide2 = 0;
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        std::string filename = entry.path().filename().generic_string();
        std::string username = filename.substr(0, filename.find('.'));
        std::string suffix = filename.substr(filename.find('.') + 1);
        if (suffix != "fl") continue;
        Player player(path.generic_string() + filename);
        player.name = username;
        player.readFile();
        users.push_back(player);
        wide1 = std::max(wide1, (int)username.size() + 2);
        int count = std::to_string(player.getData(0)).size();
        wide2 = std::max(wide2, count + 7);
    }
    for (auto& player : users)
    {
        std::string level = "[Lv." + std::to_string(player.getData(0)) + "]";
        std::string time = "创建时间:" + getFormatSystemTime(player.createTime);
        std::string difficulty = difficulties[player.getWorldData(3)];
        std::cout << std::left
            << std::setw(wide1) << player.name
            << std::setw(wide2) << level
            << difficulty << "  "
            << time
            << std::endl;
    }
}

inline int Random(int min, int max)
{
    if (min > max) std::swap(min, max);
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

inline std::string getFormatString(std::string str)
{
    int pos = -1, n = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (isdigit(str[i]))
        {
            if (pos == -1) pos = i;
            n++;
        }
        else if (pos != -1)
        {
            i = i - n + 3;
            pos = -1;
            n = 0;
        }
    }
    if (pos != -1)
    {
        str.replace(pos, n, "%d%");
    }
    return str;
}

inline bool isNumber(const std::string& str)
{
    if (str.empty()) return false;
    return std::all_of(str.begin(), str.end(), [](char c)
    {
        return isdigit(c);
    });
}

inline int getChoice(int min, int max, std::string& input, const std::vector<std::string>& whiteList)
{
    std::getline(std::cin, input);
    if (input.empty()) return -1;
    if (input == "back") return -2;
    if (!whiteList.empty())
    {
        for (const std::string& str : whiteList)
        {
            if (getFormatString(input) == str)
                return -3;
        }
    }

    int choice;
    if (isNumber(input))
    {
        choice = stoi(input);
    }
    else
    {
        std::cout << "输入错误!" << std::endl;
        getchar();
        return -1;
    }
    if (choice < min || choice > max)
    {
        std::cout << "输入数据不在范围内!" << std::endl;
        getchar();
        return -1;
    }
    return choice;
}

inline int getChoice(int min, int max)
{
    std::string input;
    return getChoice(min, max, input, std::vector<std::string>());
}

inline bool escKeyPushEnable = true;
inline bool escDown = false;

inline void escKeyListener()
{
    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            escDown = true;
            Sleep(100);
            if (escKeyPushEnable)
            {
                keybd_event(66, 0, 0, 0);
                keybd_event(66, 0, KEYEVENTF_KEYUP, 0);
                keybd_event(65, 0, 0, 0);
                keybd_event(65, 0, KEYEVENTF_KEYUP, 0);
                keybd_event(67, 0, 0, 0);
                keybd_event(67, 0, KEYEVENTF_KEYUP, 0);
                keybd_event(75, 0, 0, 0);
                keybd_event(75, 0, KEYEVENTF_KEYUP, 0);
                keybd_event(VK_RETURN, 0, 0, 0);
                keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
            }
            Sleep(100);
            escDown = false;
        }
    }
}

inline constexpr std::string endString = ".fl";
inline constexpr std::string pathString = "Users\\";

inline std::string login()
{
    std::thread(escKeyListener).detach();
LOGIN:
    system("cls");
    system("title 登录");
    std::cout << "----------ForeverLand----------\n"
        "欢迎来到 永恒大陆！\n"
        "version " + version + "\n"
        "by XiaoQi\n"
        "(按下ESC返回主菜单)\n"
        "-------------------------------\n";
    std::cout << "请选择：" << std::endl;
    std::cout << "1:登录" << std::endl << "2:注册" << std::endl;
    int choice = getChoice(1, 2);
    if (choice == -1 || choice == -2) goto LOGIN;

    if (!std::filesystem::exists(pathString)) {
        std::filesystem::create_directory(pathString);
    }
    std::string path;
    system("cls");

    if (choice == 1)
    {
        std::string name, password;
        std::cout << "所有账户: \n";
        ListUsers(pathString);
        std::cout << std::endl;
        std::cout << "请输入用户名: \n";
        std::cin >> name;
        if (name == "back") goto LOGIN;
        path = pathString + name + endString;
        std::cout << "请输入密码: \n";
        std::cin >> password;
        if (password == "back") goto LOGIN;
        Player player(path);
        Player::fileType success = player.readFile();
        if (success == Player::fileType::NO_EXISTS)
        {
            std::cout << "用户不存在！" << std::endl;
            system("pause");
            goto LOGIN;
        }
        if (success == Player::fileType::DATA_ERROR)
        {
            std::cout << "用户数据已损坏！" << std::endl;
            system("pause");
            goto LOGIN;
        }
        if (player.password == password)
        {
            return name;
        }

        std::cout << "密码错误！" << std::endl;
        system("pause");
    }

    if (choice == 2)
    {
        std::string name, password;
        std::cout << "请输入用户名: \n";
        std::cin >> name;
        if (name == "back") goto LOGIN;

        path = pathString + name + endString;
        std::cout << "请输入密码: \n";
        std::cin >> password;
        if (password == "back") goto LOGIN;

        std::cout << "请输入确认密码: \n";
        std::string confirm_password;
        std::cin >> confirm_password;

        std::cout << "请选择游戏难度: \n";
        for (int i = 0; i < 5; i++) {
            std::cout << i + 1 << ". " << difficulties[i] << std::endl;
        }
        //std::cout << "\n";
        int difficulty;
        getchar();
        difficulty = getChoice(1, 5);
        if (difficulty == -1 || difficulty == -2) goto LOGIN;

        if (confirm_password == "back") goto LOGIN;
        if (password == confirm_password)
        {
            CreateFileA(path.c_str(), 0, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
            std::ofstream fout(path);
            fout << getInitString(password);
            fout.close();

            // 玩家内部数据修改
            Player player(path);
            player.readFile();

            player.worldData[3]->value = difficulty - 1;

            player.writeFile();

            return name;
        }

        std::cout << "两次密码输入不一致！" << std::endl;
        system("pause");
    }

    goto LOGIN;
}

template <class T>
struct Lottery
{
    struct Object
    {
        T object;
        int percent = 0;

        Object() = default;

        Object(T object, int percent)
        {
            this->object = object;
            this->percent = percent;
        }
    };

    enum Return
    {
        NONE
    };

    std::vector<Object> objects;
    int totalPercent = 100;

    void BubbleSort()
    {
        int n = objects.size();
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (objects[j].percent > objects[j + 1].percent)
                {
                    Object temp = objects[j];
                    objects[j] = objects[j + 1];
                    objects[j + 1] = temp;
                }
            }
        }
    }

    Lottery() = default;

    explicit Lottery(std::vector<Object> objects, int totalPercent = 100)
    {
        this->objects = objects;
        this->totalPercent = totalPercent;
    }

    void setObjects(std::vector<Object> object)
    {
        this->objects = object;
    }

    void addObject(T object, int percent)
    {
        objects.push_back(Object(object, percent));
    }

    T lottery()
    {
        int lastPercent = 0;
        int randNum = Random(1, totalPercent);
        BubbleSort();
        for (int i = 0; i < objects.size(); i++)
        {
            if (lastPercent <= randNum && randNum <= lastPercent + objects[i].percent)
            {
                return objects[i].object;
            }
            else
            {
                lastPercent += objects[i].percent;
            }
        }
        return NONE;
    }
};

inline std::vector<std::string> split(const std::string& str, char splitChar)
{
    std::vector<std::string> result; // 存储分割后的字符串数组
    std::string current; // 临时存储当前片段
    // 遍历字符串每一个字符
    for (char ch : str)
    {
        if (ch == splitChar)
        {
            // 遇到分隔符：如果当前片段不为空，就存入结果
            if (!current.empty())
            {
                result.push_back(current);
                current.clear(); // 清空，准备下一段
            }
        }
        else
        {
            // 不是分隔符：追加到当前片段
            current += ch;
        }
    }
    // 循环结束后，把最后一段也加进去
    if (!current.empty())
    {
        result.push_back(current);
    }
    return result;
}

#endif //LIBRARY_H
