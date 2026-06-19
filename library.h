#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <windows.h>
#include <random>
#include <fstream>
#include <string>
#include <thread>

#include "Data.h"
using namespace std;

const string version = "1.0.2";
long long second = 0;
mt19937 gen;

inline string getFormatSystemTime(long long time)
{
    // 获取时间戳
    time_t now = time;
    // 转为本地时间结构体
    tm local_tm = *std::localtime(&now);

    char buf[20] = { 0 }; // 存放格式化时间字符串，yyyy-MM-dd HH:mm:ss 固定19字符
    // 格式化：%Y四位年 %m两位月 %d日 %H24小时制 %M分 %S秒
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local_tm);

    return string(buf);
}
void ListUsers(const filesystem::path& path) {
    vector<Player> users;
    int wide1 = 0, wide2 = 0, wide3 = 0;
    for (const auto& entry : filesystem::directory_iterator(path)) {
        string filename = entry.path().filename().generic_string();
        string username = filename.substr(0, filename.find('.'));
        string suffix = filename.substr(filename.find('.') + 1);
        if (suffix != "fl") continue;
        Player player(path.generic_string() + filename);
        player.name = username;
        player.readFile();
        users.push_back(player);
        wide1 = max(wide1, (int)username.size() + 2);
        int count = to_string(player.getData(0)).size();
        wide2 = max(wide2, count + 7);
    }
    for (auto &player : users) {
        string level = "[Lv." + to_string(player.getData(0)) + "]";
        string time = "创建时间:" + getFormatSystemTime(player.createTime);
        cout << left
             << setw(wide1) << player.name
             << setw(wide2) << level
             << setw(wide3) << time
             << endl;
    }
}
inline int Random(int min, int max) {
    if (min > max) swap(min, max);
    uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

string getFormatString(string str) {
    int pos = -1, n = 0;
    for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i])) {
            if (pos == -1) pos = i;
            n++;
        } else if (pos != -1) {
            i = i - n + 3;
            pos = -1;
            n = 0;
        }
    }
    if (pos != -1) {
        str.replace(pos, n, "%d%");
    }
    return str;
}
inline bool isNumber(const string& str) {
    if (str.empty()) return false;
    return all_of(str.begin(), str.end(), [](char c) {
        return isdigit(c);
    });
}

inline int getChoice(int min, int max, string& input, const vector<string>& whiteList) {
    getline(cin, input);
    if (input.empty()) return -1;
    if (input == "back") return -2;
    if (!whiteList.empty()) {
        for (const string& str : whiteList) {
            if (getFormatString(input) == str)
                return -3;
        }
    }
    int choice;
    if (isNumber(input)) {
        choice = stoi(input);
    } else {
        cout << "输入错误!" << endl;
        system("pause");
        return -1;
    }
    if (choice < min || choice > max) {
        cout << "输入数据不在范围内!" << endl;
        system("pause");
        return -1;
    }
    return choice;
}

inline int getChoice(int min, int max) {
    string input;
    return getChoice(min, max, input, vector<string>());
}

inline bool escKeyPushEnable = true;
inline bool escDown = false;
inline void escKeyListener() {
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            escDown = true;
            Sleep(100);
            if (escKeyPushEnable) {
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
inline thread escListener(escKeyListener);

inline const string endString = ".fl";
inline const string pathString = "Users\\";

inline string login() {
    escListener.detach();
    LOGIN:
    system("cls");
    system("title 登录");
    cout << "----------ForeverLand----------\n"
            "欢迎来到 永恒大陆！\n"
            "version " + version + "\n"
            "by XiaoQi\n"
            "(按下ESC返回主菜单)\n"
            "-------------------------------\n";
    cout << "请选择："<< endl;
    cout << "1:登录" << endl << "2:注册"<< endl;
    int choice = getChoice(1, 2);
    if (choice == -1 || choice == -2) goto LOGIN;

    string path;
    system("cls");

    if (choice == 1) {
        string name, password;
        cout << "所有账户: \n";
        ListUsers(pathString);
        cout << endl;
        cout << "请输入用户名: \n";
        cin >> name;
        if(name=="back") goto LOGIN;
        path = pathString + name + endString;
        cout << "请输入密码: \n";
        cin >> password;
        if(password == "back") goto LOGIN;
        Player player(path);
        Player::fileType success = player.readFile();
        if (success == Player::fileType::NO_EXISTS) {
            cout << "用户不存在！" << endl;
            system("pause");
            goto LOGIN;
        }
        if (success == Player::fileType::DATA_ERROR) {
            cout << "用户数据已损坏！" << endl;
            system("pause");
            goto LOGIN;
        }
        if (player.password == password) {
            return name;
        } else {
            cout << "密码错误！" << endl;
            system("pause");
            goto LOGIN;
        }
    }
    if (choice == 2) {
        string name, password;
        cout << "请输入用户名: \n";
        cin >> name;
        if(name=="back") goto LOGIN;
        path = pathString + name + endString;
        cout << "请输入密码: \n";
        cin >> password;
        if(password=="back") goto LOGIN;
        cout << "请输入确认密码: \n";
        string confirm_password;
        cin >> confirm_password;
        if(confirm_password=="back") goto LOGIN;
        if (password == confirm_password) {
            CreateFileA(path.c_str(), 0, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
            ofstream fout(path);
            fout << getInitString(password);
            fout.close();
            return name;
        } else {
            cout << "两次密码输入不一致！" << endl;
            goto LOGIN;
        }
    }
    goto LOGIN;
}

template<class T>
struct Lottery {
    struct Object {
        T object;
        int percent = 0;

        Object() = default;
        Object(T object, int percent) {
            this->object = object;
            this->percent = percent;
        }
    };
    enum Return {
        NONE
    };
    vector<Object> objects;
    int totalPercent = 100;
    void BubbleSort() {
        int n = objects.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (objects[j].percent > objects[j + 1].percent) {
                    Object temp = objects[j];
                    objects[j] = objects[j + 1];
                    objects[j + 1] = temp;
                }
            }
        }
    }

    Lottery() = default;
    explicit Lottery(vector<Object> objects, int totalPercent = 100) {
        this->objects = objects;
        this->totalPercent = totalPercent;
    }

    void setObjects(vector<Object> object) {
        this->objects = object;
    }
    void addObject(T object, int percent) {
        objects.push_back(Object(object, percent));
    }

    T lottery() {
        int lastPercent = 0;
        int randNum = Random(1, totalPercent);
        BubbleSort();
        for (int i = 0; i < objects.size(); i++) {
            if (lastPercent <= randNum && randNum <= lastPercent + objects[i].percent) {
                return objects[i].object;
            } else {
                lastPercent += objects[i].percent;
            }
        }
        return NONE;
    }
};

inline vector<string> split(const string& str, char splitChar) {
    vector<string> result;  // 存储分割后的字符串数组
    string current;              // 临时存储当前片段
    // 遍历字符串每一个字符
    for (char ch : str) {
        if (ch == splitChar) {
            // 遇到分隔符：如果当前片段不为空，就存入结果
            if (!current.empty()) {
                result.push_back(current);
                current.clear(); // 清空，准备下一段
            }
        } else {
            // 不是分隔符：追加到当前片段
            current += ch;
        }
    }
    // 循环结束后，把最后一段也加进去
    if (!current.empty()) {
        result.push_back(current);
    }
    return result;
}

#endif //LIBRARY_H
