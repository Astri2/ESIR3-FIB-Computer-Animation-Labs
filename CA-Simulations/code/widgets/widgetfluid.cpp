#include "widgetfluid.h"
#include "ui_widgetfluid.h"

WidgetFluid::WidgetFluid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetFluid)
{
    ui->setupUi(this);

    connect(ui->btnUpdate, &QPushButton::clicked, this,
            [=] (void) { emit updatedParameters(); });
}

WidgetFluid::~WidgetFluid()
{
    delete ui;
}

double WidgetFluid::getGravity() const {
    return ui->gravity->value();
}

bool WidgetFluid::isValveOpen() const {
    return ui->valveOpen->isChecked();
}

double WidgetFluid::getPradius() const {
    return ui->Pradius->value();
}

double WidgetFluid::getPmass() const {
    return ui->Pmass->value();
}

double WidgetFluid::getH() const {
    return ui->h->value();
}

double WidgetFluid::getCs() const {
    return ui->cs->value();
}

double WidgetFluid::getRho0() const {
    return ui->rho0->value();
}

double WidgetFluid::getMu() const {
    return ui->mu->value();
}

int WidgetFluid::getSradius() const {
    return ui->Sradius->value();
}

int WidgetFluid::getLwater() const {
    return ui->Lwater->value();
}
