/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Startwindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Startwindow)
    {
        if (Startwindow->objectName().isEmpty())
            Startwindow->setObjectName(QString::fromUtf8("Startwindow"));
        Startwindow->resize(800, 600);
        centralwidget = new QWidget(Startwindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Startwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Startwindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        Startwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(Startwindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Startwindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());

        retranslateUi(Startwindow);

        QMetaObject::connectSlotsByName(Startwindow);
    } // setupUi

    void retranslateUi(QMainWindow *Startwindow)
    {
        Startwindow->setWindowTitle(QCoreApplication::translate("Startwindow", "Startwindow", nullptr));
        menu->setTitle(QCoreApplication::translate("Startwindow", "\344\275\240\345\245\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Startwindow: public Ui_Startwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
