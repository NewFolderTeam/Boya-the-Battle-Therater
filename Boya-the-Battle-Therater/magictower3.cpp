#include "magictower3.h"
#include <random>

MagicTower3::MagicTower3(const int x,const int y)
    : Tower(x,y)
{
    width = 100, height = 100;   //防御塔宽高
    picturePath = ":/image/mtw3.png";    //防御塔图片路径
    type = 6;
    attackInterval = 8;
    range = 180;
    cost = 220;
    up = 99999999;
    sellPrice = 184;
    attackPowerMin = 41;
    attackPowerMax = 74;
    damageType = 2;
    attackType = 1;
}

//攻击函数
void MagicTower3::Attack(QVector<Enemy*>& enemyVec)
{
    if(attackInterval < 1) attackInterval = 1;  //防御塔攻速上限

    for (auto bullIt = BulletVec.begin(); bullIt != BulletVec.end(); bullIt++)        //子弹
        for (auto enemyIt = enemyVec.begin(); enemyIt != enemyVec.end(); enemyIt++)  //敌人

            if ((*bullIt)->x + 25 >= (*enemyIt)->getCoor().x && (*bullIt)->x <= (*enemyIt)->getCoor().x + (*enemyIt)->getWidth() &&
                (*bullIt)->y + 25 >= (*enemyIt)->getCoor().y && (*bullIt)->y <= (*enemyIt)->getCoor().y + (*enemyIt)->getHeight())
            {
                //击中敌人则减掉敌人血量并删除子弹
                (*enemyIt)->decreaseHealth(attackPower(),getDamageType());
                for (auto enemy : enemyVec) {
                    //巫师塔发射的强力奥术飞弹可以对命中目标周围的敌人造成魔法溅射
                    // 判断敌人是否在溅射范围内，除了当前被击中的敌人
                    if (enemy != *enemyIt && DistBetPoints(enemy->getCoor().x + (enemy->getWidth() >> 1), enemy->getCoor().y + (enemy->getHeight() >> 1),
                                                           (*enemyIt)->getCoor().x + ((*enemyIt)->getWidth() >> 1), (*enemyIt)->getCoor().y + ((*enemyIt)->getHeight() >> 1))
                                                 <= 120) {
                        // 对敌人造成溅射伤害
                        enemy->decreaseHealth(0.2*attackPower(), getDamageType());
                    }
                }
                //向数组中插入击中效果对象
                hitEffectVec.push_back(new HitEffect((*enemyIt)->getCoor().x + ((*enemyIt)->getWidth() >> 1),
                                                     (*enemyIt)->getCoor().y + ((*enemyIt)->getHeight() >> 1), 80, 80,3));

                delete *bullIt;
                BulletVec.erase(bullIt);

                goto outLoop;
            }
outLoop:

    //子弹沿直线移动
    for(auto bull : BulletVec)
    {
        bull->dirFlag ? bull->x += 24 : bull->x -= 24;    //x轴增加

        bull->y = bull->k * bull->x + bull->b;          //y随x改变
    }

    //遍历删除攻击范围外的子弹
    for(auto bullit = BulletVec.begin(); bullit != BulletVec.end(); bullit++)
        if(DistBetPoints((*bullit)->x + 15, (*bullit)->y + 15, x + halfBlockLen, y + halfBlockLen) > range) //子弹和防御塔之间的距离
        {
            delete *bullit;
            BulletVec.erase(bullit);
            break;
        }

    if(enemyVec.empty()) return;    //敌人数组为空直接返回

    if (!targetEnemy)       //目标敌人为空且敌人数组不为空
        targetEnemy = enemyVec.at(enemyVec.size() - 1); //设置目标敌人为范围内最后一个敌人
    else
    {
        if(counter >= attackInterval)    //counter大于一定值时创建子弹
        {
            BulletStr* bull = new BulletStr(x+halfBlockLen, y+10);

            if(!(targetEnemy->getCoor().x - bull->x))   //如果这个数为0则取消创建这个子弹
            {
                delete bull;
                bull = nullptr;
                goto jumpout;
            }

            //计算k、b
            bull->k = (targetEnemy->getCoor().y - bull->y) / (targetEnemy->getCoor().x - bull->x);
            bull->b = targetEnemy->getCoor().y - targetEnemy->getCoor().x * bull->k;
            //确定移动方向
            if(bull->x < targetEnemy->getCoor().x) bull->dirFlag = true;  //是向左

            BulletVec.push_back(bull);  //插入到数组中

            counter = 0;

        jumpout:;
        }

        counter++;
        //如果目标怪物和防御塔的距离超过了射程则将目标怪物重新设为空
        if (DistBetPoints(targetEnemy->getCoor().x, targetEnemy->getCoor().y, x + halfBlockLen, y + halfBlockLen) > range)
            targetEnemy = nullptr;
    }
}

