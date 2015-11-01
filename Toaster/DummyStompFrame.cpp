#include "DummyStompFrame.h"
#include "ui_DummyStompFrame.h"

DummyStompFrame::DummyStompFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DummyStompFrame)
{
  ui->setupUi(this);
}

DummyStompFrame::~DummyStompFrame()
{
  delete ui;
}

void DummyStompFrame::activate(Stomp& stomp)
{
  mpStomp = &stomp;
}

void DummyStompFrame::deactivate()
{
  mpStomp = nullptr;
}

void DummyStompFrame::setStompType(StompInstance stompInstance, FXType fxType)
{
  ui->dummyLCD->setStompFXType(stompInstance, fxType);
}

void DummyStompFrame::setStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->dummyLCD->setStompEnabled(stompInstance, enabled);
}

void DummyStompFrame::setAmpName(const QString&  ampName)
{

}
