#include "TunerFrame.h"
#include "ui_TunerFrame.h"

TunerFrame::TunerFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TunerFrame)
{
  ui->setupUi(this);
}

TunerFrame::~TunerFrame()
{
  delete ui;
}
