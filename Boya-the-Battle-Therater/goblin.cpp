#include "goblin.h"

Goblin::Goblin(QVector<Coor> path)
    : Enemy(path, 24, 1, 0, 8, 1, 3,40,40)
{
    picturePath = ":/image/gbl.png";

}

