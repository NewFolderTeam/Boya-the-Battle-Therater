#ifndef ENEMY_H
#define ENEMY_H
#include "multifilestructure.h"
#include <QString>

class Enemy : protected SFCB
{
public:
    Enemy(QVector<Coor>&, int health, int armorType, int protectionLevel, int speed, int damage, int reward, int height, int width);
    bool move();
    int getHealth() const;
    int getOrihealth() const;
    int getArmorType() const;
    int getProtectionLevel() const;
    int getSpeed() const;
    int getDamage() const;
    int getReward() const;
    int getWidth() const;
    int getHeight() const;
    void setPoision();
    void dePoision();
    void Poision();
    Coor getCoor() const;
    QString getPicturePath() const;
    QString getPoisionedPath() const;
    void decreaseHealth(int amount, int i);
    bool isPoision() const;

protected:
    int health;
    int ori_health;
    int width, height;//宽和高
    int armorType;
    int protectionLevel;
    int speed;//每次循环敌人移动的像素数
    QVector<Coor> enemyPathVec;     //敌人移动路径
    int damage;
    int reward;
    bool poision;
    int poision_counter;

};

#endif // ENEMY_H

