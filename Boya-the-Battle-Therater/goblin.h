#ifndef GOBLIN_H
#define GOBLIN_H

#include "enemy.h"

class Goblin : public Enemy
{
public:
    Goblin(QVector<Coor>);
};

#endif // GOBLIN_H

