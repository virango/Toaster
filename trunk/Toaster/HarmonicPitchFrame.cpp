#include "HarmonicPitchFrame.h"
#include "ui_HarmonicPitchFrame.h"

HarmonicPitchFrame::HarmonicPitchFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::HarmonicPitchFrame)
{
  ui->setupUi(this);
}

HarmonicPitchFrame::~HarmonicPitchFrame()
{
  delete ui;
}
