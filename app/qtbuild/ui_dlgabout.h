/********************************************************************************
** Form generated from reading UI file 'dlgabout.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGABOUT_H
#define UI_DLGABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_dlgabout
{
public:
    QLabel *lb_logo;
    QLabel *label;
    QLabel *t_version;
    QLabel *label_3;

    void setupUi(QDialog *dlgabout)
    {
        if (dlgabout->objectName().isEmpty())
            dlgabout->setObjectName(QString::fromUtf8("dlgabout"));
        dlgabout->resize(603, 228);
        QFont font;
        font.setPointSize(16);
        dlgabout->setFont(font);
        lb_logo = new QLabel(dlgabout);
        lb_logo->setObjectName(QString::fromUtf8("lb_logo"));
        lb_logo->setGeometry(QRect(40, 40, 141, 151));
        QFont font1;
        font1.setPointSize(34);
        lb_logo->setFont(font1);
        label = new QLabel(dlgabout);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 20, 181, 71));
        label->setFont(font1);
        t_version = new QLabel(dlgabout);
        t_version->setObjectName(QString::fromUtf8("t_version"));
        t_version->setGeometry(QRect(210, 80, 261, 51));
        label_3 = new QLabel(dlgabout);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 130, 371, 31));
        QFont font2;
        font2.setPointSize(14);
        label_3->setFont(font2);

        retranslateUi(dlgabout);

        QMetaObject::connectSlotsByName(dlgabout);
    } // setupUi

    void retranslateUi(QDialog *dlgabout)
    {
        dlgabout->setWindowTitle(QCoreApplication::translate("dlgabout", "About", nullptr));
        lb_logo->setText(QString());
        label->setText(QCoreApplication::translate("dlgabout", "AuTyper", nullptr));
        t_version->setText(QCoreApplication::translate("dlgabout", "Version: ", nullptr));
        label_3->setText(QCoreApplication::translate("dlgabout", "Copyrights: Varanda Labs Inc.  2020, 2021", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgabout: public Ui_dlgabout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGABOUT_H
