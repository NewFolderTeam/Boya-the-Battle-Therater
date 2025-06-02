#ifndef SINGLETARGETATTACK_H
#define SINGLETARGETATTACK_H
#include "attack.h"
#include <QVector>

// 子弹结构体，现在归 Attack 类内部管理
struct BulletStr : public Coor {
    double k = 0.0, b = 0.0; // 斜率与截距
    bool dirFlag = false;    // 移动方向
    Enemy* targetEnemy; // 子弹的目标敌人
    BulletStr(int x, int y, Enemy* target = nullptr) : Coor(x, y), targetEnemy(target) {}
};

class SingleTargetAttack : public Attack {
public:
    SingleTargetAttack();
    ~SingleTargetAttack();
    void performAttack(Tower* tower, QVector<Enemy*>& enemiesInRange, QVector<HitEffect*>& effectsOutput) override;

    // 添加公共接口，允许 GameWindow 访问子弹列表以进行绘制
    const QVector<BulletStr*>& getBulletVec() const { return BulletVec; } // 返回 const 引用防止外部修改

private:
    QVector<BulletStr*> BulletVec; // 子弹数组
};

#endif // SINGLETARGETATTACK_H
