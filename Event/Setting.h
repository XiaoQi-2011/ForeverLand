#ifndef FOREVERLAND_SETTING_H
#define FOREVERLAND_SETTING_H

#include <iostream>
#include <vector>
#include <conio.h>

#include "../library.h"

using namespace std;
// 1
void changePassword(Player& player) {
    changePassword:
    system("cls");
    string oldPassword, newPassword;
    cout << "请输入原密码:" << endl;
    cin >> oldPassword;
    if (oldPassword == "back") return;
    if (oldPassword != player.password) {
        cout << "密码错误!" << endl;
        system("pause");
        goto changePassword;
    }
    cout << "请输入新密码:" << endl;
    if (newPassword == "back") return;
    cin >> newPassword;
    player.password = newPassword;
    cout << "密码修改成功!" << endl;
    system("pause");
}
// 2
void setKey(Player& player) {
    setKey:
    system("cls");
    printf("按键设置:\n\n");
    vector<string> keys = split(player.getStrData(2), '$');
    // 显示按键
    printf("1.攻击/挖掘: %s\n", keys[0].c_str());
    printf("2.查看药水: %s\n", keys[1].c_str());
    for (int i = 2; i <= 7; i++) {
        string itemName = init_item[i - 2 + 57].name;
        printf("%d.使用%s: %s\n", i+1, itemName.c_str(), keys[i].c_str());
    }

    printf("\n请输入序号: \n");
    int choice = getChoice(1, 8);
    if (choice == -1) goto setKey;
    if (choice == -2) return;

    printf("请按下按键: \n");
    char c = (char)_getch();
    keys[choice - 1] = c;
    stringstream ss;
    for (const auto & key : keys) {
        ss << key << "$";
    }
    player.strData[2]->value = ss.str();
    goto setKey;
}
// 3
void getGift(Player& player) {
    getGift:
    system("cls");
    cout << "请输入礼包兑换码:" << endl;
    string code;
    cin >> code;
    if (code == "back") return;
    code = getVerificationCode(code);
    // test_sh8ah173j
    if (code == "#=R=") {
        for (auto & item : player.items.items) {
            if (start_with(item.type, "equipment")) item.count = 2;
            else item.count = 100;
        }
        cout << "兑换成功!" << endl;
        system("pause");
        goto getGift;
    }
    // /setitem
    if (code == "1#77") {
        cout << "请输入物品ID和数量:" << endl;
        int id, count;
        cin >> id >> count;
        if (id < 0 || id > ITEM_NUM) {
            cout << "无效的物品ID!" << endl;
            system("pause");
            goto getGift;
        }
        player.items[id]->count = count;
        goto getGift;
    }
    // /setdata
    if (code == "1=O7") {
        cout << "请输入数据ID和数量:" << endl;
        int id, count;
        cin >> id >> count;
        if (id < 0 || id > DATA_NUM) {
            cout << "无效的数据ID!" << endl;
            system("pause");
            goto getGift;
        }
        player.data[id]->value = count;
        goto getGift;
    }
    cout << "无效的兑换码!" << endl;
    system("pause");
    goto getGift;
}
// 4
void test(Player& player) {
    test:
    system("cls");
    cout << "输入测试码:" << endl;
    string code;
    getline(cin, code);
    if (code == "back") return;
    if (code == "test1") {
        for (auto & data : player.worldData.datas) {
            printf("%s(%s): %d\n", data.name.c_str(), data.type.c_str(), data.value);
        }
        system("pause");
        goto test;
    }
    goto test;
}
// 5
void about() {
    system("cls");
    printf("-关于- \n\n");
    cout << "作者: XiaoQi" << endl;
    cout << "版本: " << version << endl;
    cout << "Github: https://github.com/XiaoQi-2011/ForeverLand (暂时没有)" << endl;
    cout << endl;

    // 装备品质
    printf("装备品质(从低到高): \n\n");
    for (int i = 0; i <= 5; i++) {
        printf("%s%s\n", item_quality[i].second.c_str(), item_quality[i].first.c_str());
    }
    char colour[100];
    int light = Random(0, 1);
    int back_ground = light ? Random(41, 47) : Random(101, 107);
    sprintf(colour, item_quality[6].second.c_str(), back_ground);
    string color = colour;
    printf("%s%s[n阶]\033[0m\n", color.c_str(), item_quality[6].first.c_str());
    cout << endl;

    printf("[小提示]: win10用户将cmd字体调为黑体效果更佳!\n\n");
    printf("挖矿每挖一下损失1点体力\n\n");
    system("pause");
}
//Menu
inline void setting(Player& player) {
    setting:
    system("cls");
    printf("-设置-\n\n");
    cout << "1.修改密码" << endl;
    cout << "2.按键设置" << endl;
    cout << "3.获取礼包" << endl;
    cout << "4.测试" << endl;
    cout << "5.说玩法明" << endl;
    cout << endl;
    int choice = getChoice(1, 5);
    if (choice == -1) goto setting;
    if (choice == -2) return;
    switch (choice) {
        case 1: {
            changePassword(player);
            goto setting;
        }
        case 2: {
            setKey(player);
            goto setting;
        }
        case 3: {
            getGift(player);
            goto setting;
        }
        case 4: {
            test(player);
            goto setting;
        }
        case 5: {
            about();
            goto setting;
        }
        default:
            break;
    }
}

#endif //FOREVERLAND_SETTING_H
