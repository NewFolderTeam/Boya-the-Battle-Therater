#ifndef AREAATTACK_H
#define AREAATTACK_H
#include "attack.h"

class AreaAttack : public Attack {
public:
    void performAttack(Tower* tower, QVector<Enemy*>& enemiesInRange, QVector<HitEffect*>& effectsOutput) override;
};

#endif // AREAATTACK_H
