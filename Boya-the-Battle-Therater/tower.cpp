#include "tower.h"
#include "attack.h"
#include <random>
#include <algorithm>

Tower::Tower(const int x, const int y) : SFCB(x, y) {
    disCoorX = x;
    disCoorY = y;
    attack = nullptr; // 初始化 Attack 指针
    // counter 的初始值，会在派生类的构造函数中调用 updateAttributesForLevel() 时设置
    // 或者在派生类的构造函数中直接设置 `counter = attackInterval;`
    // 这里保持默认值，因为它在派生类构造函数中会立即被 `updateAttributesForLevel` 覆盖
    // 或者 Tower::counter 的默认初始值 0 (如果没有显式初始化)
}

Tower::~Tower() {
    delete attack; // 清理 Attack 对象
}

int Tower::getLevel() const { return level; }

void Tower::levelUp() {
    if (level < 3) { // 假设最高等级为3
        level++;
        updateAttributesForLevel(); // 调用纯虚函数，由派生类实现属性更新
    }
}

int Tower::getAttackInterval() const { return attackInterval; }
int Tower::getAttackPowerMin() const { return attackPowerMin; }
int Tower::getAttackPowerMax() const { return attackPowerMax; }
int Tower::getDamageType() const { return damageType; }
int Tower::getAttackType() const { return attackType; }
int Tower::getRange() const { return range; }
int Tower::getCost() const { return cost; }
int Tower::getUp() const { return up; } // 直接返回成员变量
int Tower::getSellPrice() const { return sellPrice; } // 直接返回成员变量
int Tower::getType() const { return type; }
int Tower::getCounter() const { return counter; }
void Tower::setCounter(const int _counter) { counter = _counter; }

int Tower::attackPower() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(attackPowerMin, attackPowerMax);
    return dis(gen);
}

QString Tower::getPicturePath() const { return picturePath; }
int Tower::getHeight() const { return height; }
int Tower::getWidth() const { return width; }
Enemy* Tower::getTargetEnemy() const { return targetEnemy; }
void Tower::setTargetEnemy(Enemy* enemy) { targetEnemy = enemy; } // 实现设置目标敌人
void Tower::setTargetEnemyNull() { targetEnemy = nullptr; }

QVector<Coor> Tower::getAttackCoor() const {
    QVector<Coor> tempAttackec;
    // 如果 Attack 类有获取子弹坐标的接口，可以在这里调用
    // if (attack) { return attack->getBulletCoordinates(); }
    return tempAttackec;
}

Coor Tower::getCoor() const { return Coor(x, y); }
Coor Tower::getDisCoor() const { return Coor(disCoorX, disCoorY); }
bool Tower::getRangeFlag() const { return displayRangeFlag; }
void Tower::setRangeFlag(const bool flag) { displayRangeFlag = flag; }
