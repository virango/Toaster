#include "DriveDSFrame.h"
#include "ui_DriveDSFrame.h"

DriveDSFrame::DriveDSFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DriveDSFrame)
{
  ui->setupUi(this);
}

DriveDSFrame::~DriveDSFrame()
{
  delete ui;
}
