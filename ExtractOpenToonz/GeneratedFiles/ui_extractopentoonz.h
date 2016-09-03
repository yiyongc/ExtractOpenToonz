/********************************************************************************
** Form generated from reading UI file 'extractopentoonz.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRACTOPENTOONZ_H
#define UI_EXTRACTOPENTOONZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExtractOpenToonzClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ExtractOpenToonzClass)
    {
        if (ExtractOpenToonzClass->objectName().isEmpty())
            ExtractOpenToonzClass->setObjectName(QStringLiteral("ExtractOpenToonzClass"));
        ExtractOpenToonzClass->resize(600, 400);
        menuBar = new QMenuBar(ExtractOpenToonzClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ExtractOpenToonzClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ExtractOpenToonzClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ExtractOpenToonzClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ExtractOpenToonzClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ExtractOpenToonzClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ExtractOpenToonzClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ExtractOpenToonzClass->setStatusBar(statusBar);

        retranslateUi(ExtractOpenToonzClass);

        QMetaObject::connectSlotsByName(ExtractOpenToonzClass);
    } // setupUi

    void retranslateUi(QMainWindow *ExtractOpenToonzClass)
    {
        ExtractOpenToonzClass->setWindowTitle(QApplication::translate("ExtractOpenToonzClass", "ExtractOpenToonz", 0));
    } // retranslateUi

};

namespace Ui {
    class ExtractOpenToonzClass: public Ui_ExtractOpenToonzClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRACTOPENTOONZ_H
