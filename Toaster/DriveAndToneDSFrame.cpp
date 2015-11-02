#include "DriveAndToneDSFrame.h"
#include "ui_DriveAndToneDSFrame.h"

DriveAndToneDSFrame::DriveAndToneDSFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DriveAndToneDSFrame)
{
  ui->setupUi(this);
}

DriveAndToneDSFrame::~DriveAndToneDSFrame()
{
  delete ui;
}
