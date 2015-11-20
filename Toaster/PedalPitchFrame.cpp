#include "PedalPitchFrame.h"
#include "ui_PedalPitchFrame.h"

PedalPitchFrame::PedalPitchFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PedalPitchFrame)
{
  ui->setupUi(this);
}

PedalPitchFrame::~PedalPitchFrame()
{
  delete ui;
}
