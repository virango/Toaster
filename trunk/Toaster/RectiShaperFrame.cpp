#include "RectiShaperFrame.h"
#include "ui_RectiShaperFrame.h"

RectiShaperFrame::RectiShaperFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::RectiShaperFrame)
{
  ui->setupUi(this);
}

RectiShaperFrame::~RectiShaperFrame()
{
  delete ui;
}
