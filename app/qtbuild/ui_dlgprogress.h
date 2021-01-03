/********************************************************************************
** Form generated from reading UI file 'dlgprogress.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPROGRESS_H
#define UI_DLGPROGRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgProgress
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;

    void setupUi(QDialog *DlgProgress)
    {
        if (DlgProgress->objectName().isEmpty())
            DlgProgress->setObjectName(QString::fromUtf8("DlgProgress"));
        DlgProgress->resize(400, 163);
        verticalLayout_2 = new QVBoxLayout(DlgProgress);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(DlgProgress);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        progressBar = new QProgressBar(DlgProgress);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setLayoutDirection(Qt::LeftToRight);
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(DlgProgress);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(100, 16777215));
        QFont font1;
        font1.setPointSize(12);
        pushButton->setFont(font1);
        pushButton->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(DlgProgress);

        QMetaObject::connectSlotsByName(DlgProgress);
    } // setupUi

    void retranslateUi(QDialog *DlgProgress)
    {
        DlgProgress->setWindowTitle(QCoreApplication::translate("DlgProgress", "Progress", nullptr));
        label->setText(QCoreApplication::translate("DlgProgress", "Converting...", nullptr));
        pushButton->setText(QCoreApplication::translate("DlgProgress", "Abort", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgProgress: public Ui_DlgProgress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGPROGRESS_H
