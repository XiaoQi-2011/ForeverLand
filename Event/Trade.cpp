#include "Trade.h"
#include "../Lib/Item.h"

void reflashShenmi(Player& player)
{
    std::stringstream ss;
    for (int i = 0; i < 6; i++)
    {
        int id = Random(0, ITEM_NUM - 1);
        if (init_item[id].type == "op" || init_item[id].quality != i + 1 || init_item[id].JB_value == -1)
        {
            i--;
            continue;
        }
        shenmiProduct[i] = id;
        ss << id << "$";
    }
    player.strData[1]->value = ss.str();
}

void initShenmi(Player& player)
{
    std::string str = player.getStrData(1);
    if (str == "empty")
    {
        reflashShenmi(player);
        return;
    }
    std::vector<std::string> IDs = split(str, '$');
    for (int i = 0; i < IDs.size(); i++)
    {
        shenmiProduct[i] = stoi(IDs[i]);
    }
}

void reflashZahuo(Player& player)
{
    std::stringstream ss;
    for (int i = 0; i < 5; i++)
    {
        int id = Random(0, ITEM_NUM - 1);
        if (init_item[id].type == "op" || init_item[id].quality >= 6 || init_item[id].JB_value == -1)
        {
            i--;
            continue;
        }
        zahuoProduct[i] = id;
        ss << id << "$";
    }
    player.strData[0]->value = ss.str();
}

void initZahuo(Player& player)
{
    std::string str = player.getStrData(0);
    if (str == "empty")
    {
        reflashZahuo(player);
        return;
    }
    std::vector<std::string> IDs = split(str, '$');
    for (int i = 0; i < IDs.size(); i++)
    {
        zahuoProduct[i] = stoi(IDs[i]);
    }
}

TradeChoice getTradeChoice()
{
    std::string input;
    std::getline(std::cin, input);
    if (input.empty()) return TradeChoice(-1);
    if (input == "back") return TradeChoice(-2);
    std::vector<std::string> choices = split(input, ' ');
    TradeChoice choice;
    if (choices.size() != 2) goto wrong;
    for (int i = 0; i < 2; i++)
    {
        if (!isNumber(choices[i])) goto wrong;
        int choiceI = stoi(choices[i]);
        switch (i)
        {
        case 0:
            {
                if (choiceI < 1 || choiceI > tradeRange) goto NumWrong;
                choice.index = choiceI;
                break;
            }
        case 1:
            {
                if (choiceI < 1 || choiceI > itemRange[choice.index - 1]) goto NumWrong;
                choice.itemIndex = choiceI;
                break;
            }
        default:
            break;
        }
    }
    return choice;
wrong:
    std::cout << "输入错误!" << std::endl;
    system("pause");
    return TradeChoice(-1);
NumWrong:
    std::cout << "输入数据不在范围内!" << std::endl;
    system("pause");
    return TradeChoice(-1);
}

bool trade(Player& player, int itemId, int count, bool isBuy, float override)
{
    int jb_value = (int)(init_item[itemId].JB_value * override) * count;
    int zs_value = (int)(init_item[itemId].ZS_value * override) * count;
    if (isBuy)
    {
        if (player.getData(2) < jb_value || player.getData(3) < zs_value)
        {
            printf("货币不足！需要: \n");
            printf("%d/%d金币 ", player.getData(2), jb_value);
            if (zs_value > 0)
            {
                printf("%d/%d钻石", player.getData(3), zs_value);
            }
            printf("\n");
            system("pause");
            return false;
        }
        player.data[2]->value -= jb_value;
        player.data[3]->value -= zs_value;
        player.items[itemId]->count += count;
        printf("购买成功\n+%s×%d\n", init_item[itemId].name.c_str(), count);
        system("pause");
    }
    else
    {
        if (player.getItem(itemId) < count)
        {
            printf("你没有那么多的 %s！\n", init_item[itemId].name.c_str());
            system("pause");
            return false;
        }
        player.data[2]->value += jb_value;
        player.data[3]->value += zs_value;
        player.items[itemId]->count -= count;
        printf("出售成功\n");
        printf("+%d金币 +%d钻石\n", jb_value, zs_value);
        system("pause");
    }
    return true;
}

int getAllCount(Player& player, int itemId, bool isBuy, float override)
{
    if (isBuy)
    {
        int jb_value = init_item[itemId].JB_value * override;
        int zs_value = init_item[itemId].ZS_value * override;
        int jb_count = jb_value > 0 ? player.getData(2) / jb_value : 1000000000;
        int zs_count = zs_value > 0 ? player.getData(3) / zs_value : 1000000000;
        int count = std::min(jb_count, zs_count);
        return count;
    }
    else
    {
        return player.getItem(itemId);
    }
}

void TradeMenu(Player& player)
{
Trade:
    system("cls");
    printf("--交易区--\n");
    printf("[金币] %d\n[钻石] %d\n\n", player.getData(2), player.getData(3));

    printf("1.-----药水女巫-----\n");
    printf("> 新酿的药水，确定不来一点?\n");
    for (int i = 57; i <= 62; i++)
    {
        int jb_value = init_item[i].JB_value * 1, zs_value = init_item[i].ZS_value * 1;
        printf("%d.%s %d金币 ", i - 56, init_item[i].name.c_str(), jb_value);
        if (zs_value > 0)
        {
            printf("%d钻石 ", zs_value);
        }
        printf("%s(出售)\033[0m\n", buyColor.c_str());
    }
    printf("------------------\n\n");

    printf("2.----矿物收藏者----\n");
    printf("> 我就喜欢闪闪发亮的东西\n");
    for (int i = 0; i <= 8; i++)
    {
        int jb_value = init_item[i].JB_value * 0.9, zs_value = init_item[i].ZS_value * 0.9;
        printf("%d.%s %d金币 ", i + 1, init_item[i].name.c_str(), jb_value);
        if (zs_value > 0)
        {
            printf("%d钻石 ", zs_value);
        }
        printf("%s(收购)\033[0m\n", sellColor.c_str());
    }
    printf("--------------------\n\n");

    printf("3.-----冒险家协会-----\n");
    printf("> 我们需要大量的怪物材料\n");
    for (int i = 63; i <= 69; i++)
    {
        int jb_value = init_item[i].JB_value * 0.9, zs_value = init_item[i].ZS_value * 0.9;
        printf("%d.%s %d金币 ", i - 62, init_item[i].name.c_str(), jb_value);
        if (zs_value > 0)
        {
            printf("%d钻石 ", zs_value);
        }
        printf("%s(收购)\033[0m\n", sellColor.c_str());
    }
    printf("--------------------\n\n");

    printf("4.-----时光老人-----\n");
    printf("> 时间真是一种奇妙的东西，你摸不着它，却要每天都看着它流逝\n");
    for (int i = 98; i <= 101; i++)
    {
        int jb_value = init_item[i].JB_value * 1, zs_value = init_item[i].ZS_value * 1;
        printf("%d.%s %d金币 ", i - 97, init_item[i].name.c_str(), jb_value);
        if (zs_value > 0)
        {
            printf("%d钻石 ", zs_value);
        }
        printf("%s(出售)\033[0m\n", buyColor.c_str());
    }
    printf("--------------------\n\n");

    int seconds = zahuoFlash * zahuoFlashTime - second;
    printf("5.----杂货铺(%dmin%ds 后刷新)----\n", seconds / 60, seconds % 60);
    printf("> 瞧一瞧看一看，走过路过不要错过\n");
    for (int i = 0; i < 5; i++)
    {
        int jb_value = init_item[zahuoProduct[i]].JB_value * 1.2, zs_value = init_item[zahuoProduct[i]].ZS_value * 1.1;
        printf("%d.%s %d金币 ", i + 1, init_item[zahuoProduct[i]].name.c_str(), jb_value);
        if (zs_value > 0)
        {
            printf("%d钻石 ", zs_value);
        }
        printf("%s(出售)\033[0m\n", buyColor.c_str());
    }
    printf("-------------------------------\n\n");

    seconds = shenmiFlash * shenmiFlashTime - second;
    printf("\033[1;35m6.----神秘商人(%dmin%ds 后刷新)----\n", seconds / 60, seconds % 60);
    printf("> ???\n");
    for (int i = 0; i < 6; i++)
    {
        int jb_value = init_item[shenmiProduct[i]].JB_value * 1.4, zs_value = init_item[shenmiProduct[i]].ZS_value *
                1.1;
        printf("\033[1;35m%d.%s %d金币 ", i + 1, init_item[shenmiProduct[i]].name.c_str(), jb_value);
        if (zs_value > 0)
        {
            printf("%d钻石 ", zs_value);
        }
        printf("%s(出售)\033[0m\n", buyColor.c_str());
    }
    printf("\033[1;35m--------------------------------\033[0m\n\n");


    printf("请输入(商人序号 物品序号): \n");
    TradeChoice choice = getTradeChoice();
    if (choice.mode == -2) return;
    if (choice.mode == -1) goto Trade;
    printf("请输入物品数量(all为全买或全卖): \n");
    std::string input;
    int count = getChoice(1, 2147483647, input, {"all"});
    if (count == -2 || count == -1) goto Trade;
    switch (choice.index)
    {
    case 1:
        {
            int itemId = choice.itemIndex + 56;
            if (input == "all")
            {
                count = getAllCount(player, itemId, true);
            }
            trade(player, itemId, count, true);
            break;
        }
    case 2:
        {
            int itemId = choice.itemIndex - 1;
            if (input == "all")
            {
                count = getAllCount(player, itemId, false, 0.9);
            }
            trade(player, itemId, count, false, 0.9);
            break;
        }
    case 3:
        {
            int itemId = choice.itemIndex + 62;
            if (input == "all")
            {
                count = getAllCount(player, itemId, false, 0.9);
            }
            trade(player, itemId, count, false, 0.9);
            break;
        }
    case 4:
        {
            int itemId = choice.itemIndex + 97;
            if (input == "all")
            {
                count = getAllCount(player, itemId, true);
            }
            trade(player, itemId, count, true);
            break;
        }
    case 5:
        {
            int itemId = zahuoProduct[choice.itemIndex - 1];
            if (input == "all")
            {
                count = getAllCount(player, itemId, true, 1.2);
            }
            trade(player, itemId, count, true, 1.1);
            break;
        }
    case 6:
        {
            int itemId = shenmiProduct[choice.itemIndex - 1];
            if (input == "all")
            {
                count = getAllCount(player, itemId, true, 1.4);
            }
            trade(player, itemId, count, true, 1.1);
            break;
        }
    }
    goto Trade;
}
