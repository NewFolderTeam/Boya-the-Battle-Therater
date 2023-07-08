#include "orc.h"

Orc::Orc(QVector<Coor> path)
    : Enemy(path, 80, 1, 1, 5, 1, 9,50,50)
{
    picturePath = ":/image/orc.png";
}

