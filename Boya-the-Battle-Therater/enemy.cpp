#include "enemy.h"
#include <math.h>

//初始化敌人的坐标和属性
Enemy::Enemy(QVector<Coor> &path, int health_,int armorType_, int protectionLevel_, int speed_, int damage_, int reward_,int w_,int h_)
    : SFCB(path.at(0).x, path.at(0).y)
{
    health=health_;
    ori_health=health_;
    armorType=armorType_;
    protectionLevel=protectionLevel_;
    speed=speed_;
    damage=damage_;
    reward=reward_;
    width=w_;
    height=h_;
    enemyPathVec=path;
    poision=false;
    poision_counter=0;
}

//敌人移动函数
bool Enemy::move()
{
    if(enemyPathVec.empty())
        return true;

    if (enemyPathVec.at(0).y > y) //下
    {
        y += speed;
        return false;
    }

    if (enemyPathVec.at(0).x < x) //左
    {
        x -= speed;
        return false;
    }

    if (enemyPathVec.at(0).x > x) //右
    {
        x += speed;
        return false;
    }

    if (enemyPathVec.at(0).y < y) //上
    {
        y -= speed;
        return false;
    }

    //如果敌人的坐标和路径点坐标重合，则删除这个路径点
    if (enemyPathVec.at(0).y == y && enemyPathVec.at(0).x == x)
    {
        enemyPathVec.erase(enemyPathVec.begin());       //删除第一个路径点
    }

    return false;
}

Coor Enemy::getCoor() const     //返回坐标
{
    return Coor(x, y);
}

QString Enemy::getPicturePath() const//返回图片路径
{
    return picturePath;
}

QString Enemy::getPoisionedPath() const
{
    return ":/image/poisioned.png";
}

int Enemy::getWidth() const     //返回宽高
{
    return width;
}

int Enemy::getHeight() const
{
    return height;
}

int Enemy::getHealth() const
{
    return health;
}

int Enemy::getOrihealth() const
{
    return ori_health;
}

int Enemy::getArmorType() const
{
    return armorType;
}

int Enemy::getProtectionLevel() const
{
    return protectionLevel;
}

void Enemy::setPoision()
{
    poision=true;
}

void Enemy::dePoision()
{
    poision=false;
}

int Enemy::getSpeed() const
{
    return speed;
}

int Enemy::getDamage() const
{
    return damage;
}

int Enemy::getReward() const
{
    return reward;
}

bool Enemy::isPoision() const
{
    return poision;
}

void Enemy::decreaseHealth(int amount,int i)
{
    if(armorType!=i||protectionLevel==0){
    health -= amount;
    }
    else if(protectionLevel==1){
    health -= amount*0.7;
    }
    else if(protectionLevel==2){
    health -= amount*0.5;
    }
    else if(protectionLevel==3){
    health -= amount*0.2;
    }
    if (health < 0)
        health = 0;
}

void Enemy::Poision()
{
    if(armorType==2){
        if(protectionLevel==1)
        health -= ori_health*0.03;
        else if(protectionLevel==2)
        health -= ori_health*0.02;
        else if(protectionLevel==3)
        health -= ori_health*0.01;
    }
    else health -= ori_health*0.04;
    if (health < 0)
        health = 0;
    poision_counter++;
    if(poision_counter>=7){
        poision_counter=0;
        poision=false;
    }
}
