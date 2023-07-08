#ifndef ARCHERTOWER1_H
#define ARCHERTOWER1_H

#include "tower.h"

class ArcherTower1 : public Tower
{
public:
    ArcherTower1(const int,const int);
    void Attack(QVector<Enemy*>&) override;  //重写攻击函数
};

#endif // ARCHERTOWER1_H
