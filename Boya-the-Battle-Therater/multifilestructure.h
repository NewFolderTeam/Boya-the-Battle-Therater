// multifilestructure.h
#ifndef MULTIFILESTRUCTURE_H
#define MULTIFILESTRUCTURE_H

#include <QString>
#include <QVector>

// 基础坐标类 (SFCB: Simple Fixed Coordinate Base)
class SFCB {
public:
    SFCB(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

    // 提供 getter 方便外部访问，如果需要的话
    int getX() const { return x; }
    int getY() const { return y; }
    QString picturePath; // 子弹的图片路径
    int x, y; // 坐标
};

// Coor 结构体
struct Coor {
    int x, y;
    Coor(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

// HitEffect 结构体
struct HitEffect : public Coor {
    int width, height;
    int type;  // 1: 弓箭命中，2: 魔法命中，3: 魔法溅射
    int index; // 用于动画帧
    HitEffect(int _x, int _y, int w, int h, int t)
        : Coor(_x, _y), width(w), height(h), type(t), index(0) {}
};

// BulletEffect 结构体，用于绘制子弹/法术效果
struct BulletEffect : public Coor {
    int width, height;
    QString picturePath; // 子弹的图片路径
    BulletEffect(int _x, int _y, int w, int h, const QString& path)
        : Coor(_x, _y), width(w), height(h), picturePath(path) {}
};

// 定义地图块长度，作为常量
const int mapBlockLen = 80;
const int halfBlockLen = mapBlockLen >> 1; // 40

#endif // MULTIFILESTRUCTURE_H
