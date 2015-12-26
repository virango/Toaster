#include "MetalEqualizerFrame.h"
#include "ui_MetalEqualizerFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

MetalEqualizerFrame::MetalEqualizerFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::MetalEqualizerFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->pageDial->setValue(0);
}

MetalEqualizerFrame::~MetalEqualizerFrame()
{
  delete ui;
}

void MetalEqualizerFrame::activate(QObject& stomp)
{
  mpStomp = dynamic_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(parametricEQLowGainReceived(double)), this, SLOT(onLowDial(double)));
    connect(mpStomp, SIGNAL(parametricEQPeakGainReceived(double)), this, SLOT(onMiddleDial(double)));
    connect(mpStomp, SIGNAL(parametricEQPeakFrequencyReceived(double)), this, SLOT(onMidFreqDial(double)));
    connect(mpStomp, SIGNAL(parametricEQHighGainReceived(double)), this, SLOT(onHighDial(double)));
    connect(mpStomp, SIGNAL(lowCutReceived(double)), this, SLOT(onLowCut(double)));
    connect(mpStomp, SIGNAL(highCutReceived(double)), this, SLOT(onHighCut(double)));
    connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));

    mpStomp->requestParametricEQLowGain();
    mpStomp->requestParametricEQPeakGain();
    mpStomp->requestParametricEQPeakFrequency();
    mpStomp->requestParametricEQHighGain();
    mpStomp->requestLowCut();
    mpStomp->requestHighCut();
    mpStomp->requestMix();
    mpStomp->requestDucking();
    mpStomp->requestVolume();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void MetalEqualizerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(parametricEQLowGainReceived(double)), this, SLOT(onLowDial(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakGainReceived(double)), this, SLOT(onMiddleDial(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakFrequencyReceived(double)), this, SLOT(onMidFreqDial(double)));
    disconnect(mpStomp, SIGNAL(parametricEQHighGainReceived(double)), this, SLOT(onHighDial(double)));
    disconnect(mpStomp, SIGNAL(lowCutReceived(double)), this, SLOT(onLowCut(double)));
    disconnect(mpStomp, SIGNAL(highCutReceived(double)), this, SLOT(onHighCut(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  }
  mpStomp = nullptr;
}

void MetalEqualizerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void MetalEqualizerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void MetalEqualizerFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void MetalEqualizerFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void MetalEqualizerFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void MetalEqualizerFrame::on_pageDial_valueChanged(int valueIndex)
{
  ui->lcdDisplay->setCurrentPage((QToasterStompEditLCD::Page)valueIndex);
}

void MetalEqualizerFrame::on_lowDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQLowGain(value);
}

void MetalEqualizerFrame::on_middleDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakGain(value);
}

void MetalEqualizerFrame::on_midFreqDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakFrequency(value);
}

void MetalEqualizerFrame::on_highDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQHighGain(value);
}

void MetalEqualizerFrame::on_lowCutDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyLowCut(value);
}

void MetalEqualizerFrame::on_highCutDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyHighCut(value);
}

void MetalEqualizerFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void MetalEqualizerFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void MetalEqualizerFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void MetalEqualizerFrame::onLowDial(double value)
{
  ui->lowDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onMiddleDial(double value)
{
  ui->middleDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onMidFreqDial(double value)
{
  ui->midFreqDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onHighDial(double value)
{
  ui->highDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onLowCut(double value)
{
  ui->lowCutDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onHighCut(double value)
{
  ui->highCutDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

