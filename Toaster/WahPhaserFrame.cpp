#include "WahPhaserFrame.h"
#include "ui_WahPhaserFrame.h"

WahPhaserFrame::WahPhaserFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::WahPhaserFrame)
{
  ui->setupUi(this);
}

WahPhaserFrame::~WahPhaserFrame()
{
  delete ui;
}
