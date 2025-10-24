#include "widgetfountain.h"
#include "ui_widgetfountain.h"

WidgetFountain::WidgetFountain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetFountain)
{
    ui->setupUi(this);

    connect(ui->btnUpdate, &QPushButton::clicked, this,
            [=] (void) { emit updatedParameters(); });
}

WidgetFountain::~WidgetFountain()
{
    delete ui;
}

double WidgetFountain::getGravity() const {
    return ui->gravity->value();
}

bool WidgetFountain::getParticleCollisions() const {
    return ui->ParticleCollisionCheckBox->isChecked();
}

bool WidgetFountain::getUseAccelerationStructure() const {
    return ui->AccelerationStructure->isChecked();
}

bool WidgetFountain::getDrawAccelerationStructure() const {
    return ui->DrawAccelerationStructure->isChecked();
}

float WidgetFountain::getAccelerationStructureSpacing() const {
    return (float)(ui->AccelerationStructureSpacing->value());
}
