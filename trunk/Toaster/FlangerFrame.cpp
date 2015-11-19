#include "FlangerFrame.h"
#include "ui_FlangerFrame.h"

FlangerFrame::FlangerFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FlangerFrame)
{
  ui->setupUi(this);
}

FlangerFrame::~FlangerFrame()
{
  delete ui;
}
