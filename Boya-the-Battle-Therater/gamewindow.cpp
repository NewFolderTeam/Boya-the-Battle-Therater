#include "gamewindow.h"
#include <QMap>
#include "generatepath.h"   //生成路径类
#include "qmath.h"
#include "qsoundeffect.h"
#include <QTimer>
#include <QPushButton>

#include "singletargetattack.h"

//鼠标点击区域宏
#define MouClickRegion(X, Y, Width, Height)     \
(ev->x() >= (X) && ev->x() <= (X) + (Width) &&  \
ev->y() >= (Y) && ev->y() <= (Y) + (Height))

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

    // --- 初始化 QElapsedTimer，使其在首次检查时通过 ---
    // start() 方法会启动计时器并重置其时间，下次 elapsed() 就会从0开始计算
    // 在构造函数中调用 restart() 确保它们从游戏开始时就开始计时，
    // 或者在第一次播放音效时调用 restart() 也可以，但在构造函数中初始化更规范。
    lastSe1PlayTime.start();
    lastSe2PlayTime.start();

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
            if(counter >= 0 && counter <= 8){
                enemyVec.push_back(new Goblin(enemyPathsVec[0]));
            }
            if(counter > 12 && counter <= 20)
                enemyVec.push_back(new Orc(enemyPathsVec[0])), enemyVec.push_back(new Goblin(enemyPathsVec[0]));
            if(counter > 24 && counter <= 32)
                enemyVec.push_back(new Goblin(enemyPathsVec[0])), enemyVec.push_back(new Shaman(enemyPathsVec[0]));
            if(counter > 36 && counter <= 44)
                enemyVec.push_back(new Shaman(enemyPathsVec[0])), enemyVec.push_back(new Orc(enemyPathsVec[0]));
            if(counter > 48 && counter <= 56)
                enemyVec.push_back(new Ogre(enemyPathsVec[0]));
            break;
        case 2:
            if(counter >= 0 && counter <= 5){
                enemyVec.push_back(new Shaman(enemyPathsVec[0]));
            }
            if(counter > 5 && counter <= 8)
                enemyVec.push_back(new Orc(enemyPathsVec[0])), enemyVec.push_back(new Goblin(enemyPathsVec[0]));
            if(counter > 8 && counter <= 12)
                enemyVec.push_back(new Goblin(enemyPathsVec[0])), enemyVec.push_back(new Orc(enemyPathsVec[0]));
            if(counter > 12 && counter <= 20)
                enemyVec.push_back(new Ogre(enemyPathsVec[0])), enemyVec.push_back(new Shaman(enemyPathsVec[0]));
            if(counter > 20 && counter <= 34)
                enemyVec.push_back(new Goblin(enemyPathsVec[0]));
            if(counter > 34 && counter <= 42)
                enemyVec.push_back(new Ogre(enemyPathsVec[0])), enemyVec.push_back(new Orc(enemyPathsVec[0]));;
            break;
        case 3:
            if(counter >= 0 && counter <= 25){
                enemyVec.push_back(new Goblin(enemyPathsVec[0]));
            }
            if(counter > 25 && counter <= 30)
                enemyVec.push_back(new Shaman(enemyPathsVec[0])), enemyVec.push_back(new Goblin(enemyPathsVec[1]));
            if(counter > 30 && counter <= 40)
                enemyVec.push_back(new Orc(enemyPathsVec[0])), enemyVec.push_back(new Orc(enemyPathsVec[1]));
            if(counter > 40 && counter <= 52)
                enemyVec.push_back(new Shaman(enemyPathsVec[0])), enemyVec.push_back(new Orc(enemyPathsVec[1]));
            if(counter > 52 && counter <= 60)
                enemyVec.push_back(new Ogre(enemyPathsVec[0])), enemyVec.push_back(new Ogre(enemyPathsVec[1]));
            break;
        }
        counter++;
    });

    // 游戏开始，主定时器
    QTimer* timer2 = new QTimer(this);
    timer2->start(100);

    QTimer* poisonTimer = new QTimer(this);
    poisonTimer->start(500); // 每隔0.5秒结算一次中毒效果
    connect(poisonTimer, &QTimer::timeout, [=]() mutable {
        for (auto enemy : enemyVec) {
            if (enemy->isPoison()) {
                enemy->Poison();
            }
        }
    });

    connect(timer2, &QTimer::timeout, [&]() {
        // 防御塔攻击
        for (auto tower : towerVec) {
            QVector<Enemy*> tempEnemyVec;

            // 遍历敌人数组，将防御塔范围内的所有敌人插入到临时敌人数组中
            for (auto& enemy : enemyVec) {
                if (enemy->getHealth() > 0 && // 只考虑活着的敌人
                    DistBetPoints(enemy->getCoor().x + (enemy->getWidth() >> 1), enemy->getCoor().y + (enemy->getHeight() >> 1),
                                  tower->getCoor().x + halfBlockLen, tower->getCoor().y + halfBlockLen) <= tower->getRange())
                    tempEnemyVec.push_back(enemy);
            }
            // 调用 performAttack 接口，并传入 effectsOutput 向量
            // 注意：hitEffectVec 作为引用传递，允许 Attack 类向其中添加效果
            tower->performAttack(tempEnemyVec, hitEffectVec);
        }

        // 敌人移动结算
        for (auto enemyIt = enemyVec.begin(); enemyIt != enemyVec.end();){
            if ((*enemyIt)->move() || (*enemyIt)->getHealth() <= 0) {
                // 如果敌人移动出地图或者死亡
                for (auto tower : towerVec) {
                    if (tower->getTargetEnemy() == *enemyIt) {
                        tower->setTargetEnemyNull(); // 将目标敌人设置为 null
                    }
                }

                if ((*enemyIt)->move()) { // 敌人逃逸
                    playerHealth -= (*enemyIt)->getDamage();
                    lifelable->setText(QString("生命：%1").arg(playerHealth));
                    if (playerHealth <= 0) { // 检查是否游戏结束
                        // 游戏结束处理：清空敌人，停止定时器等
                        for (auto& enemy : enemyVec) { delete enemy; }
                        enemyVec.clear();
                        timer1->stop();
                        timer2->stop();
                        poisonTimer->stop();
                        // 可以在这里弹出游戏失败对话框
                        // this->close(); // 如果直接关闭窗口
                        break; // 跳出循环，防止访问已删除的元素
                    }
                }
                else { // 敌人死亡
                    money += (*enemyIt)->getReward();
                    moneyLable->setText(QString("金钱：%1").arg(money));
                }

                delete *enemyIt; // 清理敌人对象
                enemyIt = enemyVec.erase(enemyIt); // 从向量中移除，erase 返回下一个有效迭代器
            }
            else {
                ++enemyIt; // 敌人还在，继续下一个
            }
        }

        //显示击中效果
        // 击中效果的 index 递增和删除逻辑保持不变
        for(auto hit = this->hitEffectVec.begin(); hit != this->hitEffectVec.end(); ) {
            if((*hit)->index < 8) { // 共 8 帧
                (*hit)->index++;
                ++hit;
            } else {
                delete *hit;
                hit = this->hitEffectVec.erase(hit);
            }
        }

        if ((playerHealth > 0) && (enemyVec.empty()) && (counter > 50))
            victoryFlag = true; // 显示胜利标签

        update(); // 请求重绘
    });

    //播放背景音乐 (如果需要，在这里添加 QMediaPlayer 或其他音频逻辑)

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
    for(int i=0;i<=11;i++)
    {
        for(int j=0;j<=14;j++)
        {
            if(mapArr[i][j]==7) // 7 代表塔坑位置
            towerPositionsVec.push_back(Coor(j * mapBlockLen, i * mapBlockLen));
            QString path=mapValuePicturePathMap[mapArr[i][j]];
            painter.drawPixmap(mapBlockLen * j, mapBlockLen * i, mapBlockLen, mapBlockLen, path); // 使用常量
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
    for(int i = 1; i < 3; i++) // 1为弓箭塔，2为魔法塔
    {
        painter.drawPixmap(selectionFrame.getChildButtonArr()[i].x, selectionFrame.getChildButtonArr()[i].y,
                           selectionFrame.getButSideLength(), selectionFrame.getButSideLength(),
                           QPixmap(selectionFrame.getChildButtonArr()[i].picturePath));

        //画出防御塔图片
        QString towerPreviewPath;
        if (i == 1) towerPreviewPath = ":/image/atw1.png"; // 弓箭塔1级预览图
        else if (i == 2) towerPreviewPath = ":/image/mtw1.png"; // 魔法塔1级预览图

        painter.drawPixmap(selectionFrame.getChildButtonArr()[i].x + 10, selectionFrame.getChildButtonArr()[i].y + 10,
                           selectionFrame.getButSideLength() - 20, selectionFrame.getButSideLength() - 20,
                           QPixmap(towerPreviewPath));
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
            if (tower->getLevel() < 3) {
                painter.drawText(tower->getCoor().x + 10, tower->getCoor().y - 80, QString("%1").arg(tower->getUp()));
            } else {
                painter.drawText(tower->getCoor().x + 10, tower->getCoor().y - 80, "MAX"); // 最高级显示MAX
            }

            painter.setPen(QPen(Qt::red));
            painter.drawEllipse(QPoint(tower->getCoor().x + halfBlockLen, tower->getCoor().y + halfBlockLen), tower->getRange(), tower->getRange());
        }

        // 绘制塔本身
        painter.drawPixmap(tower->getDisCoor().x, tower->getDisCoor().y, tower->getWidth(), tower->getHeight(), QPixmap(tower->getPicturePath()));
        painter.resetTransform();   //重置调整
    }
}

void GameWindow::drawEnemy(QPainter& painter)   //画出敌人和血条
{
    for(auto enemy : enemyVec)
    {
        // 敌人血条
        if (enemy->getHealth() > 0) { // 只为活着的敌人绘制血条
            if(enemy->isPoison()) painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
            else painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
            painter.drawRect(enemy->getCoor().x, enemy->getCoor().y - 10,
                             enemy->getWidth() * (static_cast<double>(enemy->getHealth()) / enemy->getOrihealth()), 6);
        }

        // 敌人图片
        painter.drawPixmap(enemy->getCoor().x, enemy->getCoor().y, enemy->getWidth(), enemy->getHeight(), enemy->getPicturePath());

        // 画出中毒特效
        if(enemy->isPoison())
            painter.drawPixmap(enemy->getCoor().x, enemy->getCoor().y, enemy->getWidth(), enemy->getHeight(), QPixmap(":/image/poisoned_effect.png"));
    }
}

void GameWindow::drawBull(QPainter& painter) {
    for (auto tower : towerVec) {
        SingleTargetAttack* singleTargetAttack = dynamic_cast<SingleTargetAttack*>(tower->attack);
        if (singleTargetAttack) {
            const QVector<BulletStr*>& bullets = singleTargetAttack->getBulletVec();
            for (const auto& bullet : bullets) {
                QString bulletPath;
                if (tower->getDamageType() == 2) { // 魔法伤害
                    bulletPath = ":/image/m_arrow.png"; // 魔法箭/子弹
                } else { // 物理伤害
                    bulletPath = ":/image/arrow.png"; // 物理箭/子弹
                }
                painter.drawPixmap(bullet->x, bullet->y, 15, 15, QPixmap(bulletPath));
            }
        }
    }
}

void GameWindow::drawHitEffect(QPainter& painter)   //画出命中效果
{
    for (auto hit : this->hitEffectVec)
    {
        // --- 音效播放频率控制逻辑 ---
        bool se1Played = false;
        bool se2Played = false;

        switch(hit->type){
        case 1: // 弓箭塔命中效果
            painter.drawPixmap(hit->x - (hit->width >> 1), hit->y - (hit->height >> 1), hit->width, hit->height, QPixmap(":/image/arrowHit.png"));
            // 检查自上次se1播放以来是否已超过最小间隔
            if (lastSe1PlayTime.elapsed() >= minSe1IntervalMs) {
                se1->play();
                lastSe1PlayTime.restart(); // 重置计时器
                se1Played = true; // 标记se1已播放
            }
            break;
        case 2: // 魔法塔（非溅射）命中效果
            painter.drawPixmap(hit->x - (hit->width >> 1), hit->y - (hit->height >> 1), hit->width, hit->height, QPixmap(":/image/magicHit.png"));
            // 检查自上次se2播放以来是否已超过最小间隔
            if (lastSe2PlayTime.elapsed() >= minSe2IntervalMs) {
                se2->play();
                lastSe2PlayTime.restart(); // 重置计时器
                se2Played = true; // 标记se2已播放
            }
            break;
        case 3: // 魔法塔溅射效果
            painter.drawPixmap(hit->x - (hit->width >> 1), hit->y - (hit->height >> 1), hit->width, hit->height, QPixmap(":/image/magic_splash.png"));
            // 检查自上次se2播放以来是否已超过最小间隔
            if (lastSe2PlayTime.elapsed() >= minSe2IntervalMs) {
                se2->play();
                lastSe2PlayTime.restart(); // 重置计时器
                se2Played = true; // 标记se2已播放
            }
            break;
        }
    }
}

//绘图函数
void GameWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    // 设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);

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
    if (playerHealth <= 0 || victoryFlag) return; // 游戏结束则不处理点击

    if (ev->button() != Qt::LeftButton)
        return;

    bool actionHandledThisClick = false; // 用于标记本次点击是否已被某个UI元素处理

    // 1. 处理已部署塔的升级/出售按钮
    for (auto it = towerVec.begin(); it != towerVec.end(); ) {
        Tower* currentTower = *it;
        if (currentTower->getRangeFlag()) {
            // 升级按钮点击
            if (MouClickRegion(currentTower->getCoor().x + 10, currentTower->getCoor().y - 80, 60, 60)) {
                actionHandledThisClick = true;
                if (currentTower->getLevel() < 3 && money >= currentTower->getUp()) {
                    money -= currentTower->getUp();
                    moneyLable->setText(QString("金钱：%1").arg(money));
                    currentTower->levelUp();
                }
                update();
                return;
            }

            // 出售按钮点击
            if (MouClickRegion(currentTower->getCoor().x + 10, currentTower->getCoor().y + 100, 60, 60)) {
                actionHandledThisClick = true;
                money += currentTower->getSellPrice();
                moneyLable->setText(QString("金钱：%1").arg(money));
                delete currentTower;
                it = towerVec.erase(it);
                update();
                return;
            }
            ++it;
        } else {
            ++it;
        }
    }

    // 2. 处理建造选择框中的按钮
    if (selectionFrame.getDisplay()) {
        for (int i = 1; i < 3; i++) {
            if (MouClickRegion(
                    selectionFrame.getChildButtonArr()[i].x, selectionFrame.getChildButtonArr()[i].y,
                    selectionFrame.getButSideLength(), selectionFrame.getButSideLength()))
            {
                actionHandledThisClick = true;
                const Coor towerPoscoor(
                    selectionFrame.getCoor().x + ((selectionFrame.getSelSideLength() - mapBlockLen) >> 1),
                    selectionFrame.getCoor().y + ((selectionFrame.getSelSideLength() - mapBlockLen) >> 1));

                Tower* tempTowerObj = nullptr;
                if (i == 1) tempTowerObj = new ArcherTower(towerPoscoor.x, towerPoscoor.y, 1);
                else if (i == 2) tempTowerObj = new MagicTower(towerPoscoor.x, towerPoscoor.y, 1);

                if (tempTowerObj) {
                    if (!spendFunction(tempTowerObj)) {
                        delete tempTowerObj;
                    } else {
                        towerVec.push_back(tempTowerObj);
                    }
                }
                selectionFrame.setDisplay(false);
                update();
                return;
            }
        }
    }

    // 3. 处理点击塔坑 (可放置塔的位置)
    if (!actionHandledThisClick) {
        for (const auto& towerPosition : towerPositionsVec) {
            if (MouClickRegion(towerPosition.x, towerPosition.y, mapBlockLen, mapBlockLen)) {
                actionHandledThisClick = true;
                Tower* clickedTower = nullptr;
                for (auto tower : towerVec) {
                    if (tower->getCoor().x == towerPosition.x && tower->getCoor().y == towerPosition.y) {
                        clickedTower = tower;
                        break;
                    }
                }

                for (auto tower : towerVec) {
                    tower->setRangeFlag(false);
                }
                selectionFrame.setDisplay(false);

                if (clickedTower) {
                    clickedTower->setRangeFlag(!clickedTower->getRangeFlag());
                } else {
                    selectionFrame.setCoor(
                        towerPosition.x - ((selectionFrame.getSelSideLength() - mapBlockLen) >> 1),
                        towerPosition.y - ((selectionFrame.getSelSideLength() - mapBlockLen) >> 1));
                    selectionFrame.setDisplay(true);
                }
                update();
                return;
            }
        }
    }

    // 4. 如果点击未被任何上述逻辑处理 (即点击了地图空白区域)
    if (!actionHandledThisClick) {
        bool stateChanged = false;
        for (auto tower : towerVec) {
            if (tower->getRangeFlag()) {
                tower->setRangeFlag(false);
                stateChanged = true;
            }
        }
        if (selectionFrame.getDisplay()) {
            selectionFrame.setDisplay(false);
            stateChanged = true;
        }
        if (stateChanged) {
            update();
        }
    }
}

//析构
GameWindow::~GameWindow()
{
    //释放内存
    for(auto it = towerVec.begin(); it != towerVec.end(); ++it)
    {
        delete *it;
    }
    towerVec.clear();

    for(auto it = enemyVec.begin(); it != enemyVec.end(); ++it)
    {
        delete *it;
    }
    enemyVec.clear();

    for(auto it = this->hitEffectVec.begin(); it != this->hitEffectVec.end(); ++it)
    {
        delete *it;
    }
    this->hitEffectVec.clear();

    // 清理 QLabel 和 QSoundEffect
    delete moneyLable;
    delete lifelable;
    delete se1;
    delete se2;
}
