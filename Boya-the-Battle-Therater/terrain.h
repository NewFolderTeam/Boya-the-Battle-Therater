#ifndef TERRAIN_H
#define TERRAIN_H

#include <queue>  // 添加队列的头文件
#include "tower.h"  // 添加防御塔的头文件
#include "enemy.h"  // 添加敌人的头文件

class Terrain
{
public:
    enum Type {
        Plain=0,
        Forest=1,
        Hill=2,
        Water=3,
        Road=4,
        EnemyBase=5,
        PlayerBase=6,
        TowerBase=7
    };

    Terrain(Type type);

    Type getType() const;

    // 添加防御塔对象和敌人队列的存储和获取方法
    void setTower(Tower* tower);
    Tower* getTower() const;
    void enqueueEnemy(const Enemy& enemy);
    Enemy dequeueEnemy();
    bool isEnemyQueueEmpty() const;

private:
    Type m_type;
    Tower* m_tower;  // 存储防御塔对象
    std::queue<Enemy> m_enemyQueue;  // 存储敌人队列
};

#endif // TERRAIN_H


