#include "map.h"

Map::Map(int width, int height)
    : m_width(width), m_height(height)
{
    // 初始化地图格
    m_terrainGrid.resize(height);
    for (int y = 0; y < height; ++y)
    {
        m_terrainGrid[y].resize(width, Terrain(Terrain::Plain));//全部设置为平原
    }
}

int Map::getWidth() const
{
    return m_width;
}

int Map::getHeight() const
{
    return m_height;
}

Terrain Map::getTerrain(int x, int y) const
{
    return m_terrainGrid[y][x];
}

void Map::setTerrain(int x, int y, Terrain::Type type)
{
    m_terrainGrid[y][x] = Terrain(type);
}

void Map::setTower(int x, int y, Tower* tower)
{
    m_terrainGrid[y][x].setTower(tower);
}

Tower* Map::getTower(int x, int y) const
{
    return m_terrainGrid[y][x].getTower();
}

void Map::enqueueEnemy(int x, int y, const Enemy& enemy)
{
    m_terrainGrid[y][x].enqueueEnemy(enemy);
}

Enemy Map::dequeueEnemy(int x, int y)
{
    return m_terrainGrid[y][x].dequeueEnemy();
}

bool Map::isEnemyQueueEmpty(int x, int y) const
{
    return m_terrainGrid[y][x].isEnemyQueueEmpty();
}





