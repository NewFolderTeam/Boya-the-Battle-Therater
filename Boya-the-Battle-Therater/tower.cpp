#include "tower.h"
#include <random>
Tower::Tower(const int x,const int y) : SFCB(x,y)
{
    disCoorX = x, disCoorY = y;
}

QString Tower::getPicturePath() const//返回防御塔图片路径
{
    return picturePath;
}

int Tower::getWidth() const     //返回防御塔宽
{
    return width;
}

int Tower::getHeight() const    //返回防御塔高
{
    return height;
}

Enemy* Tower::getTargetEnemy() const      //返回目标敌人
{
    return targetEnemy;
}

int Tower::getAttackInterval() const
{
    return attackInterval;
}

int Tower::getAttackPowerMin() const
{
    return attackPowerMin;
}

int Tower::getAttackPowerMax() const
{
    return attackPowerMax;
}

int Tower::getDamageType() const
{
    return damageType;
}

int Tower::getAttackType() const
{
    return attackType;
}

int Tower::getRange() const
{
    return range;
}

int Tower::getCost() const
{
    return cost;
}

int Tower::getUp() const
{
    return up;
}

int Tower::getSellPrice() const
{
    return sellPrice;
}

int Tower::getType() const
{
    return type;
}

QVector<Coor> Tower::getAttackCoor() const  //返回攻击坐标
{
    QVector<Coor> tempAttackec;
    for(auto bull : BulletVec)  //遍历子弹数组，把子弹数组的坐标全部给临时数组
        tempAttackec.push_back(Coor(bull->x, bull->y));

    return tempAttackec;    //返回
}

Coor Tower::getDisCoor() const        //返回防御塔显示坐标
{
    return Coor(disCoorX, disCoorY);
}

bool Tower::getRangeFlag() const      //返回显示范围标记
{
    return displayRangeFlag;
}

void Tower::setRangeFlag(const bool flag)      //设置显示范围标记
{
    displayRangeFlag = flag;
}

Coor Tower::getCoor() const      //返回防御塔坐标
{
    return Coor(x, y);
}

int Tower::attackPower() const
{
    // 生成随机整数作为攻击力
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(attackPowerMin, attackPowerMax);
    int attackPower = dis(gen);
    return attackPower;
}

void Tower::setTargetEnemyNull()
{
    targetEnemy = nullptr;
}

