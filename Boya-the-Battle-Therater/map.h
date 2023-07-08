#ifndef MAP_H
#define MAP_H

#include <vector>
#include "terrain.h"

class Map
{
public:
    Map(int width, int height);

    int getWidth() const;
    int getHeight() const;
    Terrain getTerrain(int x, int y) const;
    void setTerrain(int x, int y, Terrain::Type type);

    // 添加设置防御塔和敌人队列的方法
    void setTower(int x, int y, Tower* tower);
    Tower* getTower(int x, int y) const;
    void enqueueEnemy(int x, int y, const Enemy& enemy);
    Enemy dequeueEnemy(int x, int y);
    bool isEnemyQueueEmpty(int x, int y) const;

private:
    int m_width;
    int m_height;
    std::vector<std::vector<Terrain>> m_terrainGrid;
};

#endif // MAP_H


