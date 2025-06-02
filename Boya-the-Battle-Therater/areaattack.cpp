#include "areaattack.h"
#include "tower.h"
#include "enemy.h"
#include <algorithm>

void AreaAttack::performAttack(Tower* tower, QVector<Enemy*>& enemiesInRange, QVector<HitEffect*>& effectsOutput) {
    int counter = tower->getCounter();
    int attackInterval = tower->getAttackInterval();
    int range = tower->getRange();
    int towerX = tower->getCoor().x;
    int towerY = tower->getCoor().y;

    // 常量定义
    const int halfBlockLen = 40; // 塔的半边长，用于计算中心点和射程

    // 无论是否有敌人，counter 都递增到 attackInterval
    if (enemiesInRange.empty()) {
        counter = std::min(counter + 1, attackInterval);
    } else {
        if (counter >= attackInterval) {
            for (auto enemy : enemiesInRange) {
                // 检查敌人在塔的攻击范围内
                if (enemy->getHealth() > 0 && // 确保敌人是活的
                    DistBetPoints(enemy->getCoor().x + (enemy->getWidth() >> 1),
                                  enemy->getCoor().y + (enemy->getHeight() >> 1),
                                  towerX + halfBlockLen, towerY + halfBlockLen) <= range) {
                    // 造成伤害
                    enemy->decreaseHealth(tower->attackPower(), tower->getDamageType());

                    // 添加命中效果
                    int effectX = enemy->getCoor().x + (enemy->getWidth() >> 1);
                    int effectY = enemy->getCoor().y + (enemy->getHeight() >> 1);
                    effectsOutput.push_back(new HitEffect(effectX, effectY, 40, 40, 2)); // Type 2 for AOE effect
                }
            }
            counter = 0; // 重置计时器
        }
        counter++; // 攻击后继续计时
    }
    tower->setCounter(counter); // 更新塔的计时器
}
