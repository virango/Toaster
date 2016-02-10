#include "OutputFrame.h"
#include "ui_OutputFrame.h"

OutputFrame::OutputFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::OutputFrame)
{
  ui->setupUi(this);
}

OutputFrame::~OutputFrame()
{
  delete ui;
}
