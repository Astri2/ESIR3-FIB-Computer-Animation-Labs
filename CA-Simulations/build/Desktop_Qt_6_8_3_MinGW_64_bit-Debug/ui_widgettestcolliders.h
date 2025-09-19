/********************************************************************************
** Form generated from reading UI file 'widgettestcolliders.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETTESTCOLLIDERS_H
#define UI_WIDGETTESTCOLLIDERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetTestColliders
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabCollider;
    QWidget *tab;
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *plane_nx;
    QDoubleSpinBox *plane_ny;
    QDoubleSpinBox *plane_nz;
    QLabel *label_2;
    QDoubleSpinBox *plane_d;
    QWidget *tab_3;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLabel *label_3;
    QDoubleSpinBox *sphere_rad;
    QDoubleSpinBox *sphere_cx;
    QDoubleSpinBox *sphere_cy;
    QDoubleSpinBox *sphere_cz;
    QWidget *tab_4;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    QDoubleSpinBox *aabb_miny;
    QDoubleSpinBox *aabb_minx;
    QLabel *label_7;
    QDoubleSpinBox *aabb_maxx;
    QDoubleSpinBox *aabb_minz;
    QDoubleSpinBox *aabb_maxy;
    QDoubleSpinBox *aabb_maxz;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_7;
    QDoubleSpinBox *particleScale;
    QLabel *label_9;
    QDoubleSpinBox *friction;
    QLabel *label_8;
    QLabel *label_5;
    QCheckBox *checkCCD;
    QDoubleSpinBox *bounciness;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QDoubleSpinBox *prevX;
    QDoubleSpinBox *prevY;
    QDoubleSpinBox *prevZ;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QDoubleSpinBox *currX;
    QDoubleSpinBox *currY;
    QDoubleSpinBox *currZ;
    QTextEdit *textCollision;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *WidgetTestColliders)
    {
        if (WidgetTestColliders->objectName().isEmpty())
            WidgetTestColliders->setObjectName("WidgetTestColliders");
        WidgetTestColliders->resize(277, 592);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WidgetTestColliders->sizePolicy().hasHeightForWidth());
        WidgetTestColliders->setSizePolicy(sizePolicy);
        WidgetTestColliders->setMaximumSize(QSize(277, 16777215));
        verticalLayout_2 = new QVBoxLayout(WidgetTestColliders);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tabCollider = new QTabWidget(WidgetTestColliders);
        tabCollider->setObjectName("tabCollider");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabCollider->sizePolicy().hasHeightForWidth());
        tabCollider->setSizePolicy(sizePolicy1);
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(tab);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        plane_nx = new QDoubleSpinBox(tab);
        plane_nx->setObjectName("plane_nx");
        plane_nx->setMinimum(-100.000000000000000);
        plane_nx->setMaximum(100.000000000000000);
        plane_nx->setSingleStep(0.100000000000000);
        plane_nx->setValue(0.000000000000000);

        gridLayout->addWidget(plane_nx, 0, 1, 1, 1);

        plane_ny = new QDoubleSpinBox(tab);
        plane_ny->setObjectName("plane_ny");
        plane_ny->setMinimum(-100.000000000000000);
        plane_ny->setMaximum(100.000000000000000);
        plane_ny->setSingleStep(0.100000000000000);
        plane_ny->setValue(1.000000000000000);

        gridLayout->addWidget(plane_ny, 0, 2, 1, 1);

        plane_nz = new QDoubleSpinBox(tab);
        plane_nz->setObjectName("plane_nz");
        plane_nz->setMinimum(-100.000000000000000);
        plane_nz->setMaximum(100.000000000000000);
        plane_nz->setSingleStep(0.100000000000000);
        plane_nz->setValue(0.000000000000000);

        gridLayout->addWidget(plane_nz, 0, 3, 1, 1);

        label_2 = new QLabel(tab);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        plane_d = new QDoubleSpinBox(tab);
        plane_d->setObjectName("plane_d");
        plane_d->setMinimum(-100.000000000000000);
        plane_d->setMaximum(100.000000000000000);
        plane_d->setSingleStep(0.100000000000000);
        plane_d->setValue(0.000000000000000);

        gridLayout->addWidget(plane_d, 1, 1, 1, 1);

        tabCollider->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        gridLayout_2 = new QGridLayout(tab_3);
        gridLayout_2->setObjectName("gridLayout_2");
        label_4 = new QLabel(tab_3);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        label_3 = new QLabel(tab_3);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        sphere_rad = new QDoubleSpinBox(tab_3);
        sphere_rad->setObjectName("sphere_rad");
        sphere_rad->setMinimum(-100.000000000000000);
        sphere_rad->setMaximum(100.000000000000000);
        sphere_rad->setSingleStep(0.100000000000000);
        sphere_rad->setValue(1.000000000000000);

        gridLayout_2->addWidget(sphere_rad, 1, 1, 1, 1);

        sphere_cx = new QDoubleSpinBox(tab_3);
        sphere_cx->setObjectName("sphere_cx");
        sphere_cx->setMinimum(-100.000000000000000);
        sphere_cx->setMaximum(100.000000000000000);
        sphere_cx->setSingleStep(0.100000000000000);
        sphere_cx->setValue(0.000000000000000);

        gridLayout_2->addWidget(sphere_cx, 0, 1, 1, 1);

        sphere_cy = new QDoubleSpinBox(tab_3);
        sphere_cy->setObjectName("sphere_cy");
        sphere_cy->setMinimum(-100.000000000000000);
        sphere_cy->setMaximum(100.000000000000000);
        sphere_cy->setSingleStep(0.100000000000000);
        sphere_cy->setValue(0.000000000000000);

        gridLayout_2->addWidget(sphere_cy, 0, 2, 1, 1);

        sphere_cz = new QDoubleSpinBox(tab_3);
        sphere_cz->setObjectName("sphere_cz");
        sphere_cz->setMinimum(-100.000000000000000);
        sphere_cz->setMaximum(100.000000000000000);
        sphere_cz->setSingleStep(0.100000000000000);
        sphere_cz->setValue(0.000000000000000);

        gridLayout_2->addWidget(sphere_cz, 0, 3, 1, 1);

        tabCollider->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        gridLayout_3 = new QGridLayout(tab_4);
        gridLayout_3->setObjectName("gridLayout_3");
        label_6 = new QLabel(tab_4);
        label_6->setObjectName("label_6");

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        aabb_miny = new QDoubleSpinBox(tab_4);
        aabb_miny->setObjectName("aabb_miny");
        aabb_miny->setMinimum(-100.000000000000000);
        aabb_miny->setMaximum(100.000000000000000);
        aabb_miny->setSingleStep(0.100000000000000);
        aabb_miny->setValue(-1.000000000000000);

        gridLayout_3->addWidget(aabb_miny, 0, 2, 1, 1);

        aabb_minx = new QDoubleSpinBox(tab_4);
        aabb_minx->setObjectName("aabb_minx");
        aabb_minx->setMinimum(-100.000000000000000);
        aabb_minx->setMaximum(100.000000000000000);
        aabb_minx->setSingleStep(0.100000000000000);
        aabb_minx->setValue(-3.000000000000000);

        gridLayout_3->addWidget(aabb_minx, 0, 1, 1, 1);

        label_7 = new QLabel(tab_4);
        label_7->setObjectName("label_7");

        gridLayout_3->addWidget(label_7, 1, 0, 1, 1);

        aabb_maxx = new QDoubleSpinBox(tab_4);
        aabb_maxx->setObjectName("aabb_maxx");
        aabb_maxx->setMinimum(-100.000000000000000);
        aabb_maxx->setMaximum(100.000000000000000);
        aabb_maxx->setSingleStep(0.100000000000000);
        aabb_maxx->setValue(3.000000000000000);

        gridLayout_3->addWidget(aabb_maxx, 1, 1, 1, 1);

        aabb_minz = new QDoubleSpinBox(tab_4);
        aabb_minz->setObjectName("aabb_minz");
        aabb_minz->setMinimum(-100.000000000000000);
        aabb_minz->setMaximum(100.000000000000000);
        aabb_minz->setSingleStep(0.100000000000000);
        aabb_minz->setValue(-2.000000000000000);

        gridLayout_3->addWidget(aabb_minz, 0, 3, 1, 1);

        aabb_maxy = new QDoubleSpinBox(tab_4);
        aabb_maxy->setObjectName("aabb_maxy");
        aabb_maxy->setMinimum(-100.000000000000000);
        aabb_maxy->setMaximum(100.000000000000000);
        aabb_maxy->setSingleStep(0.100000000000000);
        aabb_maxy->setValue(1.000000000000000);

        gridLayout_3->addWidget(aabb_maxy, 1, 2, 1, 1);

        aabb_maxz = new QDoubleSpinBox(tab_4);
        aabb_maxz->setObjectName("aabb_maxz");
        aabb_maxz->setMinimum(-100.000000000000000);
        aabb_maxz->setMaximum(100.000000000000000);
        aabb_maxz->setSingleStep(0.100000000000000);
        aabb_maxz->setValue(2.000000000000000);

        gridLayout_3->addWidget(aabb_maxz, 1, 3, 1, 1);

        tabCollider->addTab(tab_4, QString());

        verticalLayout_2->addWidget(tabCollider);

        groupBox_4 = new QGroupBox(WidgetTestColliders);
        groupBox_4->setObjectName("groupBox_4");
        gridLayout_7 = new QGridLayout(groupBox_4);
        gridLayout_7->setObjectName("gridLayout_7");
        particleScale = new QDoubleSpinBox(groupBox_4);
        particleScale->setObjectName("particleScale");
        particleScale->setMaximum(100.000000000000000);
        particleScale->setSingleStep(0.100000000000000);
        particleScale->setValue(0.200000000000000);

        gridLayout_7->addWidget(particleScale, 2, 1, 1, 1);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName("label_9");

        gridLayout_7->addWidget(label_9, 0, 0, 1, 1);

        friction = new QDoubleSpinBox(groupBox_4);
        friction->setObjectName("friction");
        friction->setMaximum(1.000000000000000);
        friction->setSingleStep(0.100000000000000);
        friction->setValue(0.300000000000000);

        gridLayout_7->addWidget(friction, 1, 1, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName("label_8");

        gridLayout_7->addWidget(label_8, 1, 0, 1, 1);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName("label_5");

        gridLayout_7->addWidget(label_5, 2, 0, 1, 1);

        checkCCD = new QCheckBox(groupBox_4);
        checkCCD->setObjectName("checkCCD");
        checkCCD->setChecked(true);

        gridLayout_7->addWidget(checkCCD, 3, 0, 1, 2);

        bounciness = new QDoubleSpinBox(groupBox_4);
        bounciness->setObjectName("bounciness");
        bounciness->setMaximum(1.000000000000000);
        bounciness->setSingleStep(0.100000000000000);
        bounciness->setValue(0.500000000000000);

        gridLayout_7->addWidget(bounciness, 0, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox_4);

        groupBox = new QGroupBox(WidgetTestColliders);
        groupBox->setObjectName("groupBox");
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setObjectName("gridLayout_6");
        prevX = new QDoubleSpinBox(groupBox);
        prevX->setObjectName("prevX");
        prevX->setMinimum(-100.000000000000000);
        prevX->setMaximum(100.000000000000000);
        prevX->setSingleStep(0.100000000000000);
        prevX->setValue(0.000000000000000);

        gridLayout_6->addWidget(prevX, 0, 0, 1, 1);

        prevY = new QDoubleSpinBox(groupBox);
        prevY->setObjectName("prevY");
        prevY->setMinimum(-100.000000000000000);
        prevY->setMaximum(100.000000000000000);
        prevY->setSingleStep(0.100000000000000);
        prevY->setValue(1.500000000000000);

        gridLayout_6->addWidget(prevY, 0, 1, 1, 1);

        prevZ = new QDoubleSpinBox(groupBox);
        prevZ->setObjectName("prevZ");
        prevZ->setMinimum(-100.000000000000000);
        prevZ->setMaximum(100.000000000000000);
        prevZ->setSingleStep(0.100000000000000);
        prevZ->setValue(0.000000000000000);

        gridLayout_6->addWidget(prevZ, 0, 2, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(WidgetTestColliders);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName("gridLayout_5");
        currX = new QDoubleSpinBox(groupBox_2);
        currX->setObjectName("currX");
        currX->setMinimum(-100.000000000000000);
        currX->setMaximum(100.000000000000000);
        currX->setSingleStep(0.100000000000000);
        currX->setValue(-3.500000000000000);

        gridLayout_5->addWidget(currX, 0, 0, 1, 1);

        currY = new QDoubleSpinBox(groupBox_2);
        currY->setObjectName("currY");
        currY->setMinimum(-100.000000000000000);
        currY->setMaximum(100.000000000000000);
        currY->setSingleStep(0.100000000000000);
        currY->setValue(0.000000000000000);

        gridLayout_5->addWidget(currY, 0, 1, 1, 1);

        currZ = new QDoubleSpinBox(groupBox_2);
        currZ->setObjectName("currZ");
        currZ->setMinimum(-100.000000000000000);
        currZ->setMaximum(100.000000000000000);
        currZ->setSingleStep(0.100000000000000);
        currZ->setValue(0.000000000000000);

        gridLayout_5->addWidget(currZ, 0, 2, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        textCollision = new QTextEdit(WidgetTestColliders);
        textCollision->setObjectName("textCollision");
        textCollision->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        textCollision->setReadOnly(true);

        verticalLayout_2->addWidget(textCollision);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(WidgetTestColliders);

        tabCollider->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(WidgetTestColliders);
    } // setupUi

    void retranslateUi(QWidget *WidgetTestColliders)
    {
        WidgetTestColliders->setWindowTitle(QCoreApplication::translate("WidgetTestColliders", "Form", nullptr));
        label->setText(QCoreApplication::translate("WidgetTestColliders", "Normal", nullptr));
        label_2->setText(QCoreApplication::translate("WidgetTestColliders", "d", nullptr));
        tabCollider->setTabText(tabCollider->indexOf(tab), QCoreApplication::translate("WidgetTestColliders", "Plane", nullptr));
        label_4->setText(QCoreApplication::translate("WidgetTestColliders", "Radius", nullptr));
        label_3->setText(QCoreApplication::translate("WidgetTestColliders", "Center", nullptr));
        tabCollider->setTabText(tabCollider->indexOf(tab_3), QCoreApplication::translate("WidgetTestColliders", "Sphere", nullptr));
        label_6->setText(QCoreApplication::translate("WidgetTestColliders", "Min", nullptr));
        label_7->setText(QCoreApplication::translate("WidgetTestColliders", "Max", nullptr));
        tabCollider->setTabText(tabCollider->indexOf(tab_4), QCoreApplication::translate("WidgetTestColliders", "AABB", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("WidgetTestColliders", "Collision params", nullptr));
        label_9->setText(QCoreApplication::translate("WidgetTestColliders", "Restitution", nullptr));
        label_8->setText(QCoreApplication::translate("WidgetTestColliders", "Friction", nullptr));
        label_5->setText(QCoreApplication::translate("WidgetTestColliders", "Particle radius", nullptr));
        checkCCD->setText(QCoreApplication::translate("WidgetTestColliders", "Continuous collision detection", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WidgetTestColliders", "Previous position", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("WidgetTestColliders", "Predicted position", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetTestColliders: public Ui_WidgetTestColliders {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETTESTCOLLIDERS_H
