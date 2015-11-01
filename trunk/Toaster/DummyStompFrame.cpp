#include "DummyStompFrame.h"
#include "ui_DummyStompFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

DummyStompFrame::DummyStompFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::DummyStompFrame)
  , mpStomp(nullptr)
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
  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(stomp.getInstance()));
}

void DummyStompFrame::deactivate()
{
  mpStomp = nullptr;
}

void DummyStompFrame::setStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void DummyStompFrame::setStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void DummyStompFrame::setDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void DummyStompFrame::setReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void DummyStompFrame::setAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}
