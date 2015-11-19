#include "PhaserFrame.h"
#include "ui_PhaserFrame.h"
#include "Stomp.h"

PhaserFrame::PhaserFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::PhaserFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->pageDial->setValue(0);
}

PhaserFrame::~PhaserFrame()
{
  delete ui;
}

void PhaserFrame::activate(Stomp& stomp)
{
  mpStomp = &stomp;

  connect(mpStomp, SIGNAL(modulationRateReceived(double, unsigned short)), this, SLOT(onRate(double, unsigned short)));
  connect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
  connect(mpStomp, SIGNAL(modulationManualReceived(double)), this, SLOT(onManual(double)));
  connect(mpStomp, SIGNAL(modulationFeedbackReceived(double)), this, SLOT(onFeedback(double)));
  connect(mpStomp, SIGNAL(modulationPhaserPeakSpreadReceived(double)), this, SLOT(onPeakSpread(double)));
  connect(mpStomp, SIGNAL(modulationPhaserStagesReceived(double)), this, SLOT(onStages(double)));
  connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
  connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));

  mpStomp->requestModulationRate();
  mpStomp->requestModulationDepth();
  mpStomp->requestModulationManual();
  mpStomp->requestModulationFeedback();
  mpStomp->requestModulationPhaserPeakSpread();
  mpStomp->requestModulationPhaserStages();
  mpStomp->requestMix();
  mpStomp->requestDucking();
  mpStomp->requestVolume();

  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(stomp.getInstance()));
}

void PhaserFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(modulationRateReceived(double, unsigned short)), this, SLOT(onRate(double, unsigned short)));
    disconnect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
    disconnect(mpStomp, SIGNAL(modulationManualReceived(double)), this, SLOT(onManual(double)));
    disconnect(mpStomp, SIGNAL(modulationFeedbackReceived(double)), this, SLOT(onFeedback(double)));
    disconnect(mpStomp, SIGNAL(modulationPhaserPeakSpreadReceived(double)), this, SLOT(onPeakSpread(double)));
    disconnect(mpStomp, SIGNAL(modulationPhaserStagesReceived(double)), this, SLOT(onStages(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  }
  mpStomp = nullptr;
}

void PhaserFrame::setFXType(FXType fxType)
{
  mFXType = fxType;
  ui->lcdDisplay->setStompName(LookUpTables::stompFXName(fxType));

  if(mFXType == PhaserOneway)
  {
    ui->rateDial->setLEDRingType(QToasterDial::Bi);
    ui->rateDial->setMinValue(-5.0);
    ui->rateDial->setMaxValue(5.0);
    ui->rateDial->setStepWidth(0.1);
    ui->rateDial->setPrecision(1);

    ui->manualDial->setLEDRingType(QToasterDial::Bi);
    ui->manualDial->setMinValue(-5.0);
    ui->manualDial->setMaxValue(5);
  }
  else
  {
    ui->rateDial->setLEDRingType(QToasterDial::Uni);
    ui->rateDial->setMinValue(0.0);
    ui->rateDial->setMaxValue(16383.0);
    ui->rateDial->setStepWidth(1.0);
    ui->rateDial->setPrecision(0);

    ui->manualDial->setLEDRingType(QToasterDial::Uni);
    ui->manualDial->setMinValue(0);
    ui->manualDial->setMaxValue(10);
  }
}

void PhaserFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void PhaserFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void PhaserFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void PhaserFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void PhaserFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void PhaserFrame::on_pageDial_valueChanged(int valueIndex)
{
  ui->lcdDisplay->setCurrentPage((QToasterStompEditLCD::Page)valueIndex);
}

void PhaserFrame::on_rateDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
  {
    if(mFXType == PhaserOneway)
      mpStomp->applyModulationRate(value + 5.0);
    else
      mpStomp->applyModulationRate(value);
  }
}

void PhaserFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void PhaserFrame::on_manualDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
  {
    if(mFXType == PhaserOneway)
      mpStomp->applyModulationManual(value + 5.0);
    else
      mpStomp->applyModulationManual(value);
  }
}

void PhaserFrame::on_feedbackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationFeedback(value);
}

void PhaserFrame::on_peakSpreadDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationPhaserPeakSpread(value);
}

void PhaserFrame::on_stagesDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationPhaserStages(value);
}

void PhaserFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void PhaserFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void PhaserFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void PhaserFrame::onRate(double value, unsigned short rawVal)
{
  if(mFXType == PhaserOneway)
    ui->rateDial->setValue(value - 5.0);
  else
    ui->rateDial->setValue((double) rawVal);
}

void PhaserFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
}

void PhaserFrame::onManual(double value)
{
  if(mFXType == PhaserOneway)
    ui->manualDial->setValue(value);
  else
    ui->manualDial->setValue(value - 5.0);
}

void PhaserFrame::onFeedback(double value)
{
  ui->feedbackDial->setValue(value);
}

void PhaserFrame::onPeakSpread(double value)
{
  ui->peakSpreadDial->setValue(value);
}

void PhaserFrame::onStages(double value)
{
  ui->stagesDial->setValue(value);
}

void PhaserFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
}

void PhaserFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
}

void PhaserFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
}

