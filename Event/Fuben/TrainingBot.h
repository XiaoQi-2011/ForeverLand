#ifndef FOREVERLAND_TRAININGBOT_H
#define FOREVERLAND_TRAININGBOT_H

#include <iostream>

const int botShuxing[]{
    0, 0, 0, 10000, 10000, 0, 0, 0, 0, 0, 0, 20
};

inline void trainingBot(Player player)
{
    Entity bot;
    bot.name = "训练假人";
    for (int i = 4; i <= 14; i++)
    {
        bot.data[i]->value = botShuxing[i - 3];
    }
    while (true)
    {
        system("cls");
        std::cout << "训练假人属性:" << std::endl << std::endl;
        std::cout << "1.攻击力: " << bot.getData(4) << std::endl;
        std::cout << "2.防御力: " << bot.getData(5) << std::endl;
        std::cout << "3.生命值: " << bot.getData(6) << std::endl;
        std::cout << "4.生命上限: " << bot.getData(7) << std::endl;
        std::cout << "5.伤害加成%: " << bot.getData(8) << std::endl;
        std::cout << "6.伤害减免%: " << bot.getData(9) << std::endl;
        std::cout << "7.闪避概率%: " << bot.getData(10) << std::endl;
        std::cout << "8.吸血概率%: " << bot.getData(11) << std::endl;
        std::cout << "9.吸血比率%: " << bot.getData(12) << std::endl;
        std::cout << "10.暴击比率%: " << bot.getData(13) << std::endl;
        std::cout << "11.攻击速度: " << bot.getData(14) << std::endl;
        std::cout << "12.开始" << std::endl;
        std::cout << "\n请输入属性序号:" << std::endl;
        int choice = getChoice(1, 12);
        if (choice == 12)
        {
            bot.data[6]->value = bot.getData(7);
            createFightArea(player, "训练假人");
            fight(player, bot, player);
            continue;
        }
        if (choice == -1) continue;
        if (choice == -2) return;
        std::cout << "请输入属性值:" << std::endl;
        int value = getChoice(0, 2147483647);
        if (value == -1 || value == -2) continue;

        bot.data[choice + 3]->value = value;
        if (choice == 3) bot.data[4]->value = value;
        if (choice == 4) bot.data[3]->value = value;
    }
}

#endif //FOREVERLAND_TRAININGBOT_H
