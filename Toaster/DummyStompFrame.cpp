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

void DummyStompFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void DummyStompFrame::deactivate()
{
  mpStomp = nullptr;
}

void DummyStompFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void DummyStompFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void DummyStompFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void DummyStompFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void DummyStompFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}
