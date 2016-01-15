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
  ui->rateDial->setLookUpTable(LookUpTables::getFlangerRateValues());
  ui->pageDial->setValue(0);
}

PhaserFrame::~PhaserFrame()
{
  delete ui;
}

void PhaserFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(modulationRateReceived(int)), this, SLOT(onRate(int)));
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

void PhaserFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(modulationRateReceived(int)), this, SLOT(onRate(int)));
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

void PhaserFrame::on_rateDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationRate(value);
}

void PhaserFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void PhaserFrame::on_manualDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationManual(value);
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

void PhaserFrame::on_stereoDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyStereo(value);
}

void PhaserFrame::onRate(int value)
{
  ui->rateDial->setValue(value*128);
  update();
}

void PhaserFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
  update();
}

void PhaserFrame::onManual(double value)
{
  ui->manualDial->setValue(value);
  update();
}

void PhaserFrame::onFeedback(double value)
{
  ui->feedbackDial->setValue(value);
  update();
}

void PhaserFrame::onPeakSpread(double value)
{
  ui->peakSpreadDial->setValue(value);
  update();
}

void PhaserFrame::onStages(double value)
{
  ui->stagesDial->setValue(value);
  update();
}

void PhaserFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void PhaserFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void PhaserFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void PhaserFrame::onStereo(double value)
{
  ui->stereoDial->setValue(value);
  update();
}
