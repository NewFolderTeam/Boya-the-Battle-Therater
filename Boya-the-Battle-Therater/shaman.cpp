#include "shaman.h"

Shaman::Shaman(QVector<Coor> path)
    : Enemy(path, 100, 2, 3, 5, 1, 15,50,50)
{
    picturePath = ":/image/shaman.png";
}

