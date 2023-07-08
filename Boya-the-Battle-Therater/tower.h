#ifndef TOWER_H
#define TOWER_H
#include "enemy.h"
#include "multifilestructure.h"

//计算两点之间距离宏
#define DistBetPoints(X1, Y1, X2, Y2) \
abs(sqrt((((X1) - (X2)) * ((X1) - (X2))) + (((Y1) - (Y2)) * ((Y1) - (Y2)))))

extern QVector<HitEffect*> hitEffectVec;    //对游戏界面cpp中的hitEffectVec数组做外部变量声明

#include <QString>

class Tower : protected SFCB
{
public:
    Tower(const int,const int);

    int getAttackInterval() const;
    int getAttackPowerMin() const;
    int getAttackPowerMax() const;
    int getDamageType() const;
    int getAttackType() const;
    int getRange() const;
    bool getRangeFlag() const;
    void setRangeFlag(const bool flag);
    int getCost() const;
    int getUp() const;
    int getSellPrice() const;
    int attackPower() const;
    int getType() const;
    QString getPicturePath() const;
    int getHeight() const;
    int getWidth() const;
    Enemy* getTargetEnemy() const;
    QVector<Coor> getAttackCoor() const;
    Coor getCoor() const;
    Coor getDisCoor() const;
    virtual void Attack(QVector<Enemy*>&) = 0;      //攻击函数，参数为敌人对象向量
    void setTargetEnemyNull();


protected:
    int disCoorX, disCoorY; //显示坐标
    int width;//防御塔宽
    int height;//防御塔高
    int attackInterval;//攻击间隔
    int attackPowerMin;//最小攻击力
    int attackPowerMax;//最大攻击力
    int damageType;//伤害类型
    int attackType;//攻击类型
    int range;//射程
    int cost;//造价
    int up;//升级价
    int sellPrice;//出售价
    int type;//类型
    bool displayRangeFlag = false;  //显示范围标记
    Enemy* targetEnemy = nullptr;  //目标敌人
    //子弹结构
    struct BulletStr : public Coor
    {
        double k = 0.0, b = 0.0;    //斜率与截距，用于计算出子弹路径
        bool dirFlag = false;       //移动方向标识
        int attributes;             //属性标识

        //子弹构造
        BulletStr(int x, int y, int attributes = 0) : Coor(x, y), attributes(attributes) {}
    };
    QVector<BulletStr*> BulletVec;  //子弹数组
    int counter = 2;                //计数器


};

#endif // TOWER_H
