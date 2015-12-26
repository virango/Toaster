#include "WahPedalBoosterFrame.h"
#include "ui_WahPedalBoosterFrame.h"
#include "Stomp.h"

WahPedalBoosterFrame::WahPedalBoosterFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::WahPedalBoosterFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

WahPedalBoosterFrame::~WahPedalBoosterFrame()
{
  delete ui;
}

void WahPedalBoosterFrame::activate(QObject& stomp)
{
  mpStomp = dynamic_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(wahRangeReceived(double)), this, SLOT(onPedalRange(double)));

    mpStomp->requestVolume();
    mpStomp->requestWahRange();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void WahPedalBoosterFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(wahRangeReceived(double)), this, SLOT(onPedalRange(double)));
  }
  mpStomp = nullptr;
}

void WahPedalBoosterFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void WahPedalBoosterFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void WahPedalBoosterFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void WahPedalBoosterFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void WahPedalBoosterFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void WahPedalBoosterFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void WahPedalBoosterFrame::on_pedalRangeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahRange(value);
}

void WahPedalBoosterFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void WahPedalBoosterFrame::onPedalRange(double value)
{
  ui->pedalRangeDial->setValue(value);
  update();
}
