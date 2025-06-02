#ifndef TOWER_H
#define TOWER_H
#include "enemy.h"
#include "multifilestructure.h"
#include <QString>
#include <QVector>
#include <cmath>

// Forward declaration of Attack class
class Attack;

// 计算两点之间距离宏
#define DistBetPoints(X1, Y1, X2, Y2) \
static_cast<int>(std::abs(std::sqrt(static_cast<double>(((X1) - (X2)) * ((X1) - (X2))) + static_cast<double>(((Y1) - (Y2)) * ((Y1) - (Y2))))))

    class Tower : protected SFCB {
public:
    Tower(const int, const int);
    virtual ~Tower(); // 虚析构函数，清理 Attack 指针

    // Level 相关方法
    int getLevel() const;
    void levelUp();

    // getter/setter，访问protected成员
    int getAttackInterval() const;
    int getAttackPowerMin() const;
    int getAttackPowerMax() const;
    int getDamageType() const;
    int getAttackType() const; // 攻击类型, 1为单体攻击, 2为群体攻击
    int getRange() const;
    bool getRangeFlag() const;
    void setRangeFlag(const bool flag);
    int getCost() const;
    int getUp() const;      // 升级价格 (实函数，返回up成员变量)
    int getSellPrice() const; // 出售价格 (实函数，返回sellPrice成员变量)
    int getType() const; // 种类, 1为弓箭塔, 2为魔法塔
    int getCounter() const;
    void setCounter(const int _counter);
    int attackPower() const;  // 攻击力计算，使用protected的min/max
    QString getPicturePath() const;
    int getHeight() const;
    int getWidth() const;
    Enemy* getTargetEnemy() const;
    void setTargetEnemy(Enemy* enemy); // 设置目标敌人
    QVector<Coor> getAttackCoor() const; // 如果需要从 Attack 获取子弹坐标，可以在这里调用 Attack 的接口
    Coor getCoor() const;
    Coor getDisCoor() const;
    Attack* attack = nullptr;       // 指向 Attack 对象的指针，前向声明
    // 攻击方法，Tower 的 performAttack 是纯虚函数，由子类委托 Attack 对象实现
    virtual void performAttack(QVector<Enemy*>& enemiesInRange, QVector<HitEffect*>& effectsOutput) = 0;
    void setTargetEnemyNull();

protected:
    int disCoorX, disCoorY; // 显示坐标
    int width = 80;         // 防御塔宽，默认值
    int height = 80;        // 防御塔高，默认值
    int attackInterval;     // 攻击间隔
    int attackPowerMin;     // 最小攻击力
    int attackPowerMax;     // 最大攻击力
    int damageType;         // 伤害类型
    int attackType;         // 攻击类型 (1单体, 2群体)
    int range;              // 射程
    int cost;               // 造价 (初始建造价格)
    int up;                 // 升级价 (成员变量，由子类updateAttributesForLevel设置)
    int sellPrice;          // 出售价 (成员变量，由子类updateAttributesForLevel设置)
    int type;               // 类型 (1弓箭塔, 2魔法塔)
    int level = 1;          // 塔的当前等级
    bool displayRangeFlag = false;  // 显示范围标记
    Enemy* targetEnemy = nullptr;   // 目标敌人 (由塔自身维护)
    int counter;            // 攻击计时器 (成员变量)

    QString picturePath;    // 图片路径 (成员变量)

    // 受保护的纯虚函数，用于升级时更新属性
    virtual void updateAttributesForLevel() = 0;
};

#endif // TOWER_H
