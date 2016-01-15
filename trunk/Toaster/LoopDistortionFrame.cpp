#include "LoopDistortionFrame.h"
#include "ui_LoopDistortionFrame.h"
#include "Stomp.h"

LoopDistortionFrame::LoopDistortionFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::LoopDistortionFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

LoopDistortionFrame::~LoopDistortionFrame()
{
  delete ui;
}

void LoopDistortionFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));

    mpStomp->requestVolume();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void LoopDistortionFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  }
  mpStomp = nullptr;
}

void LoopDistortionFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void LoopDistortionFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void LoopDistortionFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void LoopDistortionFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void LoopDistortionFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void LoopDistortionFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void LoopDistortionFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

