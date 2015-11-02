#include "ToneAndDuckingDSFrame.h"
#include "ui_ToneAndDuckingDSFrame.h"

ToneAndDuckingDSFrame::ToneAndDuckingDSFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ToneAndDuckingDSFrame)
{
  ui->setupUi(this);
}

ToneAndDuckingDSFrame::~ToneAndDuckingDSFrame()
{
  delete ui;
}
