#include "PureBoosterFrame.h"
#include "ui_PureBoosterFrame.h"

PureBoosterFrame::PureBoosterFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PureBoosterFrame)
{
  ui->setupUi(this);
}

PureBoosterFrame::~PureBoosterFrame()
{
  delete ui;
}
