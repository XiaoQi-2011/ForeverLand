#include <conio.h>
#include "SecretRealm.h"
#include "Fighting.h"

void sr_Loop() {
    while (true)
    {
        if (!sr_canGo) {
            Sleep(800);
            sr_canGo = true;
        }
        Sleep(1);
    }
}

void SecretRealm(Player& player, int choice) {
    escKeyPushEnable = false;

    system("cls");
    printf("--%s--\n", secretRealmNames[choice].c_str());
    printf(">开始探索，按esc键返回\n\n");
    Lottery<int> secretRealm = secretRealms[choice];
    Player srPlayer = player;
    while (true)
    {
        //_getch();
        Sleep(1);
        if (!sr_canGo) continue;
        if (player.getData(29) <= 0)
        {
            printf("你的体力已耗尽!\n");
            escKeyPushEnable = true;
            system("pause");
            return;
        }
        int object = secretRealm.lottery();
        if (object == secretRealm.NONE) object = 106;
        if (object > 0) {
            std::string item = player.items[object]->name;
            player.items[object]->count++;
            printf("你找到了 %s×1 (当前拥有 %d 个)\n\n", item.c_str(), player.items[object]->count);
        }
        if (object < 0) {
            object = -object;
            if (1 <= object && object <= 100) {
                Entity entity = srEntity[object];
                printf("你遇到了 %s 即将开始战斗\n\n", entity.name.c_str());
                bool isWin = fight(srPlayer, entity, player, false);
                if (!isWin) {
                    return;
                }
            }
        }
        if (escDown)
        {
            Sleep(120);
            escKeyPushEnable = true;
            return;
        }
        player.data[29]->value --;
        sr_canGo = false;
    }
}

void SecretRealmMenu(Player& player){
    SecretRealmMenu:
    system("cls");
    printf("--秘境--\n\n");
    for (int i = 0; i < srNumber; i++)
    {
        if (player.getData(0) < srMinLevel[i])
        {
            printf("\033[1;30m-[下一个秘境将在达到 Lv.%d 后解锁]-\033[0m\n\n", srMinLevel[i]);
            break;
        }
        printf("%d.%s%s\033[0m(Lv.%d+)\n", i + 1, secretRealmColor[i].c_str(), secretRealmNames[i].c_str(), srMinLevel[i]);
        printf("%s[描述] \033[0m%s\n", getColor({"#A4EDD6"}).c_str(), secretRealmDesc[i].c_str());
        printf("\n");
    }
    printf("\n请输入序号:\n");
    int choice = getChoice(1, srNumber);
    if (choice == -1) goto SecretRealmMenu;
    if (choice == -2) return;

    choice --;
    SecretRealm(player, choice);
    goto SecretRealmMenu;
}