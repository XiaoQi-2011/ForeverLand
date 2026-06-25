#include "Producer.h"

void printValues(bool showId)
{
    std::ofstream out("values.txt");
    for (Producer& producer : producers)
    {
        int jb = 0, zs = 0;
        for (auto obj : producer.table)
        {
            jb += producer.items[obj.first]->JB_value * obj.second;
            zs += producer.items[obj.first]->ZS_value * obj.second;
        }
        out << jb << " " << zs;
        if (showId)
        {
            out << " " << producer.id << std::endl;
        }
        else out << std::endl;
    }
}

void producerInit()
{
    for (int i = 0; i < kinds; i++)
    {
        int id = i * 4 + 11;
        int mineral = i + 1;
        int capture = i + 63;
        for (int j = 0; j < 4; j++)
        {
            producers.push_back(Producer(id, {
                                             {mineral, mineralCount[j]},
                                             {capture, captureCount[j]}
                                         }));
            if (i == 6)
            {
                producers.back().table.emplace_back(id - 4, 1);
            }
            id++;
        }
    }
}

void Produce(Player& player)
{
Produce:
    system("cls");
    printf("-合成区-\n\n");

    indexs.clear();
    int n = 0;
    for (int i = 0; i < producers.size(); i++)
    {
        bool show = false;
        for (auto obj : producers[i].table)
        {
            if (player.getItem(obj.first) > 0)
            {
                show = true;
                break;
            }
        }
        if (show)
        {
            n++;
            printf("%d.制作 %s\n", n, player.items[producers[i].id]->name.c_str());
            printf("%s\n\033[0;32m>所需材料：\033[0m\n", player.items[producers[i].id]->introduce.c_str());
            std::vector<std::pair<std::string, int>> itemList = producers[i].items.getItemList({"all"}, false);
            //printf("需要：");
            for (const auto& obj : itemList)
            {
                std::string color = player.getItem(obj.second) >= producers[i].items[obj.second]->count
                                   ? NumColors[0]
                                   : NumColors[1];
                printf("%s (你有%s%d\033[0m个)\n", obj.first.c_str(), color.c_str(), player.getItem(obj.second));
            }
            printf("\n");
            indexs.push_back(i);
        }
    }

    printf("\n请输入你要合成的物品序号：\n");
    int choice = getChoice(1, n);
    if (choice == -1) goto Produce;
    if (choice == -2) return;
    if (producers[indexs[choice - 1]].produce(player))
    {
        printf("合成成功！\n");
    }
    else
    {
        printf("合成失败，材料不足\n");
    }
    system("pause");
    goto Produce;
}
