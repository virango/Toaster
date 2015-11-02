#include "MetalDSFrame.h"
#include "ui_MetalDSFrame.h"

MetalDSFrame::MetalDSFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MetalDSFrame)
{
  ui->setupUi(this);
}

MetalDSFrame::~MetalDSFrame()
{
  delete ui;
}
