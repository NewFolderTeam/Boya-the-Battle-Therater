#ifndef MAGICTOWER2_H
#define MAGICTOWER2_H

#include "tower.h"

class MagicTower2 : public Tower
{
public:
    MagicTower2(const int,const int);
    void Attack(QVector<Enemy*>&) override;  //重写攻击函数
};

#endif // MAGICTOWER2_H
