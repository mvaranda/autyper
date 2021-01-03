/********************************************************************************
** Form generated from reading UI file 'autypermain.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTYPERMAIN_H
#define UI_AUTYPERMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutyperMain
{
public:
    QAction *actionOpen;
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionChange_Model;
    QAction *actionHelp;
    QAction *actionInfo;
    QAction *actionAppend_Voice;
    QAction *actionCheck_for_Upgrade;
    QAction *actionCut;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QMdiArea *mdiArea;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuAbout;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *AutyperMain)
    {
        if (AutyperMain->objectName().isEmpty())
            AutyperMain->setObjectName(QString::fromUtf8("AutyperMain"));
        AutyperMain->resize(1042, 632);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AutyperMain->sizePolicy().hasHeightForWidth());
        AutyperMain->setSizePolicy(sizePolicy);
        actionOpen = new QAction(AutyperMain);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/rec/images/text-plain.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionNew = new QAction(AutyperMain);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/rec/images/text-plain-new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionSave = new QAction(AutyperMain);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/rec/images/media-floppy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionCopy = new QAction(AutyperMain);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionPaste = new QAction(AutyperMain);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionChange_Model = new QAction(AutyperMain);
        actionChange_Model->setObjectName(QString::fromUtf8("actionChange_Model"));
        actionHelp = new QAction(AutyperMain);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionInfo = new QAction(AutyperMain);
        actionInfo->setObjectName(QString::fromUtf8("actionInfo"));
        actionAppend_Voice = new QAction(AutyperMain);
        actionAppend_Voice->setObjectName(QString::fromUtf8("actionAppend_Voice"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/rec/images/autyper_icon_128.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAppend_Voice->setIcon(icon3);
        actionCheck_for_Upgrade = new QAction(AutyperMain);
        actionCheck_for_Upgrade->setObjectName(QString::fromUtf8("actionCheck_for_Upgrade"));
        actionCut = new QAction(AutyperMain);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        centralwidget = new QWidget(AutyperMain);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMaximumSize(QSize(2048, 2048));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        mdiArea->setDocumentMode(false);
        mdiArea->setTabsClosable(false);

        verticalLayout_2->addWidget(mdiArea);

        AutyperMain->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AutyperMain);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1042, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        AutyperMain->setMenuBar(menubar);
        statusbar = new QStatusBar(AutyperMain);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        AutyperMain->setStatusBar(statusbar);
        toolBar = new QToolBar(AutyperMain);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setIconSize(QSize(48, 48));
        AutyperMain->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionCut);
        menuEdit->addSeparator();
        menuEdit->addAction(actionAppend_Voice);
        menuEdit->addSeparator();
        menuEdit->addAction(actionChange_Model);
        menuAbout->addSeparator();
        menuAbout->addAction(actionHelp);
        menuAbout->addAction(actionInfo);
        menuAbout->addSeparator();
        menuAbout->addAction(actionCheck_for_Upgrade);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionAppend_Voice);

        retranslateUi(AutyperMain);

        QMetaObject::connectSlotsByName(AutyperMain);
    } // setupUi

    void retranslateUi(QMainWindow *AutyperMain)
    {
        AutyperMain->setWindowTitle(QCoreApplication::translate("AutyperMain", "AutyperMain", nullptr));
        actionOpen->setText(QCoreApplication::translate("AutyperMain", "Open", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("AutyperMain", "Open existing text file", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("AutyperMain", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNew->setText(QCoreApplication::translate("AutyperMain", "New", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("AutyperMain", "New Text file", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("AutyperMain", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("AutyperMain", "Save", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("AutyperMain", "Save Text File", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("AutyperMain", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy->setText(QCoreApplication::translate("AutyperMain", "Copy", nullptr));
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QCoreApplication::translate("AutyperMain", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPaste->setText(QCoreApplication::translate("AutyperMain", "Paste", nullptr));
#if QT_CONFIG(shortcut)
        actionPaste->setShortcut(QCoreApplication::translate("AutyperMain", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionChange_Model->setText(QCoreApplication::translate("AutyperMain", "Change Model", nullptr));
#if QT_CONFIG(shortcut)
        actionChange_Model->setShortcut(QCoreApplication::translate("AutyperMain", "Ctrl+M", nullptr));
#endif // QT_CONFIG(shortcut)
        actionHelp->setText(QCoreApplication::translate("AutyperMain", "Help", nullptr));
        actionInfo->setText(QCoreApplication::translate("AutyperMain", "Info", nullptr));
        actionAppend_Voice->setText(QCoreApplication::translate("AutyperMain", "Append Voice", nullptr));
#if QT_CONFIG(tooltip)
        actionAppend_Voice->setToolTip(QCoreApplication::translate("AutyperMain", "Append Voice to existing text", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionAppend_Voice->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        actionCheck_for_Upgrade->setText(QCoreApplication::translate("AutyperMain", "Check for Upgrade", nullptr));
        actionCut->setText(QCoreApplication::translate("AutyperMain", "Cut", nullptr));
#if QT_CONFIG(shortcut)
        actionCut->setShortcut(QCoreApplication::translate("AutyperMain", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        menuFile->setTitle(QCoreApplication::translate("AutyperMain", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("AutyperMain", "Edit", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("AutyperMain", "About", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("AutyperMain", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutyperMain: public Ui_AutyperMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTYPERMAIN_H
