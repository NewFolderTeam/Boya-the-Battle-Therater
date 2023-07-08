#include "terrain.h"
Terrain::Terrain(Type type)
    : m_type(type), m_tower(nullptr)
{
}

Terrain::Type Terrain::getType() const
{
    return m_type;
}

void Terrain::setTower(Tower* tower)
{
    m_tower = tower;
}

Tower* Terrain::getTower() const
{
    return m_tower;
}

void Terrain::enqueueEnemy(const Enemy& enemy)
{
    m_enemyQueue.push(enemy);
}

Enemy Terrain::dequeueEnemy()
{
    Enemy enemy = m_enemyQueue.front();
    m_enemyQueue.pop();
    return enemy;
}

bool Terrain::isEnemyQueueEmpty() const
{
    return m_enemyQueue.empty();
}


