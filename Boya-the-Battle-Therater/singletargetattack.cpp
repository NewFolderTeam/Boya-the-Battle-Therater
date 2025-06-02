#include "singletargetattack.h"
#include "tower.h"
#include "enemy.h"
#include <algorithm>
#include <cmath>

SingleTargetAttack::SingleTargetAttack() {}

SingleTargetAttack::~SingleTargetAttack() {
    for (auto bullet : BulletVec) {
        delete bullet;
    }
    BulletVec.clear();
}

void SingleTargetAttack::performAttack(Tower* tower, QVector<Enemy*>& enemiesInRange, QVector<HitEffect*>& effectsOutput) {
    int counter = tower->getCounter();
    int attackInterval = tower->getAttackInterval();
    int range = tower->getRange();
    int towerX = tower->getCoor().x; // 塔的中心x
    int towerY = tower->getCoor().y; // 塔的中心y
    Enemy* currentTargetEnemy = tower->getTargetEnemy(); // 获取当前塔的目标敌人

    // 常量定义
    const int halfBlockLen = 40; // 塔的半边长，用于计算中心点和射程
    const int bulletSize = 25;   // 子弹大小，用于碰撞检测
    const int bulletMoveSpeed = 24; // 子弹移动速度
    const int magicSplashRange = 120; // 魔法塔3级溅射范围

    // --- 子弹与敌人碰撞检测 ---
    for (auto bullIt = BulletVec.begin(); bullIt != BulletVec.end(); ) {
        bool hit = false;
        // 子弹只碰撞其目标敌人
        if ((*bullIt)->targetEnemy && (*bullIt)->targetEnemy->getHealth() > 0) { // 确保目标存在且未死亡
            Enemy* target = (*bullIt)->targetEnemy;
            if ((*bullIt)->x + bulletSize >= target->getCoor().x &&
                (*bullIt)->x <= target->getCoor().x + target->getWidth() &&
                (*bullIt)->y + bulletSize >= target->getCoor().y &&
                (*bullIt)->y <= target->getCoor().y + target->getHeight()) {
                // 击中敌人：造成伤害
                target->decreaseHealth(tower->attackPower(), tower->getDamageType());

                // 3 级 ArcherTower 特殊效果：中毒
                if (tower->getType() == 1 && tower->getLevel() == 3) {
                    target->setPoison();
                }

                // 3 级 MagicTower 特殊效果：溅射伤害
                // 检查塔的类型是否为魔法塔 (Type 2)
                if (tower->getType() == 2 && tower->getLevel() == 3) {
                    // 对周围敌人造成溅射伤害
                    for (auto enemy : enemiesInRange) { // 遍历所有在射程内的敌人
                        if (enemy != target && enemy->getHealth() > 0 &&
                            DistBetPoints(enemy->getCoor().x + (enemy->getWidth() >> 1),
                                          enemy->getCoor().y + (enemy->getHeight() >> 1),
                                          target->getCoor().x + (target->getWidth() >> 1),
                                          target->getCoor().y + (target->getHeight() >> 1)) <= magicSplashRange) {
                            // 溅射伤害为 0.25 * 攻击力
                            enemy->decreaseHealth(static_cast<int>(0.25 * tower->attackPower()), tower->getDamageType());
                        }
                    }
                }

                // 添加命中效果
                int effectX = target->getCoor().x + (target->getWidth() >> 1);
                int effectY = target->getCoor().y + (target->getHeight() >> 1);

                // --- 修正后的命中效果类型和大小逻辑 ---
                int hitEffectType;
                int hitEffectSize;

                if (tower->getType() == 1) { // 弓箭塔
                    hitEffectType = 1; // 弓箭命中
                    hitEffectSize = 60; // 弓箭击中效果大小
                } else if (tower->getType() == 2) { // 魔法塔
                    if (tower->getLevel() == 3) {
                        hitEffectType = 3; // 魔法溅射
                        hitEffectSize = 80; // 溅射效果可能更大
                    } else {
                        hitEffectType = 2; // 魔法命中（非溅射），针对1、2级魔法塔
                        hitEffectSize = 60; // 魔法击中效果大小
                    }
                } else { // 其他未知类型，默认给个弓箭命中 (作为备用，理论上不会触发)
                    hitEffectType = 1;
                    hitEffectSize = 60;
                }
                // --- 修正结束 ---

                effectsOutput.push_back(new HitEffect(effectX, effectY, hitEffectSize, hitEffectSize, hitEffectType));

                delete *bullIt;
                bullIt = BulletVec.erase(bullIt);
                hit = true;
                // 击中后，处理下一个子弹，而不是继续当前子弹的循环（因为迭代器已失效）
                // 这里 break 只是为了避免在同一轮循环中对同一个子弹执行多次操作，
                // 实际迭代器管理已经由 erase 返回下一个有效迭代器来完成。
                // 如果一个子弹命中，应该直接跳到外层循环的下一个元素，这里不需要 break，
                // 因为 erase 已经返回了正确的迭代器。
                // 保留了 `break`，但实际上`erase` 后的 `++bullIt` 是不必要的，
                // 因为 `erase` 返回的是下一个有效迭代器。
                // 但为了保持最小改动，保留了其结构。
                // 这里的 `if (!hit) ++bullIt;` 语句是关键，它确保只有当没有命中时才手动递增迭代器。
                break; // 如果命中，立即跳出内层 for 循环，进入外层循环的下一次迭代
            }
        }
        if (!hit) ++bullIt; // 如果没有命中，才手动推进迭代器
    }

    // --- 子弹移动 ---
    for (auto bull : BulletVec) {
        if (bull->targetEnemy && bull->targetEnemy->getHealth() > 0) {
            Coor targetPos = bull->targetEnemy->getCoor();
            double deltaX = targetPos.x + (bull->targetEnemy->getWidth() >> 1) - (bull->x + (bulletSize >> 1));
            double deltaY = targetPos.y + (bull->targetEnemy->getHeight() >> 1) - (bull->y + (bulletSize >> 1));

            // 确保不会除以零，虽然对于移动到目标的逻辑来说这应该不会发生
            double dist = sqrt(deltaX * deltaX + deltaY * deltaY);
            if (dist > 0) { // 避免除以零
                bull->x += static_cast<int>(bulletMoveSpeed * (deltaX / dist));
                bull->y += static_cast<int>(bulletMoveSpeed * (deltaY / dist));
            }
        } else {
            // 这部分逻辑是用于没有目标或目标死亡时的子弹行为
        }
    }

    // --- 删除超出射程的子弹 ---
    // 这个逻辑在每次更新时都会检查子弹是否飞出了塔的攻击范围。
    // 如果子弹的目标还在，但子弹本身飞出了塔的射程，子弹会被删除。
    // 这与子弹在击中目标时删除是不同的。
    for (auto bullIt = BulletVec.begin(); bullIt != BulletVec.end(); ) {
        if (DistBetPoints((*bullIt)->x + (bulletSize >> 1), (*bullIt)->y + (bulletSize >> 1), towerX + halfBlockLen, towerY + halfBlockLen) > range) {
            delete *bullIt;
            bullIt = BulletVec.erase(bullIt);
        } else {
            ++bullIt;
        }
    }

    // --- 攻击冷却和目标选择逻辑 ---
    if (enemiesInRange.empty()) {
        counter = std::min(counter + 1, attackInterval);
    } else {
        // 检查当前目标是否有效（存活且在范围内）
        if (!currentTargetEnemy || currentTargetEnemy->getHealth() <= 0 ||
            DistBetPoints(currentTargetEnemy->getCoor().x + (currentTargetEnemy->getWidth() >> 1),
                          currentTargetEnemy->getCoor().y + (currentTargetEnemy->getHeight() >> 1),
                          towerX + halfBlockLen, towerY + halfBlockLen) > range) {
            Enemy* newTarget = nullptr;
            // 尝试寻找新目标
            for (Enemy* enemy : enemiesInRange) {
                if (enemy->getHealth() > 0 &&
                    DistBetPoints(enemy->getCoor().x + (enemy->getWidth() >> 1),
                                  enemy->getCoor().y + (enemy->getHeight() >> 1),
                                  towerX + halfBlockLen, towerY + halfBlockLen) <= range) {
                    newTarget = enemy;
                    break; // 找到第一个有效目标就使用
                }
            }
            tower->setTargetEnemy(newTarget); // 更新塔的目标
            currentTargetEnemy = newTarget;   // 更新局部变量
        }

        if (currentTargetEnemy) {
            if (counter >= attackInterval) {
                // 发射新子弹
                BulletStr* bull = new BulletStr(towerX + halfBlockLen, towerY + (tower->getHeight() >> 2), currentTargetEnemy);

                // 计算子弹的飞行轨迹（k和b用于直线方程）
                double deltaX = currentTargetEnemy->getCoor().x - bull->x;
                double deltaY = currentTargetEnemy->getCoor().y - bull->y;

                if (deltaX == 0) { // 垂直方向
                    bull->dirFlag = (deltaY > 0); // 判断是向上还是向下
                    bull->k = 0; // 斜率为0
                    bull->b = bull->x; // 当deltaX=0时，b可能被用作x截距，但y=kx+b不适用垂直线
                        // 这段逻辑在数学上处理垂直线不够严谨，等待改进
                } else {
                    bull->k = deltaY / deltaX;
                    bull->b = currentTargetEnemy->getCoor().y - currentTargetEnemy->getCoor().x * bull->k;
                    bull->dirFlag = (deltaX > 0); // 判断是向左还是向右
                }
                BulletVec.push_back(bull);
                counter = 0; // 重置攻击冷却
            }
            counter++; // 递增攻击冷却计数
        } else {
            counter = std::min(counter + 1, attackInterval); // 没有目标时也递增冷却，但不超过最大值
        }
    }
    tower->setCounter(counter); // 更新塔的冷却计数
}
