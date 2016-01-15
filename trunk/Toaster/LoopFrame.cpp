#include "LoopFrame.h"
#include "ui_LoopFrame.h"
#include "Stomp.h"

LoopFrame::LoopFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::LoopFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

LoopFrame::~LoopFrame()
{
  delete ui;
}

void LoopFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));

    mpStomp->requestVolume();
    mpStomp->requestMix();
    mpStomp->requestDucking();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void LoopFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  }
  mpStomp = nullptr;
}

void LoopFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void LoopFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void LoopFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void LoopFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void LoopFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void LoopFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void LoopFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionShaperDrive(value);
}

void LoopFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void LoopFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void LoopFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void LoopFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}
