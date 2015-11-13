#include "StudioEqualizerFrame.h"
#include "ui_StudioEqualizerFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

StudioEqualizerFrame::StudioEqualizerFrame(QWidget *parent)
  : QWidget(parent)
  ,ui(new Ui::StudioEqualizerFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->pageDial->setValue(0);
}

StudioEqualizerFrame::~StudioEqualizerFrame()
{
  delete ui;
}
void StudioEqualizerFrame::activate(Stomp& stomp)
{
  mpStomp = &stomp;
  connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
  connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  connect(mpStomp, SIGNAL(lowCutReceived(double)), this, SLOT(onLowCut(double)));
  connect(mpStomp, SIGNAL(highCutReceived(double)), this, SLOT(onHighCut(double)));
  connect(mpStomp, SIGNAL(parametricEQLowGainReceived(double)), this, SLOT(onLowGain(double)));
  connect(mpStomp, SIGNAL(parametricEQLowFrequencyReceived(double)), this, SLOT(onLowFreq(double)));
  connect(mpStomp, SIGNAL(parametricEQHighGainReceived(double)), this, SLOT(onHighGain(double)));
  connect(mpStomp, SIGNAL(parametricEQHighFrequencyReceived(double)), this, SLOT(onHighFreq(double)));
  connect(mpStomp, SIGNAL(parametricEQPeakGainReceived(double)), this, SLOT(onMid1Gain(double)));
  connect(mpStomp, SIGNAL(parametricEQPeakFrequencyReceived(double)), this, SLOT(onMid1Freq(double)));
  connect(mpStomp, SIGNAL(parametricEQPeakQFactorReceived(double)), this, SLOT(onMid1QFactor(double)));
  connect(mpStomp, SIGNAL(parametricEQPeakGain2Received(double)), this, SLOT(onMid2Gain(double)));
  connect(mpStomp, SIGNAL(parametricEQPeakFrequency2Received(double)), this, SLOT(onMid2Freq(double)));
  connect(mpStomp, SIGNAL(parametricEQPeakQFactor2Received(double)), this, SLOT(onMid2QFactor(double)));

  mpStomp->requestMix();
  mpStomp->requestDucking();
  mpStomp->requestVolume();
  mpStomp->requestLowCut();
  mpStomp->requestHighCut();
  mpStomp->requestParametricEQLowGain();
  mpStomp->requestParametricEQLowFrequency();
  mpStomp->requestParametricEQHighGain();
  mpStomp->requestParametricEQHighFrequency();
  mpStomp->requestParametricEQPeakGain();
  mpStomp->requestParametricEQPeakFrequency();
  mpStomp->requestParametricEQPeakQFactor();
  mpStomp->requestParametricEQPeakGain2();
  mpStomp->requestParametricEQPeakFrequency2();
  mpStomp->requestParametricEQPeakQFactor2();

  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(stomp.getInstance()));
}

void StudioEqualizerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(lowCutReceived(double)), this, SLOT(onLowCut(double)));
    disconnect(mpStomp, SIGNAL(highCutReceived(double)), this, SLOT(onhighCut(double)));
    disconnect(mpStomp, SIGNAL(parametricEQLowGainReceived(double)), this, SLOT(onLowGain(double)));
    disconnect(mpStomp, SIGNAL(parametricEQLowFrequencyReceived(double)), this, SLOT(onLowFreq(double)));
    disconnect(mpStomp, SIGNAL(parametricEQHighGainReceived(double)), this, SLOT(onHighGain(double)));
    disconnect(mpStomp, SIGNAL(parametricEQHighFrequencyReceived(double)), this, SLOT(onHighFreq(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakGainReceived(double)), this, SLOT(onMid1Gain(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakFrequencyReceived(double)), this, SLOT(onMid1Freq(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakQFactorReceived(double)), this, SLOT(onMid1QFactor(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakGain2Received(double)), this, SLOT(onMid2Gain(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakFrequency2Received(double)), this, SLOT(onMid2Freq(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakQFactor2Received(double)), this, SLOT(onMid2QFactor(double)));
  }
  mpStomp = nullptr;
}
void StudioEqualizerFrame::setFXType(FXType fxType)
{
  mFXType = fxType;
  ui->lcdDisplay->setStompName(LookUpTables::stompFXName(fxType));
}

void StudioEqualizerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void StudioEqualizerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void StudioEqualizerFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void StudioEqualizerFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void StudioEqualizerFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void StudioEqualizerFrame::on_pageDial_valueChanged(int valueIndex)
{
  ui->lcdDisplay->setCurrentPage((QToasterStompEditLCD::Page)valueIndex);
}

void StudioEqualizerFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void StudioEqualizerFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void StudioEqualizerFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void StudioEqualizerFrame::on_lowCutDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyLowCut(value);
}

void StudioEqualizerFrame::on_highCutDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyHighCut(value);
}

void StudioEqualizerFrame::on_lowGainDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQLowGain(value);
}

void StudioEqualizerFrame::on_lowFreqDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQLowFrequency(value);
}

void StudioEqualizerFrame::on_highGainDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQHighGain(value);
}

void StudioEqualizerFrame::on_highFreqDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQHighFrequency(value);
}
void StudioEqualizerFrame::on_mid1GainDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakGain(value);
}

void StudioEqualizerFrame::on_mid1FreqDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakFrequency(value);
}

void StudioEqualizerFrame::on_mid1QFactorDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakQFactor(value);
}

void StudioEqualizerFrame::on_mid2GainDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakGain2(value);
}

void StudioEqualizerFrame::on_mid2FreqDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakFrequency2(value);
}

void StudioEqualizerFrame::on_mid2QFactorDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakQFactor2(value);
}

void StudioEqualizerFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onLowCut(double value)
{
  ui->lowCutDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onHighCut(double value)
{
  ui->highCutDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onLowGain(double value)
{
  ui->lowGainDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onLowFreq(double value)
{
  ui->lowFreqDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onHighGain(double value)
{
  ui->highGainDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onHighFreq(double value)
{
  ui->highFreqDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid1Gain(double value)
{
  ui->mid1GainDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid1Freq(double value)
{
  ui->mid1FreqDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid1QFactor(double value)
{
  ui->mid1QFactorDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid2Gain(double value)
{
  ui->mid2GainDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid2Freq(double value)
{
  ui->mid2FreqDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid2QFactor(double value)
{
  ui->mid2QFactorDial->setValue(value);
  update();
}
