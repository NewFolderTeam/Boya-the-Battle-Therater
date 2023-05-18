/********************************************************************************
** Form generated from reading UI file 'hellodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLODIALOG_H
#define UI_HELLODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Hellodialog
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Hellodialog)
    {
        if (Hellodialog->objectName().isEmpty())
            Hellodialog->setObjectName(QString::fromUtf8("Hellodialog"));
        Hellodialog->resize(800, 600);
        centralwidget = new QWidget(Hellodialog);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Hellodialog->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Hellodialog);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        Hellodialog->setMenuBar(menubar);
        statusbar = new QStatusBar(Hellodialog);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Hellodialog->setStatusBar(statusbar);

        retranslateUi(Hellodialog);

        QMetaObject::connectSlotsByName(Hellodialog);
    } // setupUi

    void retranslateUi(QMainWindow *Hellodialog)
    {
        Hellodialog->setWindowTitle(QCoreApplication::translate("Hellodialog", "Hellodialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Hellodialog: public Ui_Hellodialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLODIALOG_H
