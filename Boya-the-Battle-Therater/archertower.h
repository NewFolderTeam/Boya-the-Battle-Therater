#ifndef ARCHERTOWER_H
#define ARCHERTOWER_H

#include "tower.h"
#include "singletargetattack.h" // ArcherTower 使用单体攻击

class ArcherTower : public Tower
{
public:
    ArcherTower(const int x, const int y, int level = 1); // Default to level 1
    ~ArcherTower(); // 析构函数

    // 实现 Tower 的纯虚函数 performAttack，只负责委托给 Attack 对象
    void performAttack(QVector<Enemy*>& enemiesInRange, QVector<HitEffect*>& effectsOutput) override;

protected:
    // 实现 Tower 的纯虚函数 updateAttributesForLevel，用于设置所有塔的属性
    void updateAttributesForLevel() override;
};

#endif // ARCHERTOWER_H
