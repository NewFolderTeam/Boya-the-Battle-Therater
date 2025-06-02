#include "archertower.h"
#include "tower.h" // 确保包含 Tower
#include "enemy.h" // 确保包含 Enemy
#include <QString>

ArcherTower::ArcherTower(const int x, const int y, int level)
    : Tower(x, y) // 调用 Tower 的构造函数
{
    // 设置 Tower 基类的 level 成员
    this->level = (level >= 1 && level <= 3) ? level : 1;
    attack = new SingleTargetAttack(); // 为弓箭塔分配一个单体攻击策略
    updateAttributesForLevel(); // 根据等级设置塔的属性，包括 up 和 sellPrice
    // counter 的初始值已经在 updateAttributesForLevel 中设置
}

ArcherTower::~ArcherTower() {
    // 父类 Tower 的虚析构函数会处理 delete attack;
}

// ArcherTower 自身的攻击方法，它仅仅委托给 Attack 类的实例
void ArcherTower::performAttack(QVector<Enemy*>& enemiesInRange, QVector<HitEffect*>& effectsOutput)
{
    if (attack) {
        // 调用 SingleTargetAttack 的 performAttack，它会处理所有攻击逻辑和特殊效果
        attack->performAttack(this, enemiesInRange, effectsOutput);
    }
}

// 根据等级设置塔的属性
void ArcherTower::updateAttributesForLevel()
{
    switch (level) {
    case 1:
        width = 80;
        height = 80;
        picturePath = ":/image/atw1.png";
        type = 1; // 类型：弓箭塔
        attackInterval = 6;
        range = 150;
        cost = 70; // 建造价格
        attackPowerMin = 7;
        attackPowerMax = 9;
        damageType = 1; // 伤害类型（物理）
        attackType = 1; // 攻击类型（单体）
        up = 110;       // 升级价格从1到2
        sellPrice = 28; // 出售价格
        break;
    case 2:
        width = 80;
        height = 80;
        picturePath = ":/image/atw2.png";
        type = 1;
        attackInterval = 5; // 更快攻击
        range = 180;        // 增加射程
        cost = 0;           // 升级塔不再有初始建造费用
        attackPowerMin = 11;
        attackPowerMax = 15;
        damageType = 1;
        attackType = 1;
        up = 160;       // 升级价格从2到3
        sellPrice = 72; // 出售价格
        break;
    case 3:
        width = 80;
        height = 80;
        picturePath = ":/image/atw3.png";
        type = 1;
        attackInterval = 4; // 最快攻击
        range = 210;        // 最大射程
        cost = 0;
        attackPowerMin = 13;
        attackPowerMax = 19;
        damageType = 1;
        attackType = 1;
        up = 99999;     // 3级不能再升级
        sellPrice = 136; // 出售价格
        // 特殊效果：中毒，在 Attack 类的 performAttack 中实现，通过检查 Tower 的类型和等级
        break;
    }
    // 确保 counter 在属性更新后，如果没敌人，能立即攻击
    counter = attackInterval;
}
