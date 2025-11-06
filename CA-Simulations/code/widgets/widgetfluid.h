#ifndef WIDGETFLUID_H
#define WIDGETFLUID_H

#include <QWidget>

namespace Ui {
class WidgetFluid;
}

class WidgetFluid : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetFluid(QWidget *parent = nullptr);
    ~WidgetFluid();

    double getGravity()    const;

    bool   isValveOpen()   const;

    double getPradius() const;
    double getPmass() const;
    double getH() const;
    double getCs() const;
    double getRho0() const;
    double getMu() const;
    int getSradius() const;
    int getLwater() const;
signals:
    void updatedParameters();

private:
    Ui::WidgetFluid *ui;
};

#endif // WIDGETFLUID_H
