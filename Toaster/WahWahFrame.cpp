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
