#include "Fighting.h"
#include "conio.h"

void initKeys(Player& player)
{
    std::vector<std::string> keys = split(player.getStrData(2), '$');
    if (keys.empty())
    {
        player.strData[2]->value = getInitStrData()[2].value;
        return;
    }
    attackKey = keys[0][0];
    potionKey = keys[1][0];
    for (int i = 0; i < 6; i++)
    {
        potionKeys[i] = keys[i + 2][0];
    }
}

int getRealDamage(Data me, Data enemy)
{
    int damage = me[4]->value;
    damage *= (100 + me[8]->value) / 100;
    int max_damage = damage * (100 + me[13]->value) / 100;
    damage = Random(damage, max_damage);
    damage -= enemy[5]->value;
    damage = damage * (100 - enemy[9]->value) / 100;
    damage = damage < 0 ? 0 : damage;
    return damage;
}

//0:none 1:player 2:entity
int judgmentWin()
{
    if (win != 0) return win;
    if (meHealth > 0 && enemyHealth > 0) return 0;
    if (enemyHealth <= 0)
    {
        printf("\033[1;33m你成功击败[%s]，你获得了\033[0m\n", fEntity->name.c_str());
        printf("> %d经验 %d金币 %d钻石 \n", fEntity->getData(1), fEntity->getData(2), fEntity->getData(3));
        std::vector<std::pair<std::string, int>> items = fEntity->capture.getItemList(std::vector<std::string>{"all"}, false);
        //if (!items.empty()) printf(">");
        for (auto& item : items)
        {
            printf("%s\n", item.first.c_str());
            realPlayer->items[item.second]->count += fEntity->getCapture(item.second);
        }
        //printf("\n");
        realPlayer->data[1]->value += fEntity->getData(1);
        realPlayer->data[2]->value += fEntity->getData(2);
        realPlayer->data[3]->value += fEntity->getData(3);
        return 1;
    }
    if (meHealth <= 0)
    {
        printf("\033[0;31m------你死了--------\033[0m\n");
        printf("\033[0;31m你被[%s\033[0;31m]杀死了\033[0m\n", fEntity->name.c_str());
        printf("\033[0;31m-------------------\033[0m\n");
        return 2;
    }
    return 0;
}

void MainLoop()
{
    while (true)
    {
        Sleep(90);
        times++;
        if (times % 1 == 0)
        {
            if (attackCD != -1)
            {
                attackCD--;
                if (attackCD == 0)
                {
                    attackCD = -1;
                }
            }
            win = judgmentWin();
            if (win != 0)
            {
                return;
            }
        }
        if (times % 10 == 0)
        {
            if (healthCD != -1)
            {
                healthCD--;
                if (healthCD == 0)
                {
                    healthCD = -1;
                    health = 0;
                    //printf("\033[1;32m[+]\033[0m治疗药水冷却完成\n");
                }
            }
            if (strengthCD != -1)
            {
                strengthCD--;
                if (strengthCD == 0)
                {
                    fPlayer->data[8]->value -= strength;
                    strengthCD = -1;
                    strength = 0;
                    printf("\033[1;32m[+]\033[0m力量药水冷却完成\n");
                }
            }
            if (resistanceCD != -1)
            {
                resistanceCD--;
                if (resistanceCD == 0)
                {
                    fPlayer->data[9]->value -= resistance;
                    resistanceCD = -1;
                    resistance = 0;
                    printf("\033[1;32m[+]\033[0m抗性药水冷却完成\n");
                }
            }
        }
    }
}

void entityAttack()
{
    while (true)
    {
        if (fEntity->getData(14) == 0) continue;
        if (win != 0) return;
        Sleep(10000 / fEntity->getData(14));
        if (win != 0) return;
        std::string name = fEntity->name;
        int damage = getRealDamage(fEntity->data, fPlayer->data);
        int shanbi = Random(1, 100);
        if (shanbi <= fPlayer->getData(10))
        {
            printf("你闪避了[%s]的攻击\n", name.c_str());
        }
        else
        {
            meHealth -= damage;
            meHealth = meHealth < 0 ? 0 : meHealth;
            printf("[%s]攻击你造成\033[1;33m%d\033[0m伤害，\033[1;34m你的血量:\033[1;31m%d/%d ", name.c_str(), damage, meHealth,
                   fPlayer->getData(7));
            int healthP = meHealth * 100 / fPlayer->getData(7);
            std::cout << healthColors[healthP / 20] << healthP << "%\033[0m" << std::endl;
            if (win != 0)
            {
                return;
            }
            int xixue = Random(1, 100);
            if (xixue <= fEntity->getData(11))
            {
                xixue = damage * fEntity->getData(12) / 100;
                enemyHealth += xixue;
                enemyHealth = enemyHealth > fEntity->getData(7) ? fEntity->getData(7) : enemyHealth;
                printf("\033[1;31m[-][%s]吸取你\033[0;31m%d\033[1;31m血量，对方血量:\033[1;31m%d/%d\033[0m ", name.c_str(), xixue,
                       enemyHealth, fEntity->getData(7));
                healthP = enemyHealth * 100 / fEntity->getData(7);
                std::cout << healthP << "%" << std::endl;
            }
        }
    }
}

void specialEvent()
{
    if (fPlayer->getData(19) == 87)
    {
        fEntity->data[10]->value = 0;
        printf("\033[1;32m由于你手持「昆古尼尔」，对方将无法闪避\033[0m\n");
    }
}

bool fight(Player& player, Entity& entity, Player& real_player, bool isContinue)
{
    initKeys(player);
    win = 0;
    times = 0;
    escKeyPushEnable = false;

    fPlayer = &player;
    fEntity = &entity;
    realPlayer = &real_player;
    std::string name = fEntity->name;
    printf("你正在与[%s]战斗...\n\n", name.c_str());

    specialEvent();
    if (!isContinue)
    {
        strengthCD = -1;
        strength = 0;
        resistanceCD = -1;
        resistance = 0;
    }

    std::thread(entityAttack).detach();
    std::thread(MainLoop).detach();
    while (true)
    {
        if (win != 0)
        {
            std::string str;
            std::cout << "输入任意内容继续..." << std::endl;
            escKeyPushEnable = true;
            std::getline(std::cin, str);
            return win == 1;
        }
        int key = _getch();
        if (key == attackKey)
        {
            if (attackCD != -1) continue;
            int damage = getRealDamage(player.data, entity.data);
            int shanbi = Random(1, 100);
            if (shanbi <= entity.getData(10))
            {
                printf("[%s]闪避了你的攻击\n", name.c_str());
            }
            else
            {
                enemyHealth -= damage;
                enemyHealth = enemyHealth < 0 ? 0 : enemyHealth;
                printf("\033[1;34m>\033[0m你攻击了[%s]造成\033[1;33m%d\033[0m伤害，对方血量:\033[1;31m%d/%d\033[0m ", name.c_str(),
                       damage, enemyHealth, entity.getData(7));
                int healthP = enemyHealth * 100 / entity.getData(7);
                std::cout << healthP << "%" << std::endl;
                int xixue = Random(1, 100);
                if (xixue <= player.getData(11))
                {
                    xixue = damage * fPlayer->getData(12) / 100;
                    meHealth += xixue;
                    meHealth = meHealth > player.getData(7) ? player.getData(7) : meHealth;
                    printf("\033[1;31m[+]你吸取对方\033[0;31m%d\033[1;31m血量，\033[1;34m你的血量:\033[1;31m%d/%d\033[0m\n", xixue,
                           meHealth, player.getData(7));
                    //healthP = meHealth * 100 / player.getData(7);
                    //cout << healthColors[healthP / 20] << healthP << "%\033[0m" << endl;
                }
            }
            if (win != 0)
            {
                std::string str;
                std::cout << "输入任意内容继续..." << std::endl;
                escKeyPushEnable = true;
                std::getline(std::cin, str);
                return win == 1;
            }
            //Sleep(10000/fPlayer->getData(14));
            attackCD = 100 / player.getData(14);
        }
        if (key == potionKey)
        {
            printf("\033[1;35m== 药水栏 ==\033[0m\n");
            printf("1.小型治疗药水:%d\n", real_player.getItem(57));
            printf("2.大型治疗药水:%d\n", real_player.getItem(58));
            printf("3.小型力量药水:%d\n", real_player.getItem(59));
            printf("4.大型力量药水:%d\n", real_player.getItem(60));
            printf("5.小型抗性药水:%d\n", real_player.getItem(61));
            printf("6.大型抗性药水:%d\n", real_player.getItem(62));
            printf("输入序号使用药水(随时都可使用)\n");
        }
        if (escDown)
        {
            win = 3;
            printf("你已退出战斗\n");
            system("pause");
            escKeyPushEnable = true;
            return false;
        }
        // 判断 Potion Key
        bool isPotionKey = false;
        int item_id = 0;
        for (int i = 0; i < 6; i++)
        {
            if (key == potionKeys[i])
            {
                isPotionKey = true;
                item_id = i + 57;
                break;
            }
        }
        if (isPotionKey)
        {
            if (real_player.getItem(item_id) <= 0)
            {
                printf("\033[0;31m药水数量不足!\033[0m\n");
                continue;
            }
            switch (item_id)
            {
            case 57:
                {
                    if (healthCD == -1)
                    {
                        healthCD = 1;
                        health = 50;
                        real_player.items[57]->count--;
                        meHealth += health;
                        meHealth = meHealth > player.getData(7) ? player.getData(7) : meHealth;
                        printf("\033[1;31m[+]你使用了小型治疗药水 +%d生命值 (剩余%d瓶)，\033[1;34m你的血量:\033[1;31m%d/%d ",
                               health, real_player.getItem(item_id),meHealth, fPlayer->getData(7));
                        int healthP = meHealth * 100 / fPlayer->getData(7);
                        std::cout << healthColors[healthP / 20] << healthP << "%\033[0m" << std::endl;
                    }
                    else std::printf("药水冷却中，剩余%d秒\n", healthCD);
                    break;
                }
            case 58:
                {
                    if (healthCD == -1)
                    {
                        healthCD = 1;
                        health = 100;
                        real_player.items[58]->count--;
                        meHealth += health;
                        meHealth = meHealth > player.getData(7) ? player.getData(7) : meHealth;
                        printf("\033[1;31m[+]你使用了大型治疗药水 +%d生命值 (剩余%d瓶)，\033[1;34m你的血量:\033[1;31m%d/%d ",
                               health, real_player.getItem(item_id),meHealth, fPlayer->getData(7));
                        int healthP = meHealth * 100 / fPlayer->getData(7);
                        std::cout << healthColors[healthP / 20] << healthP << "%\033[0m" << std::endl;
                    }
                    else std::printf("药水冷却中，剩余%d秒\n", healthCD);
                    break;
                }
            case 59:
                {
                    if (strengthCD == -1)
                    {
                        strengthCD = 10;
                        strength = 4;
                        real_player.items[59]->count--;
                        player.data[8]->value += strength;
                        printf("\033[1;33m[+]你使用了小型力量药水 +%d%%伤害加成 (剩余%d瓶)\033[0m\n", strength,
                               real_player.getItem(item_id));
                    }
                    else std::printf("药水冷却中，剩余%d秒\n", strengthCD);
                    break;
                }
            case 60:
                {
                    if (strengthCD == -1)
                    {
                        strengthCD = 10;
                        strength = 8;
                        real_player.items[60]->count--;
                        player.data[8]->value += strength;
                        printf("\033[1;33m[+]你使用了大型力量药水 +%d%%伤害加成 (剩余%d瓶)\033[0m\n", strength,
                               real_player.getItem(item_id));
                    }
                    else std::printf("药水冷却中，剩余%d秒\n", strengthCD);
                    break;
                }
            case 61:
                {
                    if (resistanceCD == -1)
                    {
                        resistanceCD = 10;
                        resistance = 5;
                        real_player.items[61]->count--;
                        player.data[9]->value += resistance;
                        printf("\033[1;30m[+]你使用了小型抗性药水 +%d%%伤害减免 (剩余%d瓶)\033[0m\n", resistance,
                               real_player.getItem(item_id));
                    }
                    else std::printf("药水冷却中，剩余%d秒\n", resistanceCD);
                    break;
                }
            case 62:
                {
                    if (resistanceCD == -1)
                    {
                        resistanceCD = 10;
                        resistance = 10;
                        real_player.items[62]->count--;
                        player.data[9]->value += resistance;
                        printf("\033[1;30m[+]你使用了大型抗性药水 +%d%%伤害减免 (剩余%d瓶)\033[0m\n", resistance,
                               real_player.getItem(item_id));
                    }
                    else std::printf("药水冷却中，剩余%d秒\n", resistanceCD);
                    break;
                }
            }
        }
    }
}

void createFightArea(Player& player, const std::string& str)
{
    system("cls");
    printf("%s\n", str.c_str());
    initKeys(player);
    printf("按键> 攻击:%c 查看药水:%c 退出战斗:esc\n", attackKey, potionKey);
    printf("> 使用药水: ");
    for (char i : potionKeys)
    {
        std::printf("%c ", i);
    }
    std::cout << std::endl;
}
