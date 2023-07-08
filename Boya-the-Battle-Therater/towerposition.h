#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H
#include <QSize>
#include <QPainter>
#include <QString>

class TowerPosition
{
public:
    int x,y;
    bool fh=0;
    TowerPosition(int x1,int y1)
    {
        x=x1;
        y=y1;
    }
};

#endif // TOWERPOSITION_H
