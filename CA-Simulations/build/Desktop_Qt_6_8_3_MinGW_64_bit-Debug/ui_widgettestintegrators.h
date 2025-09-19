/********************************************************************************
** Form generated from reading UI file 'widgettestintegrators.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETTESTINTEGRATORS_H
#define UI_WIDGETTESTINTEGRATORS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetTestIntegrators
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *integrator;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *label_6;
    QDoubleSpinBox *initialPos;
    QLabel *label_5;
    QDoubleSpinBox *initialVel;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QDoubleSpinBox *stiffness;
    QLabel *label_2;
    QDoubleSpinBox *damping;
    QPushButton *btnCriticalDamp;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *forceMagnitude;
    QLabel *label_4;
    QDoubleSpinBox *forceFrequency;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QCheckBox *drawPhaseAnalytic;
    QCheckBox *drawPhaseNumerical;
    QCheckBox *drawOscillationNumerical;
    QLabel *label_11;
    QLabel *label_8;
    QLabel *label_10;
    QCheckBox *drawOscillationAnalytic;
    QLabel *label_9;
    QLabel *label_7;
    QDoubleSpinBox *timeScale;
    QCheckBox *drawScaleVectors;
    QTextEdit *textSimVals;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *WidgetTestIntegrators)
    {
        if (WidgetTestIntegrators->objectName().isEmpty())
            WidgetTestIntegrators->setObjectName("WidgetTestIntegrators");
        WidgetTestIntegrators->resize(206, 686);
        WidgetTestIntegrators->setMaximumSize(QSize(260, 16777215));
        verticalLayout = new QVBoxLayout(WidgetTestIntegrators);
        verticalLayout->setObjectName("verticalLayout");
        integrator = new QComboBox(WidgetTestIntegrators);
        integrator->addItem(QString());
        integrator->addItem(QString());
        integrator->addItem(QString());
        integrator->addItem(QString());
        integrator->addItem(QString());
        integrator->addItem(QString());
        integrator->addItem(QString());
        integrator->addItem(QString());
        integrator->setObjectName("integrator");

        verticalLayout->addWidget(integrator);

        groupBox_2 = new QGroupBox(WidgetTestIntegrators);
        groupBox_2->setObjectName("groupBox_2");
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName("formLayout_2");
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_6);

        initialPos = new QDoubleSpinBox(groupBox_2);
        initialPos->setObjectName("initialPos");
        initialPos->setMinimum(-10.000000000000000);
        initialPos->setMaximum(10.000000000000000);
        initialPos->setValue(5.000000000000000);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, initialPos);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_5);

        initialVel = new QDoubleSpinBox(groupBox_2);
        initialVel->setObjectName("initialVel");
        initialVel->setMinimum(-10.000000000000000);
        initialVel->setMaximum(10.000000000000000);
        initialVel->setValue(3.000000000000000);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, initialVel);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(WidgetTestIntegrators);
        groupBox->setObjectName("groupBox");
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        stiffness = new QDoubleSpinBox(groupBox);
        stiffness->setObjectName("stiffness");
        stiffness->setMaximum(1000.000000000000000);
        stiffness->setValue(2.000000000000000);

        formLayout->setWidget(0, QFormLayout::FieldRole, stiffness);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        damping = new QDoubleSpinBox(groupBox);
        damping->setObjectName("damping");
        damping->setDecimals(3);
        damping->setMaximum(1000.000000000000000);
        damping->setSingleStep(0.100000000000000);
        damping->setValue(0.200000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, damping);

        btnCriticalDamp = new QPushButton(groupBox);
        btnCriticalDamp->setObjectName("btnCriticalDamp");

        formLayout->setWidget(2, QFormLayout::FieldRole, btnCriticalDamp);


        verticalLayout->addWidget(groupBox);

        groupBox_3 = new QGroupBox(WidgetTestIntegrators);
        groupBox_3->setObjectName("groupBox_3");
        formLayout_3 = new QFormLayout(groupBox_3);
        formLayout_3->setObjectName("formLayout_3");
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_3);

        forceMagnitude = new QDoubleSpinBox(groupBox_3);
        forceMagnitude->setObjectName("forceMagnitude");
        forceMagnitude->setMaximum(1000.000000000000000);
        forceMagnitude->setValue(1.000000000000000);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, forceMagnitude);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_4);

        forceFrequency = new QDoubleSpinBox(groupBox_3);
        forceFrequency->setObjectName("forceFrequency");
        forceFrequency->setMaximum(1000.000000000000000);
        forceFrequency->setValue(0.500000000000000);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, forceFrequency);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(WidgetTestIntegrators);
        groupBox_4->setObjectName("groupBox_4");
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setObjectName("gridLayout_2");
        drawPhaseAnalytic = new QCheckBox(groupBox_4);
        drawPhaseAnalytic->setObjectName("drawPhaseAnalytic");
        drawPhaseAnalytic->setChecked(true);

        gridLayout_2->addWidget(drawPhaseAnalytic, 2, 2, 1, 1);

        drawPhaseNumerical = new QCheckBox(groupBox_4);
        drawPhaseNumerical->setObjectName("drawPhaseNumerical");
        drawPhaseNumerical->setChecked(true);

        gridLayout_2->addWidget(drawPhaseNumerical, 3, 2, 1, 1);

        drawOscillationNumerical = new QCheckBox(groupBox_4);
        drawOscillationNumerical->setObjectName("drawOscillationNumerical");
        drawOscillationNumerical->setChecked(true);

        gridLayout_2->addWidget(drawOscillationNumerical, 3, 1, 2, 1);

        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName("label_11");

        gridLayout_2->addWidget(label_11, 2, 0, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName("label_8");

        gridLayout_2->addWidget(label_8, 1, 1, 1, 1);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName("label_10");

        gridLayout_2->addWidget(label_10, 3, 0, 2, 1);

        drawOscillationAnalytic = new QCheckBox(groupBox_4);
        drawOscillationAnalytic->setObjectName("drawOscillationAnalytic");
        drawOscillationAnalytic->setChecked(true);

        gridLayout_2->addWidget(drawOscillationAnalytic, 2, 1, 1, 1);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName("label_9");

        gridLayout_2->addWidget(label_9, 1, 2, 1, 1);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName("label_7");

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        timeScale = new QDoubleSpinBox(groupBox_4);
        timeScale->setObjectName("timeScale");
        timeScale->setDecimals(2);
        timeScale->setMaximum(100.000000000000000);
        timeScale->setSingleStep(0.100000000000000);
        timeScale->setValue(1.000000000000000);

        gridLayout_2->addWidget(timeScale, 0, 1, 1, 2);

        drawScaleVectors = new QCheckBox(groupBox_4);
        drawScaleVectors->setObjectName("drawScaleVectors");

        gridLayout_2->addWidget(drawScaleVectors, 5, 0, 1, 3);


        verticalLayout->addWidget(groupBox_4);

        textSimVals = new QTextEdit(WidgetTestIntegrators);
        textSimVals->setObjectName("textSimVals");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textSimVals->sizePolicy().hasHeightForWidth());
        textSimVals->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(8);
        textSimVals->setFont(font);
        textSimVals->setReadOnly(true);

        verticalLayout->addWidget(textSimVals);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(WidgetTestIntegrators);

        QMetaObject::connectSlotsByName(WidgetTestIntegrators);
    } // setupUi

    void retranslateUi(QWidget *WidgetTestIntegrators)
    {
        WidgetTestIntegrators->setWindowTitle(QCoreApplication::translate("WidgetTestIntegrators", "Form", nullptr));
        integrator->setItemText(0, QCoreApplication::translate("WidgetTestIntegrators", "Euler", nullptr));
        integrator->setItemText(1, QCoreApplication::translate("WidgetTestIntegrators", "Symplectic Euler", nullptr));
        integrator->setItemText(2, QCoreApplication::translate("WidgetTestIntegrators", "Midpoint", nullptr));
        integrator->setItemText(3, QCoreApplication::translate("WidgetTestIntegrators", "Leapfrog", nullptr));
        integrator->setItemText(4, QCoreApplication::translate("WidgetTestIntegrators", "RK2 (Heun)", nullptr));
        integrator->setItemText(5, QCoreApplication::translate("WidgetTestIntegrators", "RK4", nullptr));
        integrator->setItemText(6, QCoreApplication::translate("WidgetTestIntegrators", "Verlet", nullptr));
        integrator->setItemText(7, QCoreApplication::translate("WidgetTestIntegrators", "Velocity Verlet", nullptr));

        groupBox_2->setTitle(QCoreApplication::translate("WidgetTestIntegrators", "Initial value", nullptr));
        label_6->setText(QCoreApplication::translate("WidgetTestIntegrators", "Position", nullptr));
        label_5->setText(QCoreApplication::translate("WidgetTestIntegrators", "Velocity", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WidgetTestIntegrators", "Oscillator", nullptr));
        label->setText(QCoreApplication::translate("WidgetTestIntegrators", "Stiffness", nullptr));
        label_2->setText(QCoreApplication::translate("WidgetTestIntegrators", "Damping", nullptr));
        btnCriticalDamp->setText(QCoreApplication::translate("WidgetTestIntegrators", "Set critical damping", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("WidgetTestIntegrators", "Driving force F(t) = A cos (w t)", nullptr));
        label_3->setText(QCoreApplication::translate("WidgetTestIntegrators", "Magnitude", nullptr));
        label_4->setText(QCoreApplication::translate("WidgetTestIntegrators", "Frequency", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("WidgetTestIntegrators", "Draw", nullptr));
        drawPhaseAnalytic->setText(QString());
        drawPhaseNumerical->setText(QString());
        drawOscillationNumerical->setText(QString());
        label_11->setText(QCoreApplication::translate("WidgetTestIntegrators", "Analytical", nullptr));
        label_8->setText(QCoreApplication::translate("WidgetTestIntegrators", "x(t)", nullptr));
        label_10->setText(QCoreApplication::translate("WidgetTestIntegrators", "Numerical", nullptr));
        drawOscillationAnalytic->setText(QString());
        label_9->setText(QCoreApplication::translate("WidgetTestIntegrators", "phase", nullptr));
        label_7->setText(QCoreApplication::translate("WidgetTestIntegrators", "Time axis scale", nullptr));
        drawScaleVectors->setText(QCoreApplication::translate("WidgetTestIntegrators", "Scale vectors magnitude", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetTestIntegrators: public Ui_WidgetTestIntegrators {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETTESTINTEGRATORS_H
