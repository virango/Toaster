#include "PhaserOnewayFrame.h"
#include "ui_PhaserOnewayFrame.h"
#include "Stomp.h"

PhaserOnewayFrame::PhaserOnewayFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::PhaserOnewayFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->pageDial->setValue(0);
}

PhaserOnewayFrame::~PhaserOnewayFrame()
{
  delete ui;
}

void PhaserOnewayFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(modulationRateReceived(double)), this, SLOT(onRate(double)));
    connect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
    connect(mpStomp, SIGNAL(modulationManualReceived(double)), this, SLOT(onManual(double)));
    connect(mpStomp, SIGNAL(modulationFeedbackReceived(double)), this, SLOT(onFeedback(double)));
    connect(mpStomp, SIGNAL(modulationPhaserPeakSpreadReceived(double)), this, SLOT(onPeakSpread(double)));
    connect(mpStomp, SIGNAL(modulationPhaserStagesReceived(double)), this, SLOT(onStages(double)));
    connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(stereoReceived(double)), this, SLOT(onStereo(double)));

    mFXType = mpStomp->getFXType();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mFXType));

    mpStomp->requestModulationRate();
    mpStomp->requestModulationDepth();
    mpStomp->requestModulationManual();
    mpStomp->requestModulationFeedback();
    mpStomp->requestModulationPhaserPeakSpread();
    mpStomp->requestModulationPhaserStages();
    mpStomp->requestMix();
    mpStomp->requestDucking();
    mpStomp->requestVolume();
    mpStomp->requestStereo();

    if(mpStomp->getInstance() != StompX && mpStomp->getInstance() != StompMOD)
    {
      ui->stereoDial->setIsActive(false);
      ui->lcdDisplay->setValue7("");
      ui->lcdDisplay->setValue7Title("");
    }
    else
    {
      ui->stereoDial->setIsActive(true);
      ui->lcdDisplay->setValue7Title("Stereo");
    }
  }
}

void PhaserOnewayFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(modulationRateReceived(double)), this, SLOT(onRate(double)));
    disconnect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
    disconnect(mpStomp, SIGNAL(modulationManualReceived(double)), this, SLOT(onManual(double)));
    disconnect(mpStomp, SIGNAL(modulationFeedbackReceived(double)), this, SLOT(onFeedback(double)));
    disconnect(mpStomp, SIGNAL(modulationPhaserPeakSpreadReceived(double)), this, SLOT(onPeakSpread(double)));
    disconnect(mpStomp, SIGNAL(modulationPhaserStagesReceived(double)), this, SLOT(onStages(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(stereoReceived(double)), this, SLOT(onStereo(double)));
  }
  mpStomp = nullptr;
}

void PhaserOnewayFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void PhaserOnewayFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void PhaserOnewayFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void PhaserOnewayFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void PhaserOnewayFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void PhaserOnewayFrame::on_pageDial_valueChanged(int valueIndex)
{
  ui->lcdDisplay->setCurrentPage((QToasterStompEditLCD::Page)valueIndex);
}

void PhaserOnewayFrame::on_rateDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationRate(value + 5.0);
}

void PhaserOnewayFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void PhaserOnewayFrame::on_manualDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationManual(value + 5.0);
}

void PhaserOnewayFrame::on_feedbackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationFeedback(value);
}

void PhaserOnewayFrame::on_peakSpreadDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationPhaserPeakSpread(value);
}

void PhaserOnewayFrame::on_stagesDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationPhaserStages(value);
}

void PhaserOnewayFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void PhaserOnewayFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void PhaserOnewayFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void PhaserOnewayFrame::on_stereoDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyStereo(value);
}

void PhaserOnewayFrame::onRate(double value)
{
  ui->rateDial->setValue(value - 5.0);
  update();
}

void PhaserOnewayFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onManual(double value)
{
  ui->manualDial->setValue(value - 5.0);
  update();
}

void PhaserOnewayFrame::onFeedback(double value)
{
  ui->feedbackDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onPeakSpread(double value)
{
  ui->peakSpreadDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onStages(double value)
{
  ui->stagesDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onStereo(double value)
{
  ui->stereoDial->setValue(value);
  update();
}


