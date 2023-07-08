#ifndef MAGICTOWER3_H
#define MAGICTOWER3_H

#include "tower.h"

class MagicTower3 : public Tower
{
public:
    MagicTower3(const int,const int);
    void Attack(QVector<Enemy*>&) override;  //重写攻击函数
};

#endif // MAGICTOWER3_H
