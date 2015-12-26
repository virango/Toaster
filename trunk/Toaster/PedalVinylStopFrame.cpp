#include "PedalVinylStopFrame.h"
#include "ui_PedalVinylStopFrame.h"
#include "Stomp.h"

PedalVinylStopFrame::PedalVinylStopFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::PedalVinylStopFrame)
  , mpStomp(nullptr)
  , mGlobal()
  , mFXType(None)
{
  ui->setupUi(this);
}

PedalVinylStopFrame::~PedalVinylStopFrame()
{
  delete ui;
}

void PedalVinylStopFrame::activate(QObject& stomp)
{
  mpStomp = dynamic_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    connect(&mGlobal, SIGNAL(wahPedalToPitchReceived(bool)), this, SLOT(onWahPedalToPitch(bool)));

    mpStomp->requestVolume();
    mpStomp->requestMix();
    mGlobal.requestWahPedalToPitch();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void PedalVinylStopFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(&mGlobal, SIGNAL(wahPedalToPitchReceived(bool)), this, SLOT(onWahPedalToPitch(bool)));
  }
  mpStomp = nullptr;
}

void PedalVinylStopFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void PedalVinylStopFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void PedalVinylStopFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void PedalVinylStopFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void PedalVinylStopFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void PedalVinylStopFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void PedalVinylStopFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void PedalVinylStopFrame::on_wahPedalToPitchDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mGlobal.applyWahPedalToPitchReceived(valueIndex != 0);
}

void PedalVinylStopFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void PedalVinylStopFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void PedalVinylStopFrame::onWahPedalToPitch(bool onOff)
{
  ui->wahPedalToPitchDial->setValue(onOff ? 1 : 0);
  update();
}
