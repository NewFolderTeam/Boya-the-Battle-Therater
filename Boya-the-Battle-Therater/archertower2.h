#ifndef ARCHERTOWER2_H
#define ARCHERTOWER2_H

#include "tower.h"

class ArcherTower2 : public Tower
{
public:
    ArcherTower2(const int,const int);
    void Attack(QVector<Enemy*>&) override;  //重写攻击函数
};

#endif // ARCHERTOWER2_H
