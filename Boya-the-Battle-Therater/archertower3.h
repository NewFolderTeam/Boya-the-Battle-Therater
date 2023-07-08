#ifndef ARCHERTOWER3_H
#define ARCHERTOWER3_H

#include "tower.h"

class ArcherTower3 : public Tower
{
public:
    ArcherTower3(const int,const int);
    void Attack(QVector<Enemy*>&) override;  //重写攻击函数
};

#endif // ARCHERTOWER3_H
