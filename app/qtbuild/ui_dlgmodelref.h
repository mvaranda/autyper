/********************************************************************************
** Form generated from reading UI file 'dlgmodelref.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGMODELREF_H
#define UI_DLGMODELREF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgModelRef
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPlainTextEdit *t_model;
    QPushButton *bt_browse_model;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QPlainTextEdit *t_scorer;
    QPushButton *bt_browse_scorer;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *bt_cancel;
    QSpacerItem *horizontalSpacer;
    QPushButton *bt_save;

    void setupUi(QDialog *DlgModelRef)
    {
        if (DlgModelRef->objectName().isEmpty())
            DlgModelRef->setObjectName(QString::fromUtf8("DlgModelRef"));
        DlgModelRef->resize(726, 254);
        verticalLayout = new QVBoxLayout(DlgModelRef);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DlgModelRef);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        t_model = new QPlainTextEdit(DlgModelRef);
        t_model->setObjectName(QString::fromUtf8("t_model"));
        t_model->setMaximumSize(QSize(16777215, 28));
        QFont font1;
        font1.setPointSize(10);
        t_model->setFont(font1);

        horizontalLayout->addWidget(t_model);

        bt_browse_model = new QPushButton(DlgModelRef);
        bt_browse_model->setObjectName(QString::fromUtf8("bt_browse_model"));
        bt_browse_model->setFont(font);

        horizontalLayout->addWidget(bt_browse_model);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(DlgModelRef);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        t_scorer = new QPlainTextEdit(DlgModelRef);
        t_scorer->setObjectName(QString::fromUtf8("t_scorer"));
        t_scorer->setMaximumSize(QSize(16777215, 28));
        t_scorer->setFont(font1);

        horizontalLayout_2->addWidget(t_scorer);

        bt_browse_scorer = new QPushButton(DlgModelRef);
        bt_browse_scorer->setObjectName(QString::fromUtf8("bt_browse_scorer"));
        bt_browse_scorer->setFont(font);

        horizontalLayout_2->addWidget(bt_browse_scorer);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        bt_cancel = new QPushButton(DlgModelRef);
        bt_cancel->setObjectName(QString::fromUtf8("bt_cancel"));
        bt_cancel->setFont(font);

        horizontalLayout_3->addWidget(bt_cancel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        bt_save = new QPushButton(DlgModelRef);
        bt_save->setObjectName(QString::fromUtf8("bt_save"));
        bt_save->setFont(font);

        horizontalLayout_3->addWidget(bt_save);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(DlgModelRef);

        QMetaObject::connectSlotsByName(DlgModelRef);
    } // setupUi

    void retranslateUi(QDialog *DlgModelRef)
    {
        DlgModelRef->setWindowTitle(QCoreApplication::translate("DlgModelRef", "Select Model", nullptr));
        label->setText(QCoreApplication::translate("DlgModelRef", "Model File:", nullptr));
        bt_browse_model->setText(QCoreApplication::translate("DlgModelRef", "Browse", nullptr));
        label_2->setText(QCoreApplication::translate("DlgModelRef", "Scorer File:", nullptr));
        bt_browse_scorer->setText(QCoreApplication::translate("DlgModelRef", "Browse", nullptr));
        bt_cancel->setText(QCoreApplication::translate("DlgModelRef", "Cancel", nullptr));
        bt_save->setText(QCoreApplication::translate("DlgModelRef", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgModelRef: public Ui_DlgModelRef {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGMODELREF_H
