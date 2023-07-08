#ifndef MAGICTOWER1_H
#define MAGICTOWER1_H

#include "tower.h"

class MagicTower1 : public Tower
{
public:
    MagicTower1(const int,const int);
    void Attack(QVector<Enemy*>&) override;  //重写攻击函数
};

#endif // MAGICTOWER_H
