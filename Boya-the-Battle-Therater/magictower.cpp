#include "magictower.h"
#include "tower.h"
#include "enemy.h"
#include <QString>

MagicTower::MagicTower(const int x, const int y, int level)
    : Tower(x, y) // 调用 Tower 的构造函数
{
    // 设置 Tower 基类的 level 成员
    this->level = (level >= 1 && level <= 3) ? level : 1;
    // MagicTower 是先单体攻击再溅射，所以使用 SingleTargetAttack 策略
    attack = new SingleTargetAttack();
    updateAttributesForLevel(); // 根据等级设置塔的属性
}

MagicTower::~MagicTower() {
    // 父类 Tower 的虚析构函数会处理 delete attack;
}

// MagicTower 自身的攻击方法，它仅仅委托给 Attack 类的实例
void MagicTower::performAttack(QVector<Enemy*>& enemiesInRange, QVector<HitEffect*>& effectsOutput)
{
    if (attack) {
        // 调用 SingleTargetAttack 的 performAttack，它会处理所有攻击逻辑、溅射和特殊效果
        attack->performAttack(this, enemiesInRange, effectsOutput);
    }
}

// 根据等级设置塔的属性
void MagicTower::updateAttributesForLevel()
{
    switch (level) {
    case 1:
        width = 80; // 保持与其他塔一致
        height = 80;
        picturePath = ":/image/mtw1.png";
        type = 2;
        attackInterval = 8;
        range = 140;
        cost = 90;
        attackPowerMin = 9;
        attackPowerMax = 17;
        damageType = 2; // 魔法伤害
        attackType = 1; // 单体攻击
        up = 150;       // 升级价格
        sellPrice = 36; // 出售价格
        break;
    case 2:
        width = 80;
        height = 80;
        picturePath = ":/image/mtw2.png";
        type = 2; // 类型不变
        attackInterval = 8;
        range = 160;
        cost = 0;
        attackPowerMin = 22;
        attackPowerMax = 44;
        damageType = 2;
        attackType = 1;
        up = 220;       // 升级价格
        sellPrice = 96; // 出售价格
        break;
    case 3:
        width = 80;
        height = 80;
        picturePath = ":/image/mtw3.png";
        type = 2; // 类型不变
        attackInterval = 8;
        range = 180;
        cost = 0;
        attackPowerMin = 41;
        attackPowerMax = 74;
        damageType = 2;
        attackType = 1;
        up = 99999;     // 3级不能再升级
        sellPrice = 184; // 出售价格
        // 特殊效果：溅射伤害，在 SingleTargetAttack 类的 performAttack 中实现，通过检查 Tower 的类型和等级
        break;
    }
    // 确保 counter 在属性更新后能立即攻击
    counter = attackInterval;
}
