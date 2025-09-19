/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "code/glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSceneFountain;
    QAction *actionCameraReset;
    QAction *actionSceneProjectiles;
    QAction *actionCameraX;
    QAction *actionCameraY;
    QAction *actionCameraZ;
    QAction *actionSceneCloth;
    QAction *actionSceneTestIntegrators;
    QAction *actionSceneTestColliders;
    QAction *actionSceneRope;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *controlsSim;
    QGridLayout *gridLayout;
    QPushButton *btnPause;
    QLabel *label_2;
    QDoubleSpinBox *timestep;
    QPushButton *btnReset;
    QPushButton *btnSimloop;
    QPushButton *btnSimstep;
    QGroupBox *controlsScene;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    GLWidget *openGLWidget;
    QMenuBar *menubar;
    QMenu *menuScene;
    QMenu *menuCamera;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 600);
        actionSceneFountain = new QAction(MainWindow);
        actionSceneFountain->setObjectName("actionSceneFountain");
        actionCameraReset = new QAction(MainWindow);
        actionCameraReset->setObjectName("actionCameraReset");
        actionSceneProjectiles = new QAction(MainWindow);
        actionSceneProjectiles->setObjectName("actionSceneProjectiles");
        actionCameraX = new QAction(MainWindow);
        actionCameraX->setObjectName("actionCameraX");
        actionCameraY = new QAction(MainWindow);
        actionCameraY->setObjectName("actionCameraY");
        actionCameraZ = new QAction(MainWindow);
        actionCameraZ->setObjectName("actionCameraZ");
        actionSceneCloth = new QAction(MainWindow);
        actionSceneCloth->setObjectName("actionSceneCloth");
        actionSceneTestIntegrators = new QAction(MainWindow);
        actionSceneTestIntegrators->setObjectName("actionSceneTestIntegrators");
        actionSceneTestColliders = new QAction(MainWindow);
        actionSceneTestColliders->setObjectName("actionSceneTestColliders");
        actionSceneRope = new QAction(MainWindow);
        actionSceneRope->setObjectName("actionSceneRope");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        controlsSim = new QGroupBox(centralwidget);
        controlsSim->setObjectName("controlsSim");
        controlsSim->setMinimumSize(QSize(200, 0));
        gridLayout = new QGridLayout(controlsSim);
        gridLayout->setObjectName("gridLayout");
        btnPause = new QPushButton(controlsSim);
        btnPause->setObjectName("btnPause");

        gridLayout->addWidget(btnPause, 2, 0, 1, 1);

        label_2 = new QLabel(controlsSim);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        timestep = new QDoubleSpinBox(controlsSim);
        timestep->setObjectName("timestep");
        timestep->setDecimals(6);
        timestep->setMaximum(1.000000000000000);
        timestep->setSingleStep(0.010000000000000);
        timestep->setValue(0.050000000000000);

        gridLayout->addWidget(timestep, 3, 1, 1, 1);

        btnReset = new QPushButton(controlsSim);
        btnReset->setObjectName("btnReset");

        gridLayout->addWidget(btnReset, 2, 1, 1, 1);

        btnSimloop = new QPushButton(controlsSim);
        btnSimloop->setObjectName("btnSimloop");

        gridLayout->addWidget(btnSimloop, 1, 0, 1, 1);

        btnSimstep = new QPushButton(controlsSim);
        btnSimstep->setObjectName("btnSimstep");

        gridLayout->addWidget(btnSimstep, 1, 1, 1, 1);


        verticalLayout->addWidget(controlsSim);

        controlsScene = new QGroupBox(centralwidget);
        controlsScene->setObjectName("controlsScene");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(controlsScene->sizePolicy().hasHeightForWidth());
        controlsScene->setSizePolicy(sizePolicy);
        controlsScene->setMinimumSize(QSize(200, 0));
        verticalLayout_2 = new QVBoxLayout(controlsScene);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(controlsScene);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);


        verticalLayout->addWidget(controlsScene);


        horizontalLayout->addLayout(verticalLayout);

        openGLWidget = new GLWidget(centralwidget);
        openGLWidget->setObjectName("openGLWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(openGLWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        menuScene = new QMenu(menubar);
        menuScene->setObjectName("menuScene");
        menuCamera = new QMenu(menubar);
        menuCamera->setObjectName("menuCamera");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuScene->menuAction());
        menubar->addAction(menuCamera->menuAction());
        menuScene->addAction(actionSceneProjectiles);
        menuScene->addAction(actionSceneFountain);
        menuScene->addAction(actionSceneRope);
        menuScene->addAction(actionSceneCloth);
        menuScene->addAction(actionSceneTestIntegrators);
        menuScene->addAction(actionSceneTestColliders);
        menuCamera->addAction(actionCameraReset);
        menuCamera->addAction(actionCameraX);
        menuCamera->addAction(actionCameraY);
        menuCamera->addAction(actionCameraZ);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Computer Animation: Physical Simulations", nullptr));
        actionSceneFountain->setText(QCoreApplication::translate("MainWindow", "Fountain", nullptr));
        actionCameraReset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        actionSceneProjectiles->setText(QCoreApplication::translate("MainWindow", "Projectiles", nullptr));
        actionCameraX->setText(QCoreApplication::translate("MainWindow", "Align +X", nullptr));
        actionCameraY->setText(QCoreApplication::translate("MainWindow", "Align +Y", nullptr));
        actionCameraZ->setText(QCoreApplication::translate("MainWindow", "Align +Z", nullptr));
        actionSceneCloth->setText(QCoreApplication::translate("MainWindow", "Cloth", nullptr));
        actionSceneTestIntegrators->setText(QCoreApplication::translate("MainWindow", "Test: integrators", nullptr));
        actionSceneTestColliders->setText(QCoreApplication::translate("MainWindow", "Test: colliders", nullptr));
        actionSceneRope->setText(QCoreApplication::translate("MainWindow", "Elastic rope", nullptr));
        controlsSim->setTitle(QCoreApplication::translate("MainWindow", "Simulation controls", nullptr));
        btnPause->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Time step:", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "Restart", nullptr));
        btnSimloop->setText(QCoreApplication::translate("MainWindow", "Simulate!", nullptr));
        btnSimstep->setText(QCoreApplication::translate("MainWindow", "1 step", nullptr));
        controlsScene->setTitle(QCoreApplication::translate("MainWindow", "Scene settings", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "No scene loaded", nullptr));
        menuScene->setTitle(QCoreApplication::translate("MainWindow", "Scene", nullptr));
        menuCamera->setTitle(QCoreApplication::translate("MainWindow", "Camera", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
