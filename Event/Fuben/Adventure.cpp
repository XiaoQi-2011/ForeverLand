#include "Adventure.h"
#include "../../Lib/Item.h"
#include "../Fighting.h"

void adventure(Player& player)
{
adventure:
    system("cls");
    std::cout << "-冒险世界-" << std::endl << std::endl;
    for (int i = 0; i < adventureMsts.size(); i++)
    {
        if (player.getData(0) < i * 10)
        {
            printf("\033[1;30m-[下一个副本将在达到 Lv.%d 后解锁]-\033[0m\n\n", i * 10);
            break;
        }
        printf("%d.%s(Lv.%d+)\n", i + 1, adventureMsts[i].world.c_str(), i * 10);
        printf("[小怪] %s Lv.%d~%d %s Lv.%d~%d\n", adventureMsts[i].name1.c_str(), i * 10 + 1, i * 10 + 5,
               adventureMsts[i].name2.c_str(), i * 10 + 6, i * 10 + 9);
        printf("[Boss] %s Lv.%d\n", adventureMsts[i].bossName.c_str(), (i + 1) * 10);
        printf("[掉落物] %s \n", init_item[i + 63].name.c_str());
        std::cout << std::endl;
    }
    std::cout << "请输入序号:" << std::endl;
    int choice = getChoice(1, 8);
    if (choice == -1) goto adventure;
    if (choice == -2) return;
    int n = 0;
    choice--;
    system("cls");
    createFightArea(player, "你来到了 " + adventureMsts[choice].world);
    Player fakePlayer = player;
    bool flag = false;
    while (true)
    {
        Entity entity;
        if (n == 10)
        {
            n = 0;
            entity = adventureMsts[choice].createAMonster(true);
            printf("\033[1;31m你遇到了Boss: \033[0m%s\n\n", entity.name.c_str());
        }
        else
        {
            entity = adventureMsts[choice].createAMonster(false);
            printf("你遇到了新的小怪: %s\n\n", entity.name.c_str());
        }
        bool wins = fight(fakePlayer, entity, player, flag);
        if (!flag) flag = true;
        if (!wins) goto adventure;
        n++;
    }
}
