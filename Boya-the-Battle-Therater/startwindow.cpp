#include "startwindow.h"
#include "ui_startwindow.h"
#include "gamewindow.h"
#include <QPushButton>
#include <QWindow>

Startwindow::Startwindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::Startwindow)
{
    setFixedSize(1200, 900);

    btn1 = new QPushButton("第一关",this);
    btn2 = new QPushButton("第二关",this);
    btn3 = new QPushButton("第三关",this);
    btn4 = new QPushButton("开关背景音乐",this);

    m1 = new QPushButton(this);
    m2 = new QPushButton(this);
    m3 = new QPushButton(this);
    m4 = new QPushButton(this);
    m5 = new QPushButton(this);
    m6 = new QPushButton(this);
    m7 = new QPushButton(this);
    m8 = new QPushButton(this);
    m9 = new QPushButton(this);
    m10 = new QPushButton(this);
    //ui->setupUi(this);
    setWindowTitle("开始页面");
    //btn->move(344,252);
    m1->resize(6,20);
    m2->resize(6,20);
    m3->resize(6,20);
    m4->resize(6,20);
    m5->resize(6,20);
    m6->resize(6,20);
    m7->resize(6,20);
    m8->resize(6,20);
    m9->resize(6,20);
    m10->resize(6,20);

    btn1->resize(200,80);
    btn2->resize(200,80);
    btn3->resize(200,80);
    btn4->resize(200,80);

    m1->setCheckable(true);
    m2->setCheckable(true);
    m3->setCheckable(true);
    m4->setCheckable(true);
    m5->setCheckable(true);
    m6->setCheckable(true);
    m7->setCheckable(true);
    m8->setCheckable(true);
    m9->setCheckable(true);
    m10->setCheckable(true);

    btn1->setCheckable(true);
    btn2->setCheckable(true);
    btn3->setCheckable(true);
    btn4->setCheckable(true);

    m1->move(10,100);
    m2->move(20,100);
    m3->move(30,100);
    m4->move(40,100);
    m5->move(50,100);
    m6->move(60,100);
    m7->move(70,100);
    m8->move(80,100);
    m9->move(90,100);
    m10->move(100,100);


    btn1->move(500,100);
    btn2->move(500,400);
    btn3->move(500,700);
    btn4->move(10,10);
    connect(btn1,SIGNAL(clicked(bool)),this,SLOT(on_btn1_clicked()));
    connect(btn2,SIGNAL(clicked(bool)),this,SLOT(on_btn2_clicked()));
    connect(btn3,SIGNAL(clicked(bool)),this,SLOT(on_btn3_clicked()));
    connect(btn4,SIGNAL(clicked(bool)),this,SLOT(OnPlayingChanged()));
    connect(m1,SIGNAL(clicked()),this,SLOT(on_m1_clicked()));
    connect(m2,SIGNAL(clicked()),this,SLOT(on_m2_clicked()));
    connect(m3,SIGNAL(clicked()),this,SLOT(on_m3_clicked()));
    connect(m4,SIGNAL(clicked()),this,SLOT(on_m4_clicked()));
    connect(m5,SIGNAL(clicked()),this,SLOT(on_m5_clicked()));
    connect(m6,SIGNAL(clicked()),this,SLOT(on_m6_clicked()));
    connect(m7,SIGNAL(clicked()),this,SLOT(on_m7_clicked()));
    connect(m8,SIGNAL(clicked()),this,SLOT(on_m8_clicked()));
    connect(m9,SIGNAL(clicked()),this,SLOT(on_m9_clicked()));
    connect(m10,SIGNAL(clicked()),this,SLOT(on_m10_clicked()));
    m_pSoundEffect = new QSoundEffect;
    m_pSoundEffect->setSource(QUrl::fromLocalFile(":/image/bgm.wav"));
    m_pSoundEffect->setLoopCount(QSoundEffect::Infinite);
    m_pSoundEffect->setVolume(1.0f);
    m_pSoundEffect->play();
}


Startwindow::~Startwindow()
{
    //delete ui;
}

void Startwindow::on_m1_clicked()
{
    m_pSoundEffect->setVolume(0.1f);
}
void Startwindow::on_m2_clicked()
{
    m_pSoundEffect->setVolume(0.2f);
}
void Startwindow::on_m3_clicked()
{
    m_pSoundEffect->setVolume(0.3f);
}
void Startwindow::on_m4_clicked()
{
    m_pSoundEffect->setVolume(0.4f);
}
void Startwindow::on_m5_clicked()
{
    m_pSoundEffect->setVolume(0.5f);
}
void Startwindow::on_m6_clicked()
{
    m_pSoundEffect->setVolume(0.6f);
}
void Startwindow::on_m7_clicked()
{
    m_pSoundEffect->setVolume(0.7f);
}
void Startwindow::on_m8_clicked()
{
    m_pSoundEffect->setVolume(0.8f);
}
void Startwindow::on_m9_clicked()
{
    m_pSoundEffect->setVolume(0.9f);
}
void Startwindow::on_m10_clicked()
{
    m_pSoundEffect->setVolume(1.0f);
}
void Startwindow::on_btn1_clicked()
{
    //选择关卡按钮点击
    //第一关
    int mapArr_1[12][15] =
    {
    0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    0, 0, 4, 0, 7, 0, 0, 7, 0, 0, 0, 7, 4, 1, 1,
    1, 1, 4, 4, 4, 4, 4, 0, 1, 1, 1, 0, 4, 1, 1,
    1, 1, 1, 1, 1, 7, 4, 0, 0, 0, 0, 7, 4, 1, 1,
    1, 1, 1, 1, 1, 0, 4, 0, 0, 4, 4, 4, 4, 1, 1,
    1, 2, 2, 2, 1, 0, 4, 0, 0, 4, 7, 0, 0, 1, 1,
    1, 2, 3, 2, 1, 0, 4, 0, 0, 4, 4, 4, 6, 1, 1,
    1, 2, 2, 2, 1, 0, 4, 0, 7, 0, 0, 0, 0, 1, 1,
    1, 1, 1, 1, 1, 0, 4, 7, 0, 0, 7, 0, 0, 1, 1,
    3, 3, 3, 3, 3, 0, 4, 4, 4, 4, 4, 4, 4, 4, 5,
    3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
    3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    };
    GameWindow* gamewindow = new GameWindow(mapArr_1,1);
    gamewindow->show();
}
void Startwindow::on_btn2_clicked()
{
    //选择关卡按钮点击
    //第一关
    int mapArr_2[12][15] =
        {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 0, 0, 0, 0, 0, 0, 3, 7, 3, 3, 3, 0, 0, 0,
            1, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 3, 0, 0, 0,
            1, 0, 0, 0, 0, 0, 4, 3, 3, 3, 4, 3, 0, 0, 0,
            1, 0, 0, 0, 0, 7, 4, 3, 7, 3, 4, 3, 0, 0, 0,
            1, 4, 4, 4, 4, 0, 4, 3, 3, 3, 4, 7, 0, 0, 0,
            1, 4, 7, 0, 4, 0, 4, 3, 3, 3, 4, 3, 3, 3, 3,
            1, 4, 0, 0, 4, 7, 4, 3, 3, 3, 4, 3, 3, 3, 3,
            6, 4, 0, 0, 4, 4, 4, 3, 3, 7, 4, 3, 3, 3, 3,
            1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 4, 4, 4, 4, 5,
            1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
            1, 1, 1, 1, 1, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        };
    GameWindow* gamewindow = new GameWindow(mapArr_2,2);
    gamewindow->show();
}
void Startwindow::on_btn3_clicked()
{
    //选择关卡按钮点击
    //第一关
    int mapArr_3[12][15] =
        {
            0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 4, 4, 4, 0, 1,
            1, 1, 1, 1, 7, 1, 0, 0, 0, 0, 4, 7, 4, 0, 1,
            1, 1, 1, 4, 4, 4, 0, 0, 0, 0, 4, 7, 4, 0, 1,
            1, 0, 0, 4, 7, 4, 0, 0, 7, 7, 4, 0, 4, 7, 1,
            6, 4, 0, 4, 7, 4, 4, 4, 4, 4, 4, 0, 4, 4, 5,
            1, 4, 7, 4, 0, 0, 0, 0, 7, 4, 7, 7, 7, 4, 1,
            1, 4, 7, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 4, 1,
            1, 4, 4, 4, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 1,
            1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        };
    GameWindow* gamewindow = new GameWindow(mapArr_3,3);
    gamewindow->show();
}
void Startwindow::OnPlayingChanged()
{
    if(m_pSoundEffect->isPlaying())
    {
        m_pSoundEffect->stop();
    }
    else
    {
        m_pSoundEffect->play();
    }
}
void Startwindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/image/bg.jpg"),QRect());
}

