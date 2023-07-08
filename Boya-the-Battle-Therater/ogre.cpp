#include "ogre.h"

Ogre::Ogre(QVector<Coor> path)
    : Enemy(path, 800, 1, 2, 4, 5, 50,90,90)
{
    picturePath = ":/image/ogre.png";
}

