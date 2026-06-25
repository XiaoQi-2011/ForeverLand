#include "Mine.h"
#include "conio.h"

void MineLoop()
{
    while (true)
    {
        if (!canMine)
        {
            Sleep(9990 / mineSpeed);
            canMine = true;
        }

        Sleep(1);
    }
}

void Mine(Player& player, int choice)
{
    mineKey = player.getStrData(2)[0];
    mineSpeed = player.getData(15);
    escKeyPushEnable = false;

    system("cls");
    printf("--%s--\n", mineNames[choice].c_str());
    printf(">按%c键挖掘，按esc键返回\n\n", mineKey);
    Lottery<int> mine = mines[choice];
    while (true)
    {
        int key = _getch();
        if (key == mineKey)
        {
            if (!canMine) continue;
            if (stamina <= 0)
            {
                printf("你的体力已耗尽!\n\n");
                canMine = false;
                continue;
            }
            int object = mine.lottery();
            std::string item = player.items[object]->name;
            player.items[object]->count++;
            printf("你挖到了 %s×1 (当前拥有 %d 个)\n\n", item.c_str(), player.items[object]->count);
            canMine = false;
            stamina--;
        }
        if (escDown)
        {
            Sleep(120);
            escKeyPushEnable = true;
            return;
        }
    }
}

void MineMenu(Player& player)
{
Mine:
    system("cls");
    printf("--矿区--\n\n");
    for (int i = 0; i < mineNumber; i++)
    {
        memset(tong, 0, sizeof(tong));
        if (player.getData(0) < levels[i])
        {
            printf("\033[1;30m-[下一个矿区将在达到 Lv.%d 后解锁]-\033[0m\n\n", levels[i]);
            break;
        }
        for (auto obj : mines[i].objects)
        {
            tong[obj.object] = obj.percent;
        }
        printf("%d.%s(Lv.%d+ 挖掘等级 %d+)\n", i + 1, mineNames[i].c_str(), levels[i], mineLevels[i]);
        printf("[矿产] ");
        for (int j = 0; j < ITEM_NUM; j++)
        {
            if (tong[j] == 0) continue;
            if (init_item[j].type == "mineral" || init_item[j].type == "lingshi")
            {
                printf("%s(%d%%) ", player.items[j]->name.c_str(), tong[j]);
            }
        }
        printf("\n");
        printf("[特殊] ");
        for (int j = 0; j < ITEM_NUM; j++)
        {
            if (tong[j] == 0) continue;
            if (init_item[j].type == "chest")
            {
                printf("%s(%d%%) ", player.items[j]->name.c_str(), tong[j]);
            }
        }
        printf("\n\n");
    }

    std::cout << "请输入序号:" << std::endl;
    int choice = getChoice(1, mineNumber);
    if (choice == -1) goto Mine;
    if (choice == -2) return;
    choice--;

    if (player.getData(16) < mineLevels[choice])
    {
        std::cout << "挖掘等级不足!" << std::endl;
        system("pause");
        goto Mine;
    }
    if (player.getData(0) < levels[choice])
    {
        std::cout << "等级不足!" << std::endl;
        system("pause");
        goto Mine;
    }
    Mine(player, choice);
    goto Mine;
}
