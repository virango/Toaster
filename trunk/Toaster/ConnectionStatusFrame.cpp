#include "ConnectionStatusFrame.h"
#include "ui_ConnectionStatusFrame.h"

ConnectionStatusFrame::ConnectionStatusFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::ConnectionStatusFrame)
{
  ui->setupUi(this);
}

ConnectionStatusFrame::~ConnectionStatusFrame()
{
  delete ui;
}

void ConnectionStatusFrame::setMidiStatus(bool isConnected)
{
  if(isConnected)
    ui->midiStatusLed->setColor(QMultiColorLed::Green);
  else
    ui->midiStatusLed->setColor(QMultiColorLed::Off);
  update();
}

void ConnectionStatusFrame::setKPAStatus(bool isConnected)
{
  if(isConnected)
    ui->kpaStatusLed->setColor(QMultiColorLed::Green);
  else
    ui->kpaStatusLed->setColor(QMultiColorLed::Off);
  update();
}
