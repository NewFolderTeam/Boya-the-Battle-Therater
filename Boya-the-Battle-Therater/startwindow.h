#include <QMainWindow>
#include <QLabel>
#include <QtWidgets>
#include <QAction>
#include <QMouseEvent>
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class Startwindow; }
QT_END_NAMESPACE

class Startwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Startwindow(QWidget *parent = nullptr);
    ~Startwindow();
private slots:
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_m1_clicked();
    void on_m2_clicked();
    void on_m3_clicked();
    void on_m4_clicked();
    void on_m5_clicked();
    void on_m6_clicked();
    void on_m7_clicked();
    void on_m8_clicked();
    void on_m9_clicked();
    void on_m10_clicked();
    void OnPlayingChanged();
private:
    //Ui::Startwindow *ui;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *m1;
    QPushButton *m2;
    QPushButton *m3;
    QPushButton *m4;
    QPushButton *m5;
    QPushButton *m6;
    QPushButton *m7;
    QPushButton *m8;
    QPushButton *m9;
    QPushButton *m10;
    QSoundEffect*m_pSoundEffect;
protected:
    void paintEvent(QPaintEvent*);      //绘图事件
};
