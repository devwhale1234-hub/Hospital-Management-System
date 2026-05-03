/********************************************************************************
** Form generated from reading UI file 'hospitalTeam.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOSPITALTEAM_H
#define UI_HOSPITALTEAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hospitalTeamClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *hospitalTeamClass)
    {
        if (hospitalTeamClass->objectName().isEmpty())
            hospitalTeamClass->setObjectName("hospitalTeamClass");
        hospitalTeamClass->resize(600, 400);
        menuBar = new QMenuBar(hospitalTeamClass);
        menuBar->setObjectName("menuBar");
        hospitalTeamClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(hospitalTeamClass);
        mainToolBar->setObjectName("mainToolBar");
        hospitalTeamClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(hospitalTeamClass);
        centralWidget->setObjectName("centralWidget");
        hospitalTeamClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(hospitalTeamClass);
        statusBar->setObjectName("statusBar");
        hospitalTeamClass->setStatusBar(statusBar);

        retranslateUi(hospitalTeamClass);

        QMetaObject::connectSlotsByName(hospitalTeamClass);
    } // setupUi

    void retranslateUi(QMainWindow *hospitalTeamClass)
    {
        hospitalTeamClass->setWindowTitle(QCoreApplication::translate("hospitalTeamClass", "hospitalTeam", nullptr));
    } // retranslateUi

};

namespace Ui {
    class hospitalTeamClass: public Ui_hospitalTeamClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOSPITALTEAM_H
