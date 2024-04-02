/********************************************************************************
** Form generated from reading UI file 'WhiteRabbitMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHITERABBITMAINWINDOW_H
#define UI_WHITERABBITMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WhiteRabbitMainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WhiteRabbitMainWindow)
    {
        if (WhiteRabbitMainWindow->objectName().isEmpty())
            WhiteRabbitMainWindow->setObjectName(QString::fromUtf8("WhiteRabbitMainWindow"));
        WhiteRabbitMainWindow->resize(800, 600);
        centralwidget = new QWidget(WhiteRabbitMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 511, 21));
        WhiteRabbitMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WhiteRabbitMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        WhiteRabbitMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(WhiteRabbitMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        WhiteRabbitMainWindow->setStatusBar(statusbar);

        retranslateUi(WhiteRabbitMainWindow);

        QMetaObject::connectSlotsByName(WhiteRabbitMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *WhiteRabbitMainWindow)
    {
        WhiteRabbitMainWindow->setWindowTitle(QApplication::translate("WhiteRabbitMainWindow", "WhiteRabbitMainWindow", nullptr));
        label->setText(QApplication::translate("WhiteRabbitMainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WhiteRabbitMainWindow: public Ui_WhiteRabbitMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHITERABBITMAINWINDOW_H
