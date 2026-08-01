#ifndef ITEM_H
#define ITEM_H

#define ITEM_NUM 146

#include <string>
#include <vector>
#include "Color.h"

const std::string showQualityWhiteList[] =
{
    "chess",
    "equipment_helmet",
    "equipment_sword",
    "equipment_pickaxe",
    "equipment_armor",
    "equipment_accessory",
    "equipment_offhand"
};

const std::pair<std::string, std::string> item_quality[] = {
    {"[普通]", "\033[1;30m"},
    {"[良好]", "\033[0;37m"},
    {"[稀有]", "\033[1;36m"},
    {"[史诗]", "\033[1;35m"},
    {"[传说]", "\033[0;33m"},
    {"[神话]", "\033[0;31m\033[5;31m"},
    {"[神器]", "\033[1;31m\033[5;31;%dm"},
};

struct Colors {
    std::vector<color> colors;

    enum Type {
        shenqi,
        Gradient,
        Normal
    } type;

    Colors() = default;
    Colors(std::vector<color> colors, Type type) {
        this->colors = std::move(colors);
        this->type = type;
    }

    color* operator[] (int index) {
        return &colors[index];
    }

    void paint(std::string& name, std::string& introduce) {
        switch (type) {
            case Gradient: {
                name = getGradientString(colors[0], colors[1], name);
                introduce = getGradientString(colors[2], colors[3], introduce);
                break;
            }
            case shenqi: {
                break;
            }
            case Normal: {
                name = getColor(colors[0]) + name + "\033[0m";
                introduce = getColor(colors[1]) + introduce + "\033[0m";
                break;
            }
        }
    }

};

struct Item
{
    struct item
    {
        std::string name, introduce;
        std::string type;
        int count = 0;
        int JB_value = 0, ZS_value = 0;
        int quality = 0, jie = 0;
        int back_ground = 0;
        Colors color;

        item() = default;

        // 初始化物品专用
        item(std::string name, std::string introduce, int count, int JB_value, int ZS_value, const std::string& type, int quality,
             int jie = 0, Colors color = {})
        {
            this->color = color;
            this->name = std::move(name);
            this->introduce = std::move(introduce);
            this->type = type;
            this->count = count;
            this->JB_value = JB_value;
            this->ZS_value = ZS_value;
            this->quality = quality;
            this->jie = jie;
            // 显示品质
            bool isShow = false;
            for (auto& qualities : showQualityWhiteList)
            {
                if (qualities == type)
                {
                    isShow = true;
                    break;
                }
            }
            if (quality < 7)
            {
                this->name = item_quality[quality - 1].second + this->name;
                if (isShow) this->name += item_quality[quality - 1].first;
                this->name += "\033[0m";
            }
            // 神器处理
            if (quality == 7)
            {
                this->back_ground = color[0]->cmdColor;
                char colour[100];
                sprintf(colour, item_quality[6].second.c_str(), back_ground);
                std::string color = colour;
                this->name = color + this->name;
                if (isShow) this->name += item_quality[6].first;
                if (jie > 0) this->name += "[" + std::to_string(jie) + "阶]";
                this->name += "\033[0m";
                this->introduce = "\033[" + std::to_string(back_ground - 10) + "m" + this->introduce + "\033[0m";
            }
            if (quality == 8)
            {
                if (isShow) this->name += item_quality[6].first;
                if (jie > 0) this->name += "[" + std::to_string(jie) + "阶]";
                if (!type.starts_with("equipment")) color.paint(this->name, this->introduce);
            }
        }
    } items[ITEM_NUM];

    Item() = default;

    item* operator[](int index)
    {
        return &items[index];
    }

    void init(const item item[], bool initCount = false)
    {
        for (int i = 0; i < ITEM_NUM; i++)
        {
            if (initCount)
            {
                items[i].count = item[i].count;
            }
            items[i].name = item[i].name;
            items[i].introduce = item[i].introduce;
            items[i].type = item[i].type;
            items[i].JB_value = item[i].JB_value;
            items[i].ZS_value = item[i].ZS_value;
            items[i].quality = item[i].quality;
        }
    }

    void pushObject(std::vector<std::pair<std::string, int>>& itemList, int i, bool introduce) const
    {
        std::string object = items[i].name + "×" + std::to_string(items[i].count);
        if (introduce)
        {
            object += "\n" + items[i].introduce;
        }
        itemList.emplace_back(object, i);
    }

    std::vector<std::pair<std::string, int>> getItemList(std::vector<std::string> types, bool introduce)
    {
        std::vector<std::pair<std::string, int>> itemList;
        for (int i = 0; i < ITEM_NUM; i++)
        {
            if (items[i].count <= 0) continue;
            if (types[0] != "all")
            {
                for (auto& type : types)
                {
                    if (items[i].type.starts_with(type))
                    {
                        pushObject(itemList, i, introduce);
                        break;
                    }
                }
            }
            else
            {
                pushObject(itemList, i, introduce);
            }
        }
        return itemList;
    }
};

/*
 * ==合成所需材料数量==
   头盔: 10
   护甲: 20
   剑: 8
   镐: 12
   --回收价值减半--
*/

inline Item::item (&getInitItem())[ITEM_NUM]
{
    static Item::item init_item[]{
        Item::item("石头", "普通的石头", 0, 1, 0, "mineral", 1),
        Item::item("铜锭", "最基础的金属", 0, 5, 0, "mineral", 2),
        Item::item("铁锭", "最常见的金属", 0, 10, 0, "mineral", 2),
        Item::item("银锭", "银色的表面闪着幽光", 0, 20, 0, "mineral", 3),
        Item::item("铂金锭", "白金色的光泽中散发着尊贵的气息", 0, 30, 0, "mineral", 4),
        Item::item("钛金锭", "似乎有点像黄金，但是看去发现其表面上闪着蓝紫绿交错的绚烂光芒 ", 0, 40, 0, "mineral", 4),
        Item::item("魔法钻石", "蕴含着强大魔力的钻石，闪耀着紫色的光芒", 0, 50, 5, "mineral", 5),
        Item::item("远古合金锭", "来自远古时期的合金，但其硬度却堪比现代金属", 0, 150, 20, "mineral", 5),
        Item::item("神秘锭", "没人知道它来自哪里，似乎只存在于传说之中", 0, 300, 30, "mineral", 6),

        Item::item("石剑", "", 1, 8, 0, "equipment_sword", 1),
        Item::item("石镐", "", 1, 12, 0, "equipment_pickaxe", 1),

        Item::item("铜头盔", "", 0, 110, 0, "equipment_helmet", 2), //5*10
        Item::item("铜护甲", "", 0, 220, 0, "equipment_armor", 2), //5*20
        Item::item("铜剑", "", 0, 88, 0, "equipment_sword", 2), //5*8
        Item::item("铜镐", "", 0, 132, 0, "equipment_pickaxe", 2), //5*12

        Item::item("铁头盔", "", 0, 200, 0, "equipment_helmet", 2),
        Item::item("铁护甲", "", 0, 400, 0, "equipment_armor", 2),
        Item::item("铁剑", "", 0, 160, 0, "equipment_sword", 2),
        Item::item("铁镐", "", 0, 240, 0, "equipment_pickaxe", 2),

        Item::item("银头盔", "", 0, 400, 0, "equipment_helmet", 3),
        Item::item("银护甲", "", 0, 800, 0, "equipment_armor", 3),
        Item::item("银剑", "", 0, 320, 0, "equipment_sword", 3),
        Item::item("银镐", "", 0, 480, 0, "equipment_pickaxe", 3),

        Item::item("铂金头盔", "", 0, 600, 0, "equipment_helmet", 4),
        Item::item("铂金护甲", "", 0, 1200, 0, "equipment_armor", 4),
        Item::item("铂金剑", "", 0, 480, 0, "equipment_sword", 4),
        Item::item("铂金镐", "", 0, 720, 0, "equipment_pickaxe", 4),

        Item::item("钛金头盔", "", 0, 800, 0, "equipment_helmet", 4),
        Item::item("钛金护甲", "", 0, 1600, 0, "equipment_armor", 4),
        Item::item("钛金剑", "", 0, 640, 0, "equipment_sword", 4),
        Item::item("钛金镐", "", 0, 960, 0, "equipment_pickaxe", 4),

        Item::item("魔钻头盔", "", 0, 1000, 110, "equipment_helmet", 5),
        Item::item("魔钻护甲", "", 0, 2000, 220, "equipment_armor", 5),
        Item::item("魔钻剑", "", 0, 800, 88, "equipment_sword", 5),
        Item::item("魔钻镐", "", 0, 1200, 132, "equipment_pickaxe", 5),

        Item::item("远古合金头盔", "", 0, 3000, 390, "equipment_helmet", 5),
        Item::item("远古合金护甲", "", 0, 6000, 780, "equipment_armor", 5),
        Item::item("远古合金剑", "", 0, 2600, 312, "equipment_sword", 5),
        Item::item("远古合金镐", "", 0, 3700, 468, "equipment_pickaxe", 5),

        Item::item("神秘头盔", "", 0, 3000, 300, "equipment_helmet", 6),
        Item::item("神秘护甲", "", 0, 6000, 600, "equipment_armor", 6),
        Item::item("神秘剑", "", 0, 2400, 240, "equipment_sword", 6),
        Item::item("神秘镐", "", 0, 3600, 360, "equipment_pickaxe", 6),

        Item::item("一阶灵石", "使用后+100经验值", 0, 50, 0, "lingshi", 1),
        Item::item("二阶灵石", "使用后+200经验值", 0, 100, 0, "lingshi", 2),
        Item::item("三阶灵石", "使用后+300经验值", 0, 150, 0, "lingshi", 2),
        Item::item("四阶灵石", "使用后+400经验值", 0, 200, 0, "lingshi", 3),
        Item::item("五阶灵石", "使用后+500经验值", 0, 250, 0, "lingshi", 3),
        Item::item("六阶灵石", "使用后+600经验值", 0, 300, 5, "lingshi", 4),
        Item::item("七阶灵石", "使用后+700经验值", 0, 350, 10, "lingshi", 4),
        Item::item("八阶灵石", "使用后+800经验值", 0, 400, 15, "lingshi", 5),
        Item::item("九阶灵石", "使用后+900经验值", 0, 550, 20, "lingshi", 5),
        Item::item("十阶灵石", "使用后+1000经验值", 0, 600, 25, "lingshi", 6),

        Item::item("铁质宝箱", "获得1个[良好]品质物品", 0, 100, 0, "chest", 2),
        Item::item("金质宝箱", "获得1个[稀有]品质物品", 0, 200, 0, "chest", 3),
        Item::item("钻石宝箱", "获得1个[史诗]品质物品", 0, 300, 10, "chest", 4),
        Item::item("远古宝箱", "获得1个[传说]品质物品", 0, 400, 20, "chest", 5),

        Item::item("小型治疗药水", "使用后 生命值+50", 0, 50, 0, "potion", 2),
        Item::item("大型治疗药水", "使用后 生命值+100", 0, 100, 0, "potion", 3),
        Item::item("小型力量药水", "使用后 伤害加成+10%", 0, 200, 0, "potion", 2),
        Item::item("大型力量药水", "使用后 伤害加成+20%", 0, 0, 20, "potion", 3),
        Item::item("小型抗性药水", "使用后 伤害减免+5%", 0, 300, 0, "potion", 2),
        Item::item("大型抗性药水", "使用后 伤害减免+10%", 0, 0, 30, "potion", 3),

        Item::item("史莱姆凝胶", "黏糊糊的绿色胶状物", 0, 3, 0, "capture", 1),
        Item::item("哥布林牙齿", "其坚硬程度能咬碎石头", 0, 5, 0, "capture", 2),
        Item::item("沙化枯骨", "风干的骨头，拥有着微量的魔力", 0, 10, 0, "capture", 2),
        Item::item("古代银币", "中世纪贵族们的最爱", 0, 15, 0, "capture", 3),
        Item::item("天空棱镜", "一块酷似棱镜的石头，在阳光下闪着五彩斑斓的光辉", 0, 20, 0, "capture", 3),
        Item::item("冰海珍珠", "来自冰海深处的珍珠，鲸王们用它做成象征永恒的王冠", 0, 25, 3, "capture", 4),
        Item::item("龙骨", "赤金色的骨头闪耀着金属光泽，彰显着那个种族的强大", 0, 50, 7, "capture", 4),
        Item::item("玄武石", "玄武国的特产，铁黑色的石头上闪着淡淡的光泽", 0, 100, 10, "capture", 5),
        Item::item("测试物品", "", 0, -1, -1, "op", 0),
        Item::item("测试物品", "", 0, -1, -1, "op", 0),

        Item::item("史莱姆手镯", "果冻般的质感", 0, 60, 0, "equipment_accessory", 2),
        Item::item("兽牙项链", "用兽牙串成的项链", 0, 100, 0, "equipment_accessory", 3),
        Item::item("法老权杖(副手)", "法老王的权杖，象征着无上的权威", 0, 200, 0, "equipment_offhand", 3),
        Item::item("吸血鬼戒指", "吸血鬼伯爵的戒指，戒指上的红色宝石中仿佛流淌着鲜红的血液", 0, 300, 0, "equipment_accessory", 4),
        Item::item("堕天使之翼", "灰色的翅膀上散发着堕落的气息", 0, 400, 0, "equipment_accessory", 4),
        Item::item("冰晶皇冠", "鲸王的王冠，通体冰蓝的表面上流淌着水晶般的质感", 0, 500, 45, "equipment_accessory", 5),
        Item::item("贤者之石", "由龙王骸骨炼成的顶级炼金术产物", 0, -1, -1, "material", 6),
        Item::item("暗影碎片", "闪现着淡淡的蓝色或紫色的光，用于合成「魔刀千刃」", 0, -1, -1, "material", 6),
        Item::item("测试物品", "", 0, -1, -1, "op", 0),
        Item::item("测试物品", "", 0, -1, -1, "op", 0),

        Item::item("战神之刃", "\"告诉我，神...会流血吗？\"", 0, 2400, 264, "equipment_sword", 5),
        Item::item("战神之刃<觉醒>", "\"告诉我，神...会流血吗？\"", 0, -1, -1, "equipment_sword", 6),
        Item::item("天顶剑", "至天至极之剑！", 0, 7496, 640, "equipment_sword", 6),

        Item::item("天丛云·白王圣剑", "别名[草薙剑]，由白王圣骸制成\n"
                   "刀身呈菖蒲叶型太刀，常态隐没在云雾白光中，周身缠绕云气\n"
                   "出鞘化作银白色电光，切割轨迹留白光残影，肉眼难以捕捉轨迹\n"
                   "一刀可斩断万物，其锋利程度天下无双", 0, -1, -1, "equipment_sword", 7, 1,
                   {{{47}}, Colors::shenqi}),
        Item::item("昆古尼尔·命运之矛", "众神之王奥丁的配枪\n"
                   "由世界树的枝干制成，形状扭曲，如同折断的古树枝条，枪身流转着金色流光\n"
                   "长枪掷出，锁定命运，无视规则，绝对命中\n"
                   "对流星许愿吧！因为以昆古尼尔起誓的诺言必定应验\n"
                   "[特殊]使用此武器对方将无法闪避", 0, -1, -1, "equipment_sword", 7, 2,
                   {{{102}}, Colors::shenqi}),
        Item::item("七宗罪", "“凡王之血，必以剑终”\n"
                   "炼金术的巅峰神器\n"
                   "内置七柄刀剑，分别为傲慢，妒忌，暴怒，懒惰，贪婪，饕餮，色欲\n"
                   "七柄刀剑收纳于漆黑炼金刀匣，匣身镌刻古老铭文\n"
                   "七把同时出鞘，可展开炼金领域「青铜炼狱·罪与罚」\n"
                   "龙的戾气流转于刃身，渴望用利刃终结诸王宿命", 0, -1, -1, "equipment_sword", 7, 3,
                   {{{41}}, Colors::shenqi}),
        Item::item("魔刀千刃", "原是神锻国的秘宝\n"
                   "刀刃由上千块碎片组成,黑色刀柄半截刀身\n"
                   "刀身上的蓝色条纹,显现出恶灵的图案,闪现着淡淡的蓝色或紫色的光\n"
                   "只有条纹发光,才可以发挥出强大的力量\n"
                   "“只攻不防,天下无双,魔刀千刃”\n"
                   "要小心了!\n"
                   "深渊里的恶灵无时无刻不在触动\n"
                   "他们释放的黑洞吞噬世间的一切", 0, -1, -1, "equipment_sword", 7, 3,
                   {{{105}}, Colors::shenqi}),
        Item::item("深渊·诅咒之戒", "来自深渊的目光正在凝视着你...", 0, -1, -1, "equipment_accessory", 6),
        Item::item("创世神之心", "你获得了来自Minecraft创世神的认可", 0, -1, -1, "material", 6),

        Item::item("小型金币福袋", "打开可获得5~15金币", 0, 10, 0, "fudai_jb", 2),
        Item::item("中型金币福袋", "打开可获得40~60金币", 0, 50, 0, "fudai_jb", 3),
        Item::item("大型金币福袋", "打开可获得90~110金币", 0, 100, 0, "fudai_jb", 4),
        Item::item("小型钻石福袋", "打开可获得1~5钻石", 0, 0, 3, "fudai_zs", 3),
        Item::item("中型钻石福袋", "打开可获得5~15钻石", 0, 0, 10, "fudai_zs", 4),
        Item::item("大型钻石福袋", "打开可获得40~60钻石", 0, 0, 50, "fudai_zs", 5),

        Item::item("杂货铺刷新券", "可用于刷新杂货铺", 0, 200, 20, "shuaxin_zahuo", 4),
        Item::item("神秘商人刷新券", "可用于刷新神秘商人", 0, 300, 40, "shuaxin_shenmi", 5),
        Item::item("世界Boss刷新券", "可用于刷新世界Boss", 0, 400, 60, "shuaxin_boss", 6),

        Item::item("体力瓶", "用于回复挖矿损失的体力", 0, 15, 0, "consumables", 3),
        Item::item("装备碎片", "通过分解装备获得", 0, -1, -1, "material", 3),
        Item::item("化神石", "可用于突破神级瓶颈", 0, -1, -1, "consumables_more", 6),

        Item::item("XiaoQiのSword", "--来自开发者的赠礼--\n"
                               "by XiaoQi", 0, -1, -1, "equipment_sword", 8, 5,
                               {{{"#14fbff"}, {"#90f240"}, {"#14fbff"}, {"#90f240"}}, Colors::Gradient}),
        Item::item("屠龙刀", "村长家的传世神器\n"
                                    "世世代代流传下来\n"
                                    "只有真正的勇者才能使用\n"
                                    "刃断苍溟，锋镇八荒\n"
                                    "[成长型武器]", 0, -1, -1, "equipment_sword", 8, 0,
                    {{{"#FEAF06"}, {"#FEAF07"}, {"#DEAC3F"}, {"#FEAF06"}}, Colors::Gradient}),

        Item::item("杂草", "没有任何用处的杂草", 0, 1, 0, "immortal_herb", 1),

        Item::item("凝露草[凡阶]", "[凡阶仙草]\n淬体固本，入门炼药主料", 0, 50, 0, "immortal_herb", 2),
        Item::item("青纹芝[凡阶]", "[凡阶仙本]\n滋养气血，治疗外伤", 0, 50, 0, "immortal_herb", 2),
        Item::item("紫河藤[凡阶]", "[凡阶仙草]\n辅助稳固初入修为", 0, 50, 0, "immortal_herb", 2),
        Item::item("月华草[凡阶]", "[凡阶仙草]\n吸纳夜色灵气，提升修炼效率", 0, 50, 0, "immortal_herb", 2),

        Item::item("九曲灵参[灵阶]", "[灵阶仙草]\n洗伐经脉杂质", 0, 100, 0, "immortal_herb", 3),
        Item::item("冰魄雪莲[灵阶]", "[灵阶仙草]\n极寒灵药，压制心魔、去火毒", 0, 100, 0, "immortal_herb", 3),
        Item::item("赤炎朱果[灵阶]", "[灵阶仙草]\n火属性灵草，大幅暴涨灵力", 0, 100, 0, "immortal_herb", 3),
        Item::item("星辰草[灵阶]", "[灵阶仙草]\n吸收星力，突破瓶颈", 0, 100, 0, "immortal_herb", 3),

        Item::item("九叶玄参[玄阶]", "[玄阶仙草]\n净化魔气，祛除丹毒", 0, 150, 0, "immortal_herb", 4),
        Item::item("幽冥鬼芝[玄阶]", "[玄阶仙草]\n阴属性灵药，魔道修士常用", 0, 150, 0, "immortal_herb", 4),
        Item::item("血龙参[玄阶]", "[玄阶仙草]\n淬炼肉身，增强精血", 0, 150, 0, "immortal_herb", 4),
        Item::item("阴阳同心草[玄阶]", "[玄阶仙草]\n一阴一阳成对生长，炼制合道丹药", 0, 150, 0, "immortal_herb", 4),

        Item::item("万年龙涎草[地阶]", "[地阶仙草]\n龙族灵气滋养而生，助修士凝丹", 0, 200, 5, "immortal_herb", 5),
        Item::item("涅槃灵莲[地阶]", "[地阶仙草]\n可使濒死修士重塑肉身", 0, 200, 5, "immortal_herb", 5),
        Item::item("补天芝[地阶]", "[地阶仙草]\n使用天地灵气修补道基裂痕", 0, 200, 5, "immortal_herb", 5),
        Item::item("七色仙兰[地阶]", "[地阶仙草]\n调和五行灵气，杜绝走火入魔", 0, 200, 5, "immortal_herb", 5),

        Item::item("九转还魂草[天阶]", "[天阶仙草]\n断肢重生，吊住一缕残魂", 0, 250, 10, "immortal_herb", 6),
        Item::item("混沌青莲[天阶]", "[天阶仙草]\n先天灵根，造化至宝", 0, 250, 10, "immortal_herb", 6),
        Item::item("扶桑神叶[天阶]", "[天阶仙草]\n日之精华，铸就纯阳道体", 0, 250, 10, "immortal_herb", 6),
        Item::item("太阴神芝[天阶]", "[天阶仙草]\n月华本源，修炼太阴功法必备", 0, 250, 10, "immortal_herb", 6),

        Item::item("废丹", "炼丹失败的产物", 0, 10, 0, "alchemy", 1),

        Item::item("淬体丹[凡阶]", "淬炼肉身，提升肉身力量\n[效果] 攻击力+3", 0, 400, 0, "elixir", 2),
        Item::item("烈血丹[灵阶]", "大幅增幅力量，强化肌肉与精血爆发力\n[效果] 攻击力+5", 0, 1200, 0, "elixir", 3),
        Item::item("龙血丹[玄阶]", "塑肉身筋骨，服用后力量成倍暴涨，近战战力质变\n[效果] 攻击力+8 伤害加成%+1", 0, 2400, 0, "elixir", 4),
        Item::item("龙涎丹[地阶]", "龙族力量加持，肉身力量堪比妖兽，长期服用固化肉身上限\n[效果] 攻击力+12 伤害加成%+2 暴击比率%+1", 0, 6000, 300, "elixir", 5),
        Item::item("纯阳焚天丹[天阶]", "铸就纯阳战体，力量突破法则限制\n[效果] 攻击力+16 伤害加成%+3 暴击比率%+2", 0, 9000, 360, "elixir", 6),

        Item::item("厚甲丹[凡阶]", "皮肉增厚，降低物理外伤伤害\n[效果] 防御力+2", 0, 400, 0, "elixir", 2),
        Item::item("磐石丹[灵阶]", "经脉皮肉强化，灵气自动形成护体屏障\n[效果] 防御力+4", 0, 1200, 0, "elixir", 3),
        Item::item("万法护身丹[玄阶]", "魔气、术法、物理伤害全方位削减\n[效果] 防御力+7", 0, 2400, 0, "elixir", 4),
        Item::item("补天道铠丹[地阶]", "修复肉身受损部位，道基化作防御壁垒\n[效果] 防御力+11 伤害减免%+1", 0, 6000, 300, "elixir", 5),
        Item::item("青莲不灭丹[天阶]", "受到致命伤害可触发一次肉身不灭护盾\n[效果] 防御力+15 伤害减免%+2", 0, 9000, 360, "elixir", 6),

        Item::item("续元丹[凡阶]", "加快伤口自愈，小幅提升气血上限\n[效果] 生命值+5", 0, 400, 0, "elixir", 2),
        Item::item("长生丹[灵阶]", "大幅提升生命上限，内伤快速修复\n[效果] 生命值+10", 0, 1200, 0, "elixir", 3),
        Item::item("延寿丹[玄阶]", "壮大本源精血，提升续航能力，延缓寿元损耗\n[效果] 生命值+15 吸血概率%+1", 0, 2400, 0, "elixir", 4),
        Item::item("涅槃灵丹[地阶]", "重伤快速复原，永久提升生命本源上限\n[效果] 生命值+20 吸血概率%+2 吸血比率%+1", 0, 6000, 300, "elixir", 5),
        Item::item("还魂造化丹[天阶]", "保留残魂复活，生命本源得到造化级增幅\n[效果] 生命值+25 吸血概率%+3 吸血比率%+2", 0, 9000, 360, "elixir", 6),

        Item::item("续力丹[凡阶]", "淬炼体质，提高耐力和体力\n[效果] 体力上限+5", 0, 400, 0, "elixir", 2),
        Item::item("聚灵丹[灵阶]", "增长灵力总量，提升法术释放威力\n[效果] 灵力上限+10", 0, 1200, 0, "elixir", 3),
        Item::item("幽冥幻隐丹[玄阶]", "气息虚化，身形半隐匿，提升闪避概率\n[效果] 闪避概率%+1", 0, 2400, 0, "elixir", 4),

    };
    return init_item;
}

#define init_item getInitItem()

#endif // ITEM_H
