#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>

#include "library.h"
#include "Event/Event.h"
using namespace std;
#define EXP_MAX ((pow(player.getData(0)/10+1, 2) * 100 + 10 * player.getData(0)) * 2 * pow(2, player.getData(0) / 100))

Player player;
string name;
long long tick = 0;
int hour = 7, minute = 0;
string dayPeriods[] {
    "\033[0;36m凌晨\033[0m", "\033[1;37m上午\033[0m", "\033[1;37m下午\033[0m", "\033[0;34m晚上\033[0m"
};
int periods[24] {
    3, 3, 3, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3
};

void playerLoop() {
    while (true) {
        Sleep(1);
        tick++;
        int exp_max = EXP_MAX;
        if (player.getData(1) >= exp_max) {
            // 成神
            int ping = 99 + player.getData(26) * 10;
            if (player.getData(0) >= ping) {
                player.data[1]->value = exp_max - 1;
                continue;
            }
            // level
            player.data[0]->value ++;
            player.data[1]->value -= exp_max;
            int lv = player.getData(0);
            //basic
            player.data[4]->value += 3;
            player.data[5]->value += 1;
            player.data[6]->value += 5;
            player.data[7]->value += 5;
            //shuxing
            player.data[8]->value += (int)(lv*0.6) - (int)((lv-1)*0.6);
            player.data[9]->value += (int)(lv*0.4) - (int)((lv-1)*0.4);
            player.data[10]->value += (int)(lv*0.3) - (int)((lv-1)*0.3);
            player.data[11]->value += (int)(lv*0.7) - (int)((lv-1)*0.7);
            player.data[12]->value += (int)(lv*0.4) - (int)((lv-1)*0.4);
            player.data[13]->value += (int)(lv*0.4) - (int)((lv-1)*0.4);
            printf("\n\033[1;32m[+]\033[0m你已升级, 当前等级 lv.%d\n", lv);
        }
        if (player.getData(9) > 80) player.data[9]->value = 80;
        if (player.getData(10) > 80) player.data[10]->value = 80;
        if (tick % 50 == 0) {
            player.writeFile();
        }
    }
}
thread playerLoopThread;
void worldLoop() {
    while (true) {
        Sleep(1000);
        player.worldData[1]->value ++;
        if (player.getWorldData(1) >= 1440) {
            player.worldData[1]->value -= 1440;
            player.worldData[2]->value ++;
        }
        hour = player.getWorldData(1) / 60;
        minute = player.getWorldData(1) % 60;
        dayPeriod = periods[hour];
        second ++;
        if (second >= zahuoFlash * zahuoFlashTime) {
            if(zahuoFlash == 0) {
                initZahuo(player);
            } else {
                reflashZahuo(player);
                printf("\n\033[0;32m--杂货铺已刷新--\033[0m\n");
            }
            zahuoFlash ++;
        }
        if (second >= shenmiFlash * shenmiFlashTime) {
            if(shenmiFlash == 0) {
                initShenmi(player);
            } else {
                reflashShenmi(player);
                printf("\n\033[0;35m--神秘商人已刷新--\033[0m\n");
            }
            shenmiFlash ++;
        }
        for (auto & boss : worldBosses) {
            if (boss.flashTime != 0) {
                if (second >= boss.count * boss.flashTime) {
                    boss.isFlashed = true;
                    printf("\n\033[1;31m--------世界Boss--------\n");
                    printf("[Boss] %s 已刷新\033[0m\n", boss.boss.name.c_str());
                    boss.count ++;
                }
            }
        }
    }
}
thread worldLoopThread;
int main()
{
    // 系统初始设置
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {150, 150, 400, 250}; // 设置窗口的左上角和右下角坐标
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    random_device rd;
    gen = mt19937(rd());

    // 初始化常量
    initEquipmentItem();

    // 用户登录
    name = login();
    player.name = name;
    player.path = pathString + name + endString;
    player.readFile();

    // 初始化用户常量
    initKeys(player);
    producerInit();
    hour = player.getWorldData(1) / 60;
    minute = player.getWorldData(1) % 60;
    dayPeriod = periods[hour];
    //printValues(true);

    // 启动线程
    playerLoopThread = thread(playerLoop);
    worldLoopThread = thread(worldLoop);
    thread(MineLoop).detach();

    // 主循环
    while (true)
    {
        int exp_max = EXP_MAX;
        system("cls");
        system("title 永恒大陆");
        printf("欢迎来到【永恒大陆】 (按下ESC返回上级) \n");
        if (player.getData(26) > 0) printf("\033[1;31m[%d级神]", player.getData(26));
        printf("[lv.%d] %s\033[0m\n", player.getData(0), name.c_str());
        printf("[经验值] %d/%d\n", player.getData(1), exp_max);
        printf("[金币] %d  [钻石] %d\n", player.getData(2), player.getData(3));
        printf("[攻击力] %d  [防御力] %d [生命值] %d/%d\n", player.getData(4), player.getData(5), player.getData(6), player.getData(7));
        printf("[时间] 第%d天 %d:%02d (%s) \n", player.getWorldData(2)+1, hour, minute, dayPeriods[dayPeriod].c_str());
        cout << "\033[4m菜单\033[0m:" << endl << endl;
        cout << "1.个人信息" << endl;
        cout << "2.物品栏" << endl;
        cout << "3.矿区" << endl;
        cout << "4.交易区" << endl;
        cout << "5.合成区" << endl;
        cout << "6.副本" << endl;
        cout << "7.功能区" << endl;
        cout << "8.设置" << endl;
        int choice = getChoice(1, 8);
        if (choice == -1 || choice == -2) continue;
        switch (choice) {
            case 1: {
                showPlayerData(player);
                break;
            }
            case 2: {
                showPlayerItems(player);
                break;
            }
            case 3: {
                MineMenu(player);
                break;
            }
            case 4: {
                TradeMenu(player);
                break;
            }
            case 5: {
                Produce(player);
                break;
            }
            case 6: {
                fuben(player);
                break;
            }
            case 7: {
                workArea(player);
                break;
            }
            case 8: {
                setting(player);
                break;
            }
            default: {
                cout << "此功能暂未开发" << endl;
                system("pause");
                break;
            }
        }
    }
}
