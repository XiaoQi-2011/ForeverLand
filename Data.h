#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <sstream>
#include <iomanip>
#include <utility>
#include <filesystem>

#include "Base64.h"

using namespace std;
#define DATA_NUM 27
#define WORLDDATA_NUM 3
#define STRDATA_NUM 3
#define ITEM_NUM 104

int dayPeriod = 1;

static bool start_with(const string& str, const string& prefix) {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}
struct Data {
    struct data {
        string name;
        string type;
        int value = 0;
        data() = default;
        data(string name, int value, string type) {
            this->name = std::move(name);
            this->value = value;
            this->type = std::move(type);
        }
    } datas[DATA_NUM];

    Data() = default;
    data *operator[] (int index) {
        return &datas[index];
    }
    void init(const data data[], bool initValue = false) {
        for (int i = 0; i < DATA_NUM; i++) {
            if (initValue) {
                datas[i].value = data[i].value;
            }
            datas[i].name = data[i].name;
            datas[i].type = data[i].type;
        }
    }
};
struct WorldData{
    struct data {
        string name;
        string type;
        int value = 0;
        data() = default;
        data(string name, int value, string type) {
            this->name = std::move(name);
            this->value = value;
            this->type = std::move(type);
        }
    } datas[WORLDDATA_NUM];

    WorldData() = default;
    data *operator[] (int index) {
        return &datas[index];
    }
    void init(const data data[], bool initValue = false) {
        for (int i = 0; i < WORLDDATA_NUM; i++) {
            if (initValue) {
                datas[i].value = data[i].value;
            }
            datas[i].name = data[i].name;
            datas[i].type = data[i].type;
        }
    }
};
struct StrData {
    struct data {
        string name, type;
        string value;
        data() = default;
        data(string name, string value, string type) {
            this->name = std::move(name);
            this->value = std::move(value);
            this->type = std::move(type);
        }
    } datas[DATA_NUM];
    char split = ' ';

    StrData() = default;
    data *operator[] (int index) {
        return &datas[index];
    }
    void init(const data data[], bool initValue = false) {
        for (int i = 0; i < STRDATA_NUM; i++) {
            if (initValue) {
                datas[i].value = data[i].value;
            }
            datas[i].name = data[i].name;
            datas[i].type = data[i].type;
        }
    }
};

pair<int, int> getRealDamage(Data data) {
    int damage = data[4]->value * (100 + data[8]->value) / 100;
    int max_damage = damage * (100 + data[13]->value) / 100;
    return make_pair(damage, max_damage);
}

const string showQualityWhiteList[] =
        {
          "chess",
          "equipment_helmet",
          "equipment_sword",
          "equipment_pickaxe",
          "equipment_armor",
          "equipment_accessory",
          "equipment_offhand"
        };
const pair<string, string> item_quality[] = {
        {"[普通]", "\033[1;30m"},
        {"[良好]", "\033[0;37m"},
        {"[稀有]", "\033[1;36m"},
        {"[史诗]", "\033[1;35m"},
        {"[传说]", "\033[0;33m"},
        {"[神话]", "\033[0;31m\033[5;31m"},
        {"[神器]", "\033[1;31m\033[5;31;%dm"},
};
//use: \033color - 30 light: +8
const int colors[] = {
    8, 4, 2, 6, 1, 5, 3, 7
};
struct ITEM {
    struct item {
        string name, introduce;
        string type;
        int count = 0;
        int JB_value = 0, ZS_value = 0;
        int quality = 0, jie = 0;
        int back_ground = 0;

        item() = default;

        // 初始化物品专用
        item(string name, string introduce, int count, int JB_value, int ZS_value, string type, int quality, int back_ground = 0, int jie = 0) {
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
            for (auto & qualities : showQualityWhiteList) {
                if (qualities == type) {
                    isShow = true;
                    break;
                }
            }
            // 神器处理
            if (quality == 7) {
                this->back_ground = back_ground;
                char colour[100];
                sprintf(colour, item_quality[6].second.c_str(), back_ground);
                string color = colour;
                this->name = color + this->name;
                if (isShow) this->name += item_quality[6].first;
                if (jie > 0) this->name += "[" + to_string(jie) + "阶]";
                this->name += "\033[0m";
                this->introduce = "\033[" + to_string(back_ground - 10) + "m" + this->introduce + "\033[0m";
            } else {
                this->name = item_quality[quality - 1].second + this->name;
                if (isShow) this->name += item_quality[quality - 1].first;
                this->name += "\033[0m";
            }
        }
    } items[ITEM_NUM];

    ITEM() = default;
    item *operator[] (int index) {
        return &items[index];
    }

    void init(const item item[], bool initCount = false) {
        for (int i = 0; i < ITEM_NUM; i++) {
            if (initCount) {
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

    void pushObject(vector<pair<string, int>>& itemList, int i, bool introduce) {
        string object = items[i].name + "×" + to_string(items[i].count);
        if (introduce) {
            object += "\n" + items[i].introduce;
        }
        itemList.emplace_back(object, i);
    }
    vector<pair<string, int>> getItemList(vector<string> types, bool introduce) {
        vector<pair<string, int>> itemList;
        for (int i = 0; i < ITEM_NUM; i++) {
            if (items[i].count <= 0) continue;
            if (types[0] != "all") {
                for (auto & type : types) {
                    if (start_with(items[i].type, type)) {
                        pushObject(itemList, i, introduce);
                        break;
                    }
                }
            } else {
                pushObject(itemList, i, introduce);
            }
        }
        return itemList;
    }
};

inline const Data::data init_data[] {
        Data::data("等级", 0, "basic"),
        Data::data("经验值", 0, "basic"),
        Data::data("金币", 100, "basic"),
        Data::data("钻石", 10, "basic"),
        Data::data("攻击力", 0, "shuxing"),
        Data::data("防御力", 0, "shuxing"),
        Data::data("生命值", 20, "shuxing"),
        Data::data("生命上限", 20, "shuxing"),
        Data::data("伤害加成%", 0, "shuxing"),
        Data::data("伤害减免%", 0, "shuxing"),
        Data::data("闪避概率%", 0, "shuxing"),
        Data::data("吸血概率%", 0, "shuxing"),
        Data::data("吸血比率%", 0, "shuxing"),
        Data::data("暴击比率%", 0, "shuxing"),
        Data::data("攻击速度", 10, "shuxing"),
        Data::data("挖掘速度", 0, "shuxing"),
        Data::data("挖掘等级", 0, "shuxing"),
        Data::data("头盔装备", -1, "slot"),
        Data::data("护甲装备", -1, "slot"),
        Data::data("武器装备", -1, "slot"),
        Data::data("副手装备", -1, "slot"),
        Data::data("镐子装备", -1, "slot"),
        Data::data("饰品装备1", -1, "slot"),
        Data::data("饰品装备2", -1, "slot"),
        Data::data("饰品装备3", -1, "slot"),
        Data::data("饰品装备4", -1, "slot"),
        Data::data("神级", 0, "basic"),
};
inline const WorldData::data init_worldData[] {
        WorldData::data("无尽之塔层数", 1, "fuben_infiniteTower"),
        WorldData::data("游玩时长/s", 420, "time_second"),
        WorldData::data("游玩天数", 0, "time_day"),
};
inline const StrData::data init_strData[] {
        StrData::data("杂货铺商品", "empty", "trade_zahuo"),
        StrData::data("神秘人商品", "empty", "trade_shenmi"),
        StrData::data("按键配置", "e$r$1$2$3$4$5$6$", "key")
};
/*
 * ==合成所需材料数量==
   头盔: 10
   护甲: 20
   剑: 8
   镐: 12
   --回收价值减半--
*/

inline ITEM::item init_item[] {
    ITEM::item("石头", "普通的石头", 0, 1, 0, "mineral", 1),
    ITEM::item("铜锭", "最基础的金属", 0, 5, 0, "mineral", 2),
    ITEM::item("铁锭", "最常见的金属", 0, 10, 0, "mineral", 2),
    ITEM::item("银锭", "银色的表面闪着幽光", 0, 20, 0, "mineral", 3),
    ITEM::item("铂金锭", "白金色的光泽中散发着尊贵的气息", 0, 30, 0, "mineral", 4),
    ITEM::item("钛金锭", "似乎有点像黄金，但是看去发现其表面上闪着蓝紫绿交错的绚烂光芒 ", 0, 40, 0, "mineral", 4),
    ITEM::item("魔法钻石", "蕴含着强大魔力的钻石，闪耀着紫色的光芒", 0, 50, 5, "mineral", 5),
    ITEM::item("远古合金锭", "来自远古时期的合金，但其硬度却堪比现代金属", 0, 150, 20, "mineral", 5),
    ITEM::item("神秘锭", "没人知道它来自哪里，似乎只存在于传说之中", 0, 300, 30, "mineral", 6),

    ITEM::item("石剑", "", 1, 8, 0, "equipment_sword", 1),
    ITEM::item("石镐", "", 1, 12, 0, "equipment_pickaxe", 1),

    ITEM::item("铜头盔", "", 0, 110, 0, "equipment_helmet", 2), //5*10
    ITEM::item("铜护甲", "", 0, 220, 0, "equipment_armor", 2), //5*20
    ITEM::item("铜剑", "", 0, 88, 0, "equipment_sword", 2), //5*8
    ITEM::item("铜镐", "", 0, 132, 0, "equipment_pickaxe", 2), //5*12

    ITEM::item("铁头盔", "", 0, 200, 0, "equipment_helmet", 2),
    ITEM::item("铁护甲", "", 0, 400, 0, "equipment_armor", 2),
    ITEM::item("铁剑", "", 0, 160, 0, "equipment_sword", 2),
    ITEM::item("铁镐", "", 0, 240, 0, "equipment_pickaxe", 2),

    ITEM::item("银头盔", "", 0, 400, 0, "equipment_helmet", 3),
    ITEM::item("银护甲", "", 0, 800, 0, "equipment_armor", 3),
    ITEM::item("银剑", "", 0, 320, 0, "equipment_sword", 3),
    ITEM::item("银镐", "", 0, 480, 0, "equipment_pickaxe", 3),

    ITEM::item("铂金头盔", "", 0, 600, 0, "equipment_helmet", 4),
    ITEM::item("铂金护甲", "", 0, 1200, 0, "equipment_armor", 4),
    ITEM::item("铂金剑", "", 0, 480, 0, "equipment_sword", 4),
    ITEM::item("铂金镐", "", 0, 720, 0, "equipment_pickaxe", 4),

    ITEM::item("钛金头盔", "", 0, 800, 0, "equipment_helmet", 4),
    ITEM::item("钛金护甲", "", 0, 1600, 0, "equipment_armor", 4),
    ITEM::item("钛金剑", "", 0, 640, 0, "equipment_sword", 4),
    ITEM::item("钛金镐", "", 0, 960, 0, "equipment_pickaxe", 4),

    ITEM::item("魔钻头盔", "", 0, 1000, 110, "equipment_helmet", 5),
    ITEM::item("魔钻护甲", "", 0, 2000, 220, "equipment_armor", 5),
    ITEM::item("魔钻剑", "", 0, 800, 88, "equipment_sword", 5),
    ITEM::item("魔钻镐", "", 0, 1200, 132, "equipment_pickaxe", 5),

    ITEM::item("远古合金头盔", "", 0, 3000, 390, "equipment_helmet", 5),
    ITEM::item("远古合金护甲", "", 0, 6000, 780, "equipment_armor", 5),
    ITEM::item("远古合金剑", "", 0, 2600, 312, "equipment_sword", 5),
    ITEM::item("远古合金镐", "", 0, 3700, 468, "equipment_pickaxe", 5),

    ITEM::item("神秘头盔", "", 0, 3000, 300, "equipment_helmet", 6),
    ITEM::item("神秘护甲", "", 0, 6000, 600, "equipment_armor", 6),
    ITEM::item("神秘剑", "", 0, 2400, 240, "equipment_sword", 6),
    ITEM::item("神秘镐", "", 0, 3600, 360, "equipment_pickaxe", 6),

    ITEM::item("一阶灵石", "使用后+100经验值", 0, 50, 0, "lingshi", 1),
    ITEM::item("二阶灵石", "使用后+200经验值", 0, 100, 0, "lingshi", 2),
    ITEM::item("三阶灵石", "使用后+300经验值", 0, 150, 0, "lingshi", 2),
    ITEM::item("四阶灵石", "使用后+400经验值", 0, 200, 0, "lingshi", 3),
    ITEM::item("五阶灵石", "使用后+500经验值", 0, 250, 0, "lingshi", 3),
    ITEM::item("六阶灵石", "使用后+600经验值", 0, 300, 5, "lingshi", 4),
    ITEM::item("七阶灵石", "使用后+700经验值", 0, 350, 10, "lingshi", 4),
    ITEM::item("八阶灵石", "使用后+800经验值", 0, 400, 15, "lingshi", 5),
    ITEM::item("九阶灵石", "使用后+900经验值", 0, 550, 20, "lingshi", 5),
    ITEM::item("十阶灵石", "使用后+1000经验值", 0, 600, 25, "lingshi", 6),

    ITEM::item("铁质宝箱", "获得1个[良好]品质物品", 0, 100, 0, "chest", 2),
    ITEM::item("金质宝箱", "获得1个[稀有]品质物品", 0, 200, 0, "chest", 3),
    ITEM::item("钻石宝箱", "获得1个[史诗]品质物品", 0, 300, 10, "chest", 4),
    ITEM::item("远古宝箱", "获得1个[传说]品质物品", 0, 400, 20, "chest", 5),

    ITEM::item("小型治疗药水", "使用后 生命值+50", 0, 50, 0, "potion", 2),
    ITEM::item("大型治疗药水", "使用后 生命值+100", 0, 100, 0, "potion", 3),
    ITEM::item("小型力量药水", "使用后 伤害加成+10%", 0, 200, 0, "potion", 2),
    ITEM::item("大型力量药水", "使用后 伤害加成+20%", 0, 0, 20, "potion", 3),
    ITEM::item("小型抗性药水", "使用后 伤害减免+5%", 0, 300, 0, "potion", 2),
    ITEM::item("大型抗性药水", "使用后 伤害减免+10%", 0, 0, 30, "potion", 3),

    ITEM::item("史莱姆凝胶", "黏糊糊的绿色胶状物", 0, 3, 0, "capture", 1),
    ITEM::item("哥布林牙齿", "其坚硬程度能咬碎石头", 0, 5, 0, "capture", 2),
    ITEM::item("沙化枯骨", "风干的骨头，拥有着微量的魔力", 0, 10, 0, "capture", 2),
    ITEM::item("古代银币", "中世纪贵族们的最爱", 0, 15, 0, "capture", 3),
    ITEM::item("天空棱镜", "一块酷似棱镜的石头，在阳光下闪着五彩斑斓的光辉", 0, 20, 0, "capture", 3),
    ITEM::item("冰海珍珠", "来自冰海深处的珍珠，鲸王们用它做成象征永恒的王冠", 0, 25, 3, "capture", 4),
    ITEM::item("龙骨", "赤金色的骨头闪耀着金属光泽，彰显着那个种族的强大", 0, 50, 7, "capture", 4),
    ITEM::item("玄武石", "玄武国的特产，铁黑色的石头上闪着淡淡的光泽", 0, 100, 10, "capture", 5),
    ITEM::item("测试物品", "", 0, -1, -1, "op", 0),
    ITEM::item("测试物品", "", 0, -1, -1, "op", 0),

    ITEM::item("史莱姆手镯", "果冻般的质感", 0, 60, 0, "equipment_accessory", 2),
    ITEM::item("兽牙项链", "用兽牙串成的项链", 0, 100, 0, "equipment_accessory", 3),
    ITEM::item("法老权杖(副手)", "法老王的权杖，象征着无上的权威", 0, 200, 0, "equipment_offhand", 3),
    ITEM::item("吸血鬼戒指", "吸血鬼伯爵的戒指，戒指上的红色宝石中仿佛流淌着鲜红的血液", 0, 300, 0, "equipment_accessory", 4),
    ITEM::item("堕天使之翼", "灰色的翅膀上散发着堕落的气息", 0, 400, 0, "equipment_accessory", 4),
    ITEM::item("冰晶皇冠", "鲸王的王冠，通体冰蓝的表面上流淌着水晶般的质感", 0, 500, 45, "equipment_accessory", 5),
    ITEM::item("贤者之石", "由龙王骸骨炼成的顶级炼金术产物", 0, -1, -1, "material", 6),
    ITEM::item("暗影碎片", "闪现着淡淡的蓝色或紫色的光，用于合成「魔刀千刃」", 0, -1, -1, "material", 6),
    ITEM::item("测试物品", "", 0, -1, -1, "op", 0),
    ITEM::item("测试物品", "", 0, -1, -1, "op", 0),

    ITEM::item("战神之刃", "\"告诉我，神...会流血吗？\"", 0, 2400, 264, "equipment_sword", 5),
    ITEM::item("战神之刃<觉醒>", "\"告诉我，神...会流血吗？\"", 0, -1, -1, "equipment_sword", 6),
    ITEM::item("天顶剑", "至天至极之剑！", 0, 7496, 640, "equipment_sword", 6),

    ITEM::item("天丛云·白王圣剑", "别名[草薙剑]，由白王圣骸制成\n"
                           "刀身呈菖蒲叶型太刀，常态隐没在云雾白光中，周身缠绕云气\n"
                           "出鞘化作银白色电光，切割轨迹留白光残影，肉眼难以捕捉轨迹\n"
                           "一刀可斩断万物，其锋利程度天下无双", 0, -1, -1, "equipment_sword", 7, 47, 1),
    ITEM::item("昆古尼尔·命运之矛", "众神之王奥丁的配枪\n"
                                    "由世界树的枝干制成，形状扭曲，如同折断的古树枝条，枪身流转着金色流光\n"
                                    "长枪掷出，锁定命运，无视规则，绝对命中\n"
                                    "对流星许愿吧！因为以昆古尼尔起誓的诺言必定应验\n"
                                    "[特殊]使用此武器对方将无法闪避", 0, -1, -1, "equipment_sword", 7, 102, 2),
    ITEM::item("七宗罪", "“凡王之血，必以剑终”\n"
                         "炼金术的巅峰神器\n"
                         "内置七柄刀剑，分别为傲慢，妒忌，暴怒，懒惰，贪婪，饕餮，色欲\n"
                         "七柄刀剑收纳于漆黑炼金刀匣，匣身镌刻古老铭文\n"
                         "七把同时出鞘，可展开炼金领域「青铜炼狱·罪与罚」\n"
                         "龙的戾气流转于刃身，渴望用利刃终结诸王宿命", 0, -1, -1, "equipment_sword", 7, 41, 3),
    ITEM::item("魔刀千刃", "原是神锻国的秘宝\n"
                           "刀刃由上千块碎片组成,黑色刀柄半截刀身\n"
                           "刀身上的蓝色条纹,显现出恶灵的图案,闪现着淡淡的蓝色或紫色的光\n"
                           "只有条纹发光,才可以发挥出强大的力量\n"
                           "“只攻不防,天下无双,魔刀千刃”\n"
                           "要小心了!\n"
                           "深渊里的恶灵无时无刻不在触动\n"
                           "他们释放的黑洞吞噬世间的一切", 0, -1, -1, "equipment_sword", 7, 105, 3),
    ITEM::item("深渊·诅咒之戒", "来自深渊的目光正在凝视着你...", 0, -1, -1, "equipment_accessory", 6),
    ITEM::item("创世神之心", "你获得了来自Minecraft创世神的认可", 0, -1, -1, "material", 6),

    ITEM::item("小型金币福袋", "打开可获得5~15金币", 0, 10, 0, "fudai_jb", 2),
    ITEM::item("中型金币福袋", "打开可获得40~60金币", 0, 50, 0, "fudai_jb", 3),
    ITEM::item("大型金币福袋", "打开可获得90~110金币", 0, 100, 0, "fudai_jb", 4),
    ITEM::item("小型钻石福袋", "打开可获得1~5钻石", 0, 0, 3, "fudai_zs", 3),
    ITEM::item("中型钻石福袋", "打开可获得5~15钻石", 0, 0, 10, "fudai_zs", 4),
    ITEM::item("大型钻石福袋", "打开可获得40~60钻石", 0, 0, 50, "fudai_zs", 5),

    ITEM::item("杂货铺刷新券", "可用于刷新杂货铺", 0, 200, 20, "shuaxin_zahuo", 4),
    ITEM::item("神秘商人刷新券", "可用于刷新神秘商人", 0, 300, 40, "shuaxin_shenmi", 5),
    ITEM::item("世界Boss刷新券", "可用于刷新世界Boss", 0, 400, 60, "shuaxin_boss", 6),

    ITEM::item("体力瓶", "用于回复挖矿损失的体力", 0, 15, 0, "consumables", 3),
    ITEM::item("装备碎片", "通过分解装备获得", 0, -1, -1, "material", 3),
    ITEM::item("化神石", "可用于突破神级瓶颈", 0, -1, -1, "consumables_more", 6),
};

struct Player {
    Data data;
    WorldData worldData;
    StrData strData;
    ITEM items;
    string path;
    string name, password;
    long long createTime = 0;

    Player() = default;
    Player(string path) {
        this->path = std::move(path);
    }

    enum fileType {
        SUCCESS, NO_EXISTS, DATA_ERROR
    };
    fileType readFile() {
        if (!filesystem::exists(path) || !filesystem::is_regular_file(path)) {
            return NO_EXISTS;
        }
        ifstream fin(path);
        string s_time, s_password, s_data, s_worldData, s_strData, s_items, verCode;
        fin >> s_time
            >> s_password
            >> s_data
            >> s_worldData
            >> s_strData
            >> s_items
            >> verCode;
        createTime = decodeTime(s_time);
        Base64Key = createTime / 7;
        password = decode(s_password);
        string realVerCode = getVerificationCode(s_time + s_password + s_data + s_worldData + s_strData + s_items);
        if (realVerCode != verCode) {
            return DATA_ERROR;
        }

        stringstream vdata(decode(s_data));
        data.init(init_data);
        int index = 0;
        for (auto & mdata : data.datas) {
            vdata >> mdata.value;
            index ++;
        }

        stringstream vdata2(decode(s_worldData));
        worldData.init(init_worldData);
        index = 0;
        for (auto & mdata2 : worldData.datas) {
            vdata2 >> mdata2.value;
            index ++;
        }

        stringstream vdata3(decode(s_strData));
        strData.init(init_strData);
        index = 0;
        for (auto & mdata3 : strData.datas) {
            vdata3 >> mdata3.value;
            index ++;
        }

        stringstream vitem(decode(s_items));
        items.init(init_item);
        index = 0;
        for (auto & mitem : items.items) {
            vitem >> mitem.count;
            index ++;
        }
        fin.close();
        return SUCCESS;
    }

    bool writeFile() {
        ofstream fout(path);
        fout << encodeTime(createTime) << endl;
        fout << encode(password) << endl;

        stringstream vdata;
        for (auto & data : data.datas) {
            vdata << data.value << " ";
        }

        stringstream vdata2;
        for (auto & data2 : worldData.datas) {
            vdata2 << data2.value << " ";
        }

        stringstream vdata3;
        for (auto & data3 : strData.datas) {
            vdata3 << data3.value << " ";
        }

        stringstream vitem;
        for (auto & item : items.items) {
            vitem << item.count << " ";
        }
        string code = encode(vdata.str());
        string code2 = encode(vdata2.str());
        string code3 = encode(vdata3.str());
        string code4 = encode(vitem.str());
        string verCode = getVerificationCode(encodeTime(createTime) + encode(password) + code + code2 + code3 + code4);
        fout << code << endl
             << code2 << endl
             << code3 << endl
             << code4 << endl
             << verCode << endl;
        fout.close();
        return true;
    }

    vector<pair<string, int>> getItemList(vector<string> types, bool introduce) {
        return items.getItemList(std::move(types), introduce);
    }

    int getData(const int index) {
        return data[index]->value;
    }

    int getWorldData(const int index) {
        return worldData[index]->value;
    }

    string getStrData(const int index) {
        return strData[index]->value;
    }

    int getItem(const int index) {
        return items[index]->count;
    }
};

struct Entity {
    string name;
    string introduce;
    Data data;
    ITEM capture;

    Entity() = default;
    Entity(string name, string introduce, Data data, ITEM capture) {
        this->name = std::move(name);
        this->introduce = std::move(introduce);
        this->data = std::move(data);
        this->capture = std::move(capture);
    }
    Entity(string name, Data data, ITEM capture) {
        this->name = std::move(name);
        this->data = std::move(data);
        this->capture = std::move(capture);
    }

    int getData(const int index) {
        return data[index]->value;
    }

    int getCapture(const int index) {
        return capture[index]->count;
    }
};

inline Entity createMonster(const string& name, int level, bool showLevel, float override = 1) {
    Entity monster;
    // 特殊
    if (dayPeriod == 3) {
        override += 0.1;
    }
    // 数据
    if (showLevel) {
        monster.name = name + "[lv." + to_string(level) + "]";
    } else {
        monster.name = name;
    }
    monster.data.init(init_data);
    monster.capture.init(init_item);

    monster.data.datas[1].value = level * 10 * override;
    monster.data.datas[2].value = level / 2 * override;
    monster.data.datas[3].value = level / 20 * override;

    monster.data.datas[4].value = level * 3 * override;
    monster.data.datas[5].value = level * override;
    monster.data.datas[6].value = level * 10 * override;
    monster.data.datas[7].value = level * 10 * override;
    monster.data.datas[8].value = level * 0.4 * override;
    monster.data.datas[9].value = level * 0.2 * override;
    monster.data.datas[10].value = level * 0.2 * override;
    monster.data.datas[11].value = level * 0.5 * override;
    monster.data.datas[12].value = level * 0.3 * override;
    monster.data.datas[13].value = level * 0.3 * override;
    monster.data.datas[14].value = 10 + (level/10) * 3;
    return monster;
}

inline string getInitString(const string& password) {
    long long createTime = time(0);
    Base64Key = createTime / 7;
    string vtime = encodeTime(createTime);
    string vpassword = encode(password);

    stringstream vdata;
    for (auto & data : init_data) {
        vdata << data.value << " ";
    }
    stringstream vdata2;
    for (auto & data2 : init_worldData) {
        vdata2 << data2.value << " ";
    }
    stringstream vdata3;
    for (auto & data3 : init_strData) {
        vdata3 << data3.value << " ";
    }
    stringstream vitem;
    for (auto & item : init_item) {
        vitem << item.count << " ";
    }

    string code = encode(vdata.str());
    string code2 = encode(vdata2.str());
    string code3 = encode(vdata3.str());
    string code4 = encode(vitem.str());
    string verCode = getVerificationCode(vtime + vpassword + code + code2 + code3 + code4);
    string res = vtime + "\n"
            + vpassword + "\n"
            + code + "\n"
            + code2 + "\n"
            + code3 + "\n"
            + code4 + "\n"
            + verCode;
    return res;
}


#endif //DATA_H
