#include "WahWahFrame.h"
#include "ui_WahWahFrame.h"

WahWahFrame::WahWahFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::WahWahFrame)
{
  ui->setupUi(this);
}

WahWahFrame::~WahWahFrame()
{
  delete ui;
}



void WahWahFrame::on_manualDial_valueChanged(double arg1)
{

}

void WahWahFrame::on_peakDial_valueChanged(double arg1)
{

}

void WahWahFrame::on_pedalRangeDial_valueChanged(double arg1)
{

}

void WahWahFrame::on_peakRangeDial_valueChanged(double arg1)
{

}

void WahWahFrame::on_pedalModeDial_valueChanged(int valueIndex)
{

}

void WahWahFrame::on_mixDial_valueChanged(double arg1)
{

}

void WahWahFrame::on_duckingDial_valueChanged(double arg1)
{

}

void WahWahFrame::on_page1Dial_valueChanged(double arg1)
{

}
