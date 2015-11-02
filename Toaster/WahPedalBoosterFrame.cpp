#include "WahPedalBoosterFrame.h"
#include "ui_WahPedalBoosterFrame.h"

WahPedalBoosterFrame::WahPedalBoosterFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::WahPedalBoosterFrame)
{
  ui->setupUi(this);
}

WahPedalBoosterFrame::~WahPedalBoosterFrame()
{
  delete ui;
}
