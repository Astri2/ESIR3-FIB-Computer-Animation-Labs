/********************************************************************************
** Form generated from reading UI file 'widgetfountain.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETFOUNTAIN_H
#define UI_WIDGETFOUNTAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetFountain
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QDoubleSpinBox *gravity;
    QPushButton *btnUpdate;

    void setupUi(QWidget *WidgetFountain)
    {
        if (WidgetFountain->objectName().isEmpty())
            WidgetFountain->setObjectName("WidgetFountain");
        WidgetFountain->resize(247, 462);
        formLayout = new QFormLayout(WidgetFountain);
        formLayout->setObjectName("formLayout");
        label = new QLabel(WidgetFountain);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        gravity = new QDoubleSpinBox(WidgetFountain);
        gravity->setObjectName("gravity");
        gravity->setMaximum(100.000000000000000);
        gravity->setSingleStep(0.100000000000000);
        gravity->setValue(9.810000000000000);

        formLayout->setWidget(0, QFormLayout::FieldRole, gravity);

        btnUpdate = new QPushButton(WidgetFountain);
        btnUpdate->setObjectName("btnUpdate");

        formLayout->setWidget(1, QFormLayout::SpanningRole, btnUpdate);


        retranslateUi(WidgetFountain);

        QMetaObject::connectSlotsByName(WidgetFountain);
    } // setupUi

    void retranslateUi(QWidget *WidgetFountain)
    {
        WidgetFountain->setWindowTitle(QCoreApplication::translate("WidgetFountain", "Form", nullptr));
        label->setText(QCoreApplication::translate("WidgetFountain", "Gravity", nullptr));
        btnUpdate->setText(QCoreApplication::translate("WidgetFountain", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetFountain: public Ui_WidgetFountain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETFOUNTAIN_H
