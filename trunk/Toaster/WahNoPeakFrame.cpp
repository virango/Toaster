#include "WahNoPeakFrame.h"
#include "ui_WahNoPeakFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

WahNoPeakFrame::WahNoPeakFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::WahNoPeakFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);

  ui->pageDial->setValue(0);
}

WahNoPeakFrame::~WahNoPeakFrame()
{
  delete ui;
}

void WahNoPeakFrame::activate(Stomp& stomp)
{
  mpStomp = &stomp;

  connect(mpStomp, SIGNAL(wahManualReceived(double)), this, SLOT(onManual(double)));
  connect(mpStomp, SIGNAL(wahRangeReceived(double)), this, SLOT(onPedalRange(double)));
  connect(mpStomp, SIGNAL(wahPedalModeReceived(::WahPedalMode)), this, SLOT(onPedalMode(::WahPedalMode)));
  connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
  connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  connect(mpStomp, SIGNAL(wahTouchAttackReceived(double)), this, SLOT(onTouchAttack(double)));
  connect(mpStomp, SIGNAL(wahTouchReleaseReceived(double)), this, SLOT(onTouchRelease(double)));
  connect(mpStomp, SIGNAL(wahTouchBoostReceived(double)), this, SLOT(onTouchBoost(double)));

  mpStomp->requestWahManual();
  mpStomp->requestWahRange();
  mpStomp->requestWahPedalMode();
  mpStomp->requestMix();
  mpStomp->requestDucking();
  mpStomp->requestVolume();
  mpStomp->requestWahTouchAttack();
  mpStomp->requestWahTouchRelease();
  mpStomp->requestWahTouchBoost();

  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(stomp.getInstance()));
}

void WahNoPeakFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(wahManualReceived(double)), this, SLOT(onManual(double)));
    disconnect(mpStomp, SIGNAL(wahRangeReceived(double)), this, SLOT(onPedalRange(double)));
    disconnect(mpStomp, SIGNAL(wahPedalModeReceived(::WahPedalMode)), this, SLOT(onPedalMode(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(wahTouchAttackReceived(double)), this, SLOT(onTouchAttack(double)));
    disconnect(mpStomp, SIGNAL(wahTouchReleaseReceived(double)), this, SLOT(onTouchRelease(double)));
    disconnect(mpStomp, SIGNAL(wahTouchBoostReceived(double)), this, SLOT(onTouchBoost(double)));
  }
  mpStomp = nullptr;
}

void WahNoPeakFrame::setFXType(FXType fxType)
{
  mFXType = fxType;
  ui->lcdDisplay->setStompName(LookUpTables::stompFXName(fxType));
}


void WahNoPeakFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void WahNoPeakFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void WahNoPeakFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void WahNoPeakFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void WahNoPeakFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void WahNoPeakFrame::on_pageDial_valueChanged(int valueIndex)
{
  ui->lcdDisplay->setCurrentPage((QToasterStompEditLCD::Page)valueIndex);
}

void WahNoPeakFrame::on_manualDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahManual(value);
}

void WahNoPeakFrame::on_pedalRangeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahRange(value);
}

void WahNoPeakFrame::on_pedalModeDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahPedalMode((::WahPedalMode)valueIndex);
}

void WahNoPeakFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void WahNoPeakFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void WahNoPeakFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void WahNoPeakFrame::on_touchAttackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahTouchAttack(value);
}

void WahNoPeakFrame::on_touchReleaseDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahTouchRelease(value);
}

void WahNoPeakFrame::on_touchBoostDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahTouchBoost(value);
}

void WahNoPeakFrame::onManual(double value)
{
  ui->manualDial->setValue(value);
  update();
}

void WahNoPeakFrame::onPedalRange(double value)
{
  ui->pedalRangeDial->setValue(value);
  update();
}

void WahNoPeakFrame::onPedalMode(WahPedalMode value)
{
  ui->pedalModeDial->setValue((int)value);
  update();
}

void WahNoPeakFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void WahNoPeakFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void WahNoPeakFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void WahNoPeakFrame::onTouchAttack(double value)
{
  ui->touchAttackDial->setValue(value);
  update();
}

void WahNoPeakFrame::onTouchRelease(double value)
{
  ui->touchReleaseDial->setValue(value);
  update();
}

void WahNoPeakFrame::onTouchBoost(double value)
{
  ui->touchBoostDial->setValue(value);
  update();
}

