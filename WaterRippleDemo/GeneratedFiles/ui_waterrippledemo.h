/********************************************************************************
** Form generated from reading UI file 'waterrippledemo.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WATERRIPPLEDEMO_H
#define UI_WATERRIPPLEDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WaterRippleDemoClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QToolButton *toolButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WaterRippleDemoClass)
    {
        if (WaterRippleDemoClass->objectName().isEmpty())
            WaterRippleDemoClass->setObjectName(QStringLiteral("WaterRippleDemoClass"));
        WaterRippleDemoClass->resize(600, 400);
        centralWidget = new QWidget(WaterRippleDemoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(290, 120, 75, 23));
        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(330, 220, 37, 18));
        WaterRippleDemoClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WaterRippleDemoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        WaterRippleDemoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WaterRippleDemoClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WaterRippleDemoClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(WaterRippleDemoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WaterRippleDemoClass->setStatusBar(statusBar);

        retranslateUi(WaterRippleDemoClass);

        QMetaObject::connectSlotsByName(WaterRippleDemoClass);
    } // setupUi

    void retranslateUi(QMainWindow *WaterRippleDemoClass)
    {
        WaterRippleDemoClass->setWindowTitle(QApplication::translate("WaterRippleDemoClass", "WaterRippleDemo", 0));
        pushButton->setText(QApplication::translate("WaterRippleDemoClass", "PushButton", 0));
        toolButton->setText(QApplication::translate("WaterRippleDemoClass", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class WaterRippleDemoClass: public Ui_WaterRippleDemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WATERRIPPLEDEMO_H
