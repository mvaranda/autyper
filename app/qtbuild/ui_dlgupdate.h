/********************************************************************************
** Form generated from reading UI file 'dlgupdate.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGUPDATE_H
#define UI_DLGUPDATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DlgUpdate
{
public:
    QLabel *t_latest_ver;
    QLabel *lb_logo;
    QLabel *t_conclusion;
    QPushButton *bt_close1;
    QPushButton *bt_close2;
    QPushButton *bt_goto_web;
    QPlainTextEdit *t_note;

    void setupUi(QDialog *DlgUpdate)
    {
        if (DlgUpdate->objectName().isEmpty())
            DlgUpdate->setObjectName(QString::fromUtf8("DlgUpdate"));
        DlgUpdate->resize(495, 207);
        t_latest_ver = new QLabel(DlgUpdate);
        t_latest_ver->setObjectName(QString::fromUtf8("t_latest_ver"));
        t_latest_ver->setGeometry(QRect(210, 10, 201, 31));
        QFont font;
        font.setPointSize(14);
        t_latest_ver->setFont(font);
        lb_logo = new QLabel(DlgUpdate);
        lb_logo->setObjectName(QString::fromUtf8("lb_logo"));
        lb_logo->setGeometry(QRect(20, 20, 101, 121));
        t_conclusion = new QLabel(DlgUpdate);
        t_conclusion->setObjectName(QString::fromUtf8("t_conclusion"));
        t_conclusion->setGeometry(QRect(160, 50, 311, 31));
        QFont font1;
        font1.setPointSize(10);
        t_conclusion->setFont(font1);
        bt_close1 = new QPushButton(DlgUpdate);
        bt_close1->setObjectName(QString::fromUtf8("bt_close1"));
        bt_close1->setGeometry(QRect(400, 170, 75, 23));
        bt_close1->setFont(font1);
        bt_close2 = new QPushButton(DlgUpdate);
        bt_close2->setObjectName(QString::fromUtf8("bt_close2"));
        bt_close2->setGeometry(QRect(20, 170, 75, 23));
        bt_close2->setFont(font1);
        bt_goto_web = new QPushButton(DlgUpdate);
        bt_goto_web->setObjectName(QString::fromUtf8("bt_goto_web"));
        bt_goto_web->setGeometry(QRect(330, 170, 141, 23));
        bt_goto_web->setFont(font1);
        t_note = new QPlainTextEdit(DlgUpdate);
        t_note->setObjectName(QString::fromUtf8("t_note"));
        t_note->setGeometry(QRect(160, 90, 311, 61));
        t_note->setReadOnly(true);

        retranslateUi(DlgUpdate);

        QMetaObject::connectSlotsByName(DlgUpdate);
    } // setupUi

    void retranslateUi(QDialog *DlgUpdate)
    {
        DlgUpdate->setWindowTitle(QCoreApplication::translate("DlgUpdate", "Version Checker", nullptr));
        t_latest_ver->setText(QCoreApplication::translate("DlgUpdate", "Latest Version: 0.0.0", nullptr));
        lb_logo->setText(QString());
        t_conclusion->setText(QCoreApplication::translate("DlgUpdate", "Conclusion: You have the latest version", nullptr));
        bt_close1->setText(QCoreApplication::translate("DlgUpdate", "Close", nullptr));
        bt_close2->setText(QCoreApplication::translate("DlgUpdate", "Close", nullptr));
        bt_goto_web->setText(QCoreApplication::translate("DlgUpdate", "Visit AuType Webpage", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgUpdate: public Ui_DlgUpdate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGUPDATE_H
