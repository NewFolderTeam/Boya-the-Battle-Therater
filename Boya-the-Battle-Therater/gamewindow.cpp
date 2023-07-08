#include "gamewindow.h"
#include <QMap>
#include "generatepath.h"   //生成路径类
#include "qmath.h"
#include "qsoundeffect.h"
#include <QTimer>
#include <QPushButton>

//鼠标点击区域宏
#define MouClickRegion(X, Y, Width, Height)     \
(ev->x() >= (X) && ev->x() <= (X) + (Width) &&  \
ev->y() >= (Y) && ev->y() <= (Y) + (Height))

QVector<HitEffect*> hitEffectVec;   //命中效果数组

inline bool GameWindow::spendFunction(Tower* tempPtr)  //支出功能
{
    if(!tempPtr) return false;


    if(money - tempPtr->getCost() >= 0)
    {
        money -= tempPtr->getCost();
        moneyLable->setText(QString("金钱：%1").arg(money));
        return true;    //成功支出
    }
    else
    {
        delete tempPtr;
        return false;
    }
}

GameWindow::GameWindow(int mapArr[12][15],int level)
{
    setFixedSize(1200, 900);//分辨率
    setWindowTitle("博雅战斗剧场");
    levelNumber=level;
    //把参数数组拷贝给成员数组
    memcpy(this->mapArr, mapArr, sizeof(this->mapArr));

    //地图数组值对应的图片路径
    mapValuePicturePathMap.insert(0, ":/image/py.jpg");
    mapValuePicturePathMap.insert(1, ":/image/sl.jpg");
    mapValuePicturePathMap.insert(2, ":/image/ql.jpg");
    mapValuePicturePathMap.insert(3, ":/image/sy.jpg");
    mapValuePicturePathMap.insert(4, ":/image/road.jpg");
    mapValuePicturePathMap.insert(5, ":/image/cgk.jpg");
    mapValuePicturePathMap.insert(6, ":/image/dby.jpg");
    mapValuePicturePathMap.insert(7, ":/image/dj.jpg");

    se1 = new QSoundEffect;
    se1->setSource(QUrl::fromLocalFile(":/image/ht1.wav"));
    se1->setVolume(0.5f);
    se2 = new QSoundEffect;
    se2->setSource(QUrl::fromLocalFile(":/image/ht2.wav"));
    se2->setVolume(0.5f);
    //得到生成路径
    QVector<QVector<int*> > tempVec = GeneratePath().getPathVec(mapArr);

    //将int*类型路径转换为Coor
    for (int j = 0; j < tempVec.size(); j++)          //每条路径
    {
        QVector<Coor> enemytempVec_1;
        for (int i = 0; i < tempVec[j].size(); i++)   //每个元素
            enemytempVec_1.push_back({ tempVec[j][i][1] * mapBlockLen, tempVec[j][i][0] * mapBlockLen});

        enemyPathsVec.push_back(enemytempVec_1);
    }

    //用于产生怪物定时器
    QTimer* timer1 = new QTimer(this);
    timer1->start(2000);

    //金钱标签
    QPalette pe;
    pe.setColor(QPalette::Base,Qt::black);
    pe.setColor(QPalette::WindowText,Qt::yellow);
    moneyLable->setPalette(pe);
    moneyLable->move(20, 40);
    moneyLable->setFont(QFont("黑体", 20));
    moneyLable->setText(QString("金钱：%1").arg(money));

    //生命标签
    pe.setColor(QPalette::Base,Qt::black);
    pe.setColor(QPalette::WindowText,Qt::red);
    lifelable->setPalette(pe);
    lifelable->move(20, 90);
    lifelable->setFont(QFont("黑体", 20));
    lifelable->setText(QString("生命：%1").arg(playerHealth));

    connect(timer1,&QTimer::timeout,[=]() mutable
    {
        switch (levelNumber)     //检查传入的地图数组有几条路径，目前根据路径数区分关卡
        {
        case 1://一条路径时：出怪规划
            if(counter >= 0 && counter <= 5){
                enemyVec.push_back(new Goblin(enemyPathsVec[0]));
            }
            else if(counter >= 5 && counter <= 8)
                enemyVec.push_back(new Shaman(enemyPathsVec[0])), enemyVec.push_back(new Goblin(enemyPathsVec[0]));
            else if(counter >= 8 && counter <= 12)
                enemyVec.push_back(new Goblin(enemyPathsVec[0])), enemyVec.push_back(new Orc(enemyPathsVec[0]));
            else if(counter >= 12 && counter <= 20)
                enemyVec.push_back(new Shaman(enemyPathsVec[0])), enemyVec.push_back(new Goblin(enemyPathsVec[0]));
            else if(counter >= 20 && counter <= 34)
                enemyVec.push_back(new Ogre(enemyPathsVec[0])),enemyVec.push_back(new Orc(enemyPathsVec[0]));
            break;
        case 2:
            if(counter >= 0 && counter <= 5){
                enemyVec.push_back(new Shaman(enemyPathsVec[0]));
            }
            else if(counter >= 5 && counter <= 8)
                enemyVec.push_back(new Orc(enemyPathsVec[0])), enemyVec.push_back(new Goblin(enemyPathsVec[0]));
            else if(counter >= 8 && counter <= 12)
                enemyVec.push_back(new Goblin(enemyPathsVec[0])), enemyVec.push_back(new Orc(enemyPathsVec[0]));
            else if(counter >= 12 && counter <= 20)
                enemyVec.push_back(new Ogre(enemyPathsVec[0])), enemyVec.push_back(new Shaman(enemyPathsVec[0]));
            else if(counter >= 20 && counter <= 34)
                enemyVec.push_back(new Goblin(enemyPathsVec[0]));
            else if(counter >= 34 && counter <= 42)
                enemyVec.push_back(new Ogre(enemyPathsVec[0])), enemyVec.push_back(new Orc(enemyPathsVec[0]));;
            break;
        case 3:
            if(counter >= 0 && counter <= 25){
                enemyVec.push_back(new Goblin(enemyPathsVec[0]));
            }
            else if(counter >= 25 && counter <= 30)
                enemyVec.push_back(new Shaman(enemyPathsVec[0])), enemyVec.push_back(new Goblin(enemyPathsVec[1]));
            else if(counter >= 30 && counter <= 40)
                enemyVec.push_back(new Orc(enemyPathsVec[0])), enemyVec.push_back(new Orc(enemyPathsVec[1]));
            else if(counter >= 40 && counter <= 52)
                enemyVec.push_back(new Shaman(enemyPathsVec[0])), enemyVec.push_back(new Orc(enemyPathsVec[1]));
            else if(counter >= 52 && counter <= 60)
                enemyVec.push_back(new Ogre(enemyPathsVec[0])), enemyVec.push_back(new Ogre(enemyPathsVec[1]));
            break;
        }
        counter++;
    });

    // 游戏开始，主定时器
    QTimer* timer2 = new QTimer(this);
    timer2->start(100);

    QTimer* poisonTimer = new QTimer(this);
    poisonTimer->start(1000); // 每隔1秒结算一次中毒效果
    connect(poisonTimer, &QTimer::timeout, [=]() mutable {
        for (auto enemy : enemyVec) {
            if (enemy->isPoision()) {
                enemy->Poision();
            }
        }
    });

    connect(timer2, &QTimer::timeout, [&]() {
    // 防御塔攻击
    for (auto tower : towerVec) {
        QVector<Enemy*> tempEnemyVec;

        for (auto& enemy : enemyVec) { // 遍历敌人数组，将防御塔范围内的所有敌人插入到临时敌人数组中
            if (DistBetPoints(enemy->getCoor().x + (enemy->getWidth() >> 1), enemy->getCoor().y + (enemy->getHeight() >> 1),
                tower->getCoor().x + halfBlockLen, tower->getCoor().y + halfBlockLen) <= tower->getRange())
                tempEnemyVec.push_back(enemy);
        }

        tower->Attack(tempEnemyVec); // 把范围内的敌人作为参数传递给防御塔
    }

    // 敌人移动结算
    for (auto enemyIt = enemyVec.begin(); enemyIt != enemyVec.end();) {

        if ((*enemyIt)->move() || (*enemyIt)->getHealth() <= 0) {
            for (auto tower : towerVec) {
                if (tower->getTargetEnemy() == *enemyIt) {
                    tower->setTargetEnemyNull();
                }
            }

            if ((*enemyIt)->move()) {
                playerHealth -= (*enemyIt)->getDamage();
                lifelable->setText(QString("生命：%1").arg(playerHealth));
                if (!playerHealth) {
                    delete *enemyIt;
                    enemyIt = enemyVec.erase(enemyIt);
                    this->close();
                    break;
                }
            }
            else {
                money += (*enemyIt)->getReward();
                moneyLable->setText(QString("金钱：%1").arg(money));
            }

            delete *enemyIt;
            enemyIt = enemyVec.erase(enemyIt);
        }
        else {
            ++enemyIt;
        }
    }

    //显示击中效果
    for(auto hit = hitEffectVec.begin(); hit != hitEffectVec.end(); hit++)
        if((*hit)->index <= 7)
            (*hit)->index++;
    //删除击中效果,不同时显示太多
    for(auto hit = hitEffectVec.begin(); hit != hitEffectVec.end(); hit++)
        if((*hit)->index >= 8)
        {
            delete *hit;
            hitEffectVec.erase(hit);
            break;
        }

    if ((playerHealth > 0) && (enemyVec.empty()) && (counter > 50))
        victoryFlag = true; // 显示胜利标签

    update();
    repaint();
    });

    //播放背景音乐

    //范围按钮
    QPushButton* rangesBtn = new QPushButton(this);
    rangesBtn->setGeometry(20, 140, 100, 40);
    rangesBtn->setFont(QFont("黑体", 10));
    rangesBtn->setText("显示范围");

    connect(rangesBtn, &QPushButton::clicked,[=]()
    {
        if(allRanges) rangesBtn->setText("显示范围"), allRanges = false;
        else rangesBtn->setText("隐藏范围"), allRanges = true;
        update();
    });
}

//画出地图
void GameWindow::drawMap(QPainter& painter)
{
    Coor towerCoor;
    for(int i=0;i<=11;i++)
    {
        for(int j=0;j<=14;j++)
        {
            if(mapArr[i][j]==7)
            towerPositionsVec.push_back(Coor(j * mapBlockLen, i * mapBlockLen));
            QString path=mapValuePicturePathMap[mapArr[i][j]];
            //QPainter* tempPainter = new QPainter(this);
            painter.drawPixmap(80*j,80*i,80,80,path);
        }
    }
}

//画出选择框
void GameWindow::drawSelectionFrame(QPainter& painter)
{
    if(!selectionFrame.getDisplay()) return;    //选择框显示状态为假则返回

    //画出选择框
    painter.drawPixmap(selectionFrame.getCoor().x, selectionFrame.getCoor().y,
                       selectionFrame.getSelSideLength(), selectionFrame.getSelSideLength(),
                       QPixmap(":/image/selection.png"));

    //画出选中标志2
    painter.drawPixmap(selectionFrame.getCoor().x + ((selectionFrame.getSelSideLength() - mapBlockLen) >> 1),
                       selectionFrame.getCoor().y + ((selectionFrame.getSelSideLength() - mapBlockLen) >> 1),
                       mapBlockLen, mapBlockLen, QPixmap(":/image/Check_the_tower_effect.png"));

    //画出子按钮
    for(int i = 1; i < 3; i++)
    {
        painter.drawPixmap(selectionFrame.getChildButtonArr()[i].x, selectionFrame.getChildButtonArr()[i].y,
                           selectionFrame.getButSideLength(), selectionFrame.getButSideLength(),
                           QPixmap(selectionFrame.getChildButtonArr()[i].picturePath));

        //画出防御塔图片
        painter.drawPixmap(selectionFrame.getChildButtonArr()[i].x + 10, selectionFrame.getChildButtonArr()[i].y + 10,
                           selectionFrame.getButSideLength() - 20, selectionFrame.getButSideLength() - 20,
                           QPixmap(selectionFrame.getTowerPicturePathArr()[i]));
    }
}

//画出防御塔、按钮、防御塔攻击范围
void GameWindow::drawTower(QPainter& painter)
{
    for(auto &tower : towerVec)
    {
        painter.setBrush(QBrush(Qt::NoBrush));  //清除画刷样式
        //画出全局防御塔范围
        if(allRanges)
            painter.setPen(QPen(Qt::black)),
            painter.drawEllipse(QPoint(tower->getCoor().x + halfBlockLen, tower->getCoor().y + halfBlockLen), tower->getRange(), tower->getRange());

        //画出被点击防御塔的范围和升级按钮图片
        if(tower->getRangeFlag())
        {
            painter.drawPixmap(tower->getCoor().x + 10, tower->getCoor().y - 80, 60, 60, QPixmap(":/image/up.jpg")); //升级按钮
            painter.drawPixmap(tower->getCoor().x + 10, tower->getCoor().y + 100, 60, 60, QPixmap(":/image/down.jpg")); //出售按钮
            painter.setFont(QFont("黑体", 16));
            painter.drawText(tower->getCoor().x + 10, tower->getCoor().y - 80, QString("%1").arg(tower->getUp()));    //画出升级成本文字
            painter.setPen(QPen(Qt::red));
            painter.drawEllipse(QPoint(tower->getCoor().x + halfBlockLen, tower->getCoor().y + halfBlockLen), tower->getRange(), tower->getRange());
        }

        painter.drawPixmap(tower->getDisCoor().x-15, tower->getDisCoor().y-20, tower->getWidth(), tower->getHeight(), QPixmap(tower->getPicturePath()));
        painter.resetTransform();   //重置调整
    }
}

void GameWindow::drawEnemy(QPainter& painter)   //画出敌人和血条
{
    for(auto enemy : enemyVec)
    {
        (enemy->getHealth()) > 0?
            painter.setBrush(QBrush(Qt::green, Qt::SolidPattern)) :     //设置画刷形式
            painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
        painter.drawRect(enemy->getCoor().x, enemy->getCoor().y - 10, enemy->getWidth() * (enemy->getHealth())/(enemy->getOrihealth()), 6);    //画出敌人血条
        painter.drawPixmap(enemy->getCoor().x, enemy->getCoor().y, enemy->getWidth(), enemy->getHeight(), enemy->getPicturePath());
        //画出中毒特效
        if(enemy->isPoision())
            painter.drawPixmap(enemy->getCoor().x, enemy->getCoor().y, enemy->getWidth(), enemy->getHeight(), enemy->getPoisionedPath());
    }
}

void GameWindow::drawBull(QPainter& painter) {
    for (auto tower : towerVec) {
        if (tower->getDamageType() == 2) {
            for (auto bullcoor : tower->getAttackCoor()) {
                // 保存当前绘图状态
                painter.save();

                // 绘制子弹
                painter.drawPixmap(bullcoor.x, bullcoor.y, 15, 15, QPixmap(":/image/m_arrow.png"));

                // 恢复绘图状态
                painter.restore();
            }
        } else {
            for (auto bullcoor : tower->getAttackCoor()) {
                // 保存当前绘图状态
                painter.save();

                // 绘制子弹
                painter.drawPixmap(bullcoor.x, bullcoor.y, 15, 15, QPixmap(":/image/arrow.png"));

                // 恢复绘图状态
                painter.restore();
            }
        }
    }
}

void GameWindow::drawHitEffect(QPainter& painter)   //画出命中效果
{
    for (auto hit : hitEffectVec)//根据防御塔画出命中效果
    {
        switch(hit->type){
        case 1:
            painter.drawPixmap(hit->x - 40, hit->y - 40, hit->width, hit->height, QPixmap(QString(":/image/arrowHit.png").arg(hit->index)));
            se1->play();
            break;
        case 2:
            painter.drawPixmap(hit->x - 40, hit->y - 40, hit->width, hit->height, QPixmap(QString(":/image/magicHit.png").arg(hit->index)));
            se2->play();
            break;
        case 3:
            painter.drawPixmap(hit->x - 40, hit->y - 40, hit->width, hit->height, QPixmap(QString(":/image/magic_splash.png").arg(hit->index)));
            se2->play();
            break;
        }
    }
}

//绘图函数
void GameWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    drawMap(painter);       //画出地图
    drawBull(painter);      //画出子弹
    drawEnemy(painter);     //画出怪物
    drawTower(painter);     //画出防御塔
    drawHitEffect(painter); //画出打击效果

    drawSelectionFrame(painter);    //画出选择框

    if(victoryFlag)         //画出游戏胜利提示
    painter.setPen(QPen(Qt::white)), painter.setFont(QFont("楷体", 110)), painter.drawText(176, 350, "游戏胜利");

}

void GameWindow::mousePressEvent(QMouseEvent* ev)
{
if (ev->button() != Qt::LeftButton) //鼠标左键点击
    return;

for (auto it = towerVec.begin(); it != towerVec.end(); ) {
    auto tower = *it;
    if (tower->getRangeFlag()) {
        // 升级按钮的边长为70
        if (MouClickRegion(tower->getCoor().x + 10, tower->getCoor().y - 80, 60, 60)) {
            if (money - tower->getUp() < 0)
                break;

            money -= tower->getUp();
            moneyLable->setText(QString("金钱：%1").arg(money));

            int x1 = tower->getDisCoor().x - ((int)(tower->getWidth() - tower->getWidth()) >> 1);
            int y1 = tower->getDisCoor().y - ((int)(tower->getHeight() - tower->getHeight()) >> 1);
            int tp = tower->getType();

            it = towerVec.erase(it);  // 更新迭代器位置

            // 创建新塔对象并设置属性
            if (tp == 1) {
                Tower* newTower = new ArcherTower2(x1, y1);
                towerVec.push_back(newTower);
            } else if (tp == 2) {
                Tower* newTower = new ArcherTower3(x1, y1);
                towerVec.push_back(newTower);
            } else if (tp == 4) {
                Tower* newTower = new MagicTower2(x1, y1);
                towerVec.push_back(newTower);
            } else if (tp == 5) {
                Tower* newTower = new MagicTower3(x1, y1);
                towerVec.push_back(newTower);
            }

            break;
        }

        // 拆除按钮点击
        if (MouClickRegion(tower->getCoor().x + 10, tower->getCoor().y + 100, 60, 60)) {
            money += tower->getSellPrice();
            it = towerVec.erase(it);  // 更新迭代器位置
            break;

        }
    }
    ++it;  // 增加迭代器位置
    }

    //选择框为显示状态时判断子按钮点击
    if(selectionFrame.getDisplay())
    {
    for (int i = 1; i < 3; i++)
            if (MouClickRegion (
                    selectionFrame.getChildButtonArr()[i].x, selectionFrame.getChildButtonArr()[i].y,
                    selectionFrame.getButSideLength(), selectionFrame.getButSideLength()))
            {
                //防御塔位置原坐标
                const Coor towerPoscoor(selectionFrame.getCoor().x + ((selectionFrame.getSelSideLength() - mapBlockLen) >> 1),
                                        selectionFrame.getCoor().y + ((selectionFrame.getSelSideLength() - mapBlockLen) >> 1));

                //根据i将不同的防御塔对象插入到数组
                Tower* tempTowerObj = nullptr;
                switch (i) {
                case 1:
                    tempTowerObj = new ArcherTower1(towerPoscoor.x, towerPoscoor.y);
                    if(!spendFunction(tempTowerObj)) break;

                    towerVec.push_back(tempTowerObj);
                    break;
                case 2:
                    tempTowerObj = new MagicTower1(towerPoscoor.x, towerPoscoor.y);
                    if(!spendFunction(tempTowerObj)) break;

                    towerVec.push_back(tempTowerObj);
                    break;
                }

                selectionFrame.setDisplay(false);
                update();
                return;
            }
    }


    //判断防御塔位置的点击
    for (auto towerPosition : towerPositionsVec)
    if (MouClickRegion(towerPosition.x, towerPosition.y, mapBlockLen, mapBlockLen))
    {
            for (auto tower : towerVec) //检查当前位置上是否已经有防御塔
                if (tower->getCoor().x == towerPosition.x && tower->getCoor().y == towerPosition.y) //有防御塔则显示该防御塔范围、显示升级按钮
                {
                    for (auto tower : towerVec)
                        if (tower->getRangeFlag()) tower->setRangeFlag(false); //先取消显示所有防御塔的范围

                    tower->setRangeFlag(true);          //设置被点击的显示范围标记为真
                    selectionFrame.setDisplay(false);
                    update();
                    return;
                }

            for (auto tower : towerVec)
                if (tower->getRangeFlag()) tower->setRangeFlag(false);

            //设置选择框坐标
            selectionFrame.setCoor
                (towerPosition.x - ((selectionFrame.getSelSideLength() - mapBlockLen) >> 1),
                 towerPosition.y - ((selectionFrame.getSelSideLength() - mapBlockLen) >> 1));
            selectionFrame.setDisplay(true);    //设置选择框的显示状态为true

            update();   //调用绘图函数
            return;
    }

    for (auto tower : towerVec)     //点击其他地方取消显示防御塔范围
    if (tower->getRangeFlag()) { tower->setRangeFlag(false); break; }

    selectionFrame.setDisplay(false);   //点击其他地方则取消显示选择框
    update();

}

//析构
GameWindow::~GameWindow()
{
    //释放内存
    for(auto it = towerVec.begin(); it != towerVec.end(); it++) //防御塔对象数组
    {
    delete *it;
    }

    towerVec.clear();

    for(auto it = enemyVec.begin(); it != enemyVec.end(); it++) //敌人对象数组
    {
    delete *it;
    }

    enemyVec.clear();

    for(auto it = hitEffectVec.begin(); it != hitEffectVec.end(); it++) //命中效果数组
    {
    delete *it;
    }

    hitEffectVec.clear();

}
