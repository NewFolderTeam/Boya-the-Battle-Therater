#ifndef MAGICTOWER_H
#define MAGICTOWER_H

#include "tower.h"
#include "singletargetattack.h" // MagicTower 使用单体攻击策略

class MagicTower : public Tower
{
public:
    MagicTower(const int x, const int y, int level = 1); // 默认从 1 级开始
    ~MagicTower(); // 析构函数

    // 实现 Tower 的纯虚函数 performAttack，只负责委托给 Attack 对象
    void performAttack(QVector<Enemy*>& enemiesInRange, QVector<HitEffect*>& effectsOutput) override;

private:
    // 实现 Tower 的纯虚函数 updateAttributesForLevel，用于设置所有塔的属性
    void updateAttributesForLevel() override;
};

#endif // MAGICTOWER_H
