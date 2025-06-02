#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPainter>         //画家类
#include <QMouseEvent>      //鼠标事件
#include "QtCore/qelapsedtimer.h"
#include "selectionframe.h" //选择框
#include "archertower.h"    //弓箭塔
#include "magictower.h"     //法师塔
#include "goblin.h"        //敌人哥布林
#include "orc.h"           //敌人兽人
#include "shaman.h"
#include "ogre.h"
#include <QLabel>           //标签控件
#include <QSoundEffect>
#include <QTimer>

//游戏主界面类
class GameWindow : public QWidget
{
public:
    GameWindow(int[][15],int level);    //构造
    ~GameWindow();

private:

    int levelNumber;    //记录从开始界面传入的关卡编号

    SelectionFrame selectionFrame;      //选择框类

    int mapArr[12][15];                  //地图数组

    int playerHealth = 10;              //玩家生命值

    int money = 600;                   //金钱

    QLabel* moneyLable = new QLabel(this);      //金钱标签
    QLabel *lifelable = new QLabel(this);       //生命标签

    bool allRanges = false;             //显示全部防御塔范围标记

    int counter = 0;                    //计数器

    bool victoryFlag = false;           //胜利标记

    QMap<int, QString> mapValuePicturePathMap;  //地图数组值和对应图片路径map
    QVector<Coor> towerPositionsVec;    //防御塔位置数组
    QVector<QVector<Coor> > enemyPathsVec;       //敌人路径数组
    QVector<Tower*> towerVec;  //防御塔数组
    QVector<Enemy*> enemyVec;  //敌人数组
    QVector<HitEffect*> hitEffectVec;   // 命中效果数组
    QSoundEffect*se1; // 音效1：弓箭塔命中音效
    QSoundEffect*se2; // 音效2：魔法塔命中音效

    // --- 音效播放控制变量 ---
    QElapsedTimer lastSe1PlayTime; // 记录se1上次播放的时间
    QElapsedTimer lastSe2PlayTime; // 记录se2上次播放的时间
    const qint64 minSe1IntervalMs = 250; // 弓箭塔音效最小播放间隔，单位毫秒
    const qint64 minSe2IntervalMs = 250; // 魔法塔音效最小播放间隔，单位毫秒

protected:
    void paintEvent(QPaintEvent*);      //绘图事件
    void drawMap(QPainter&);            //画出地图
    void drawSelectionFrame(QPainter&); //画出选择框
    void drawTower(QPainter&);          //画出防御塔
    void drawEnemy(QPainter&);          //画出敌人
    void drawBull(QPainter&);           //画出子弹
    void drawHitEffect(QPainter&);      //画出打击效果

    void mousePressEvent(QMouseEvent*); //鼠标点击事件

    inline bool spendFunction(Tower*); //支出功能
};

#endif // GAMEWINDOW_H
