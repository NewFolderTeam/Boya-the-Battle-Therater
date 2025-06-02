#ifndef ATTACK_H
#define ATTACK_H
#include <QVector>
#include "multifilestructure.h" // 包含 HitEffect 定义

// 前向声明 Tower 和 Enemy 类
class Tower;
class Enemy;

class Attack {
public:
    virtual ~Attack() {}
    // 执行攻击的接口，会读取 Tower 的数据和敌人数据，并进行攻击、显示特效
    // 也会更新 Enemy 的生命值和状态，并管理 Tower 的 counter
    virtual void performAttack(Tower* tower, QVector<Enemy*>& enemiesInRange, QVector<HitEffect*>& effectsOutput) = 0;
};

#endif // ATTACK_H
