/********************************************************************************
** Form generated from reading UI file 'widgetprojectiles.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETPROJECTILES_H
#define UI_WIDGETPROJECTILES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetProjectiles
{
public:
    QFormLayout *formLayout;
    QLabel *label_2;
    QDoubleSpinBox *gravity;
    QLabel *label;
    QDoubleSpinBox *height;
    QLabel *label_3;
    QDoubleSpinBox *angle;
    QLabel *label_4;
    QDoubleSpinBox *speed;
    QCheckBox *sameZ;
    QCheckBox *trajectory;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *solver1;
    QComboBox *solver2;

    void setupUi(QWidget *WidgetProjectiles)
    {
        if (WidgetProjectiles->objectName().isEmpty())
            WidgetProjectiles->setObjectName("WidgetProjectiles");
        WidgetProjectiles->resize(262, 453);
        formLayout = new QFormLayout(WidgetProjectiles);
        formLayout->setObjectName("formLayout");
        label_2 = new QLabel(WidgetProjectiles);
        label_2->setObjectName("label_2");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        gravity = new QDoubleSpinBox(WidgetProjectiles);
        gravity->setObjectName("gravity");
        gravity->setSingleStep(0.100000000000000);
        gravity->setValue(9.810000000000000);

        formLayout->setWidget(0, QFormLayout::FieldRole, gravity);

        label = new QLabel(WidgetProjectiles);
        label->setObjectName("label");

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        height = new QDoubleSpinBox(WidgetProjectiles);
        height->setObjectName("height");
        height->setMaximum(100.000000000000000);
        height->setValue(30.000000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, height);

        label_3 = new QLabel(WidgetProjectiles);
        label_3->setObjectName("label_3");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        angle = new QDoubleSpinBox(WidgetProjectiles);
        angle->setObjectName("angle");
        angle->setMinimum(-90.000000000000000);
        angle->setMaximum(90.000000000000000);
        angle->setValue(45.000000000000000);

        formLayout->setWidget(3, QFormLayout::FieldRole, angle);

        label_4 = new QLabel(WidgetProjectiles);
        label_4->setObjectName("label_4");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        speed = new QDoubleSpinBox(WidgetProjectiles);
        speed->setObjectName("speed");
        speed->setMaximum(50.000000000000000);
        speed->setValue(40.000000000000000);

        formLayout->setWidget(2, QFormLayout::FieldRole, speed);

        sameZ = new QCheckBox(WidgetProjectiles);
        sameZ->setObjectName("sameZ");

        formLayout->setWidget(7, QFormLayout::SpanningRole, sameZ);

        trajectory = new QCheckBox(WidgetProjectiles);
        trajectory->setObjectName("trajectory");

        formLayout->setWidget(6, QFormLayout::SpanningRole, trajectory);

        label_5 = new QLabel(WidgetProjectiles);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("font-weight:bold;color:darkred"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(WidgetProjectiles);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("font-weight:bold;color:darkblue"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        solver1 = new QComboBox(WidgetProjectiles);
        solver1->addItem(QString());
        solver1->addItem(QString());
        solver1->addItem(QString());
        solver1->addItem(QString());
        solver1->setObjectName("solver1");

        formLayout->setWidget(4, QFormLayout::FieldRole, solver1);

        solver2 = new QComboBox(WidgetProjectiles);
        solver2->setObjectName("solver2");

        formLayout->setWidget(5, QFormLayout::FieldRole, solver2);


        retranslateUi(WidgetProjectiles);

        QMetaObject::connectSlotsByName(WidgetProjectiles);
    } // setupUi

    void retranslateUi(QWidget *WidgetProjectiles)
    {
        WidgetProjectiles->setWindowTitle(QCoreApplication::translate("WidgetProjectiles", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("WidgetProjectiles", "Gravity accel", nullptr));
        label->setText(QCoreApplication::translate("WidgetProjectiles", "Initial height", nullptr));
        label_3->setText(QCoreApplication::translate("WidgetProjectiles", "Angle", nullptr));
        label_4->setText(QCoreApplication::translate("WidgetProjectiles", "Initial speed", nullptr));
        sameZ->setText(QCoreApplication::translate("WidgetProjectiles", "Same Z coordinate", nullptr));
        trajectory->setText(QCoreApplication::translate("WidgetProjectiles", "Show trajectory", nullptr));
        label_5->setText(QCoreApplication::translate("WidgetProjectiles", "Solver 1", nullptr));
        label_6->setText(QCoreApplication::translate("WidgetProjectiles", "Solver 2", nullptr));
        solver1->setItemText(0, QCoreApplication::translate("WidgetProjectiles", "Euler", nullptr));
        solver1->setItemText(1, QCoreApplication::translate("WidgetProjectiles", "Symplectic Euler", nullptr));
        solver1->setItemText(2, QCoreApplication::translate("WidgetProjectiles", "Midpoint", nullptr));
        solver1->setItemText(3, QCoreApplication::translate("WidgetProjectiles", "RK2", nullptr));

    } // retranslateUi

};

namespace Ui {
    class WidgetProjectiles: public Ui_WidgetProjectiles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETPROJECTILES_H
